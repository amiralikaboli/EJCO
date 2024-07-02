#include <iostream>
#include <limits>
#include "load/7b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/n.csv");
	load_pi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/pi.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/it.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/t.csv");
	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/lt.csv");
	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_an("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/an.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		auto pi_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(pi_trie0, pi_person_id);
		auto it_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(it_trie0, it_id);
		vector<int> interm0_col0;
		vector<string> interm0_col1;
		vector<int> interm0_col2;
		vector<int> interm0_offsets;
		cnt = 0;
		for (const auto &n_off: n_offsets) {
			auto x0 = n_id[n_off];
			if (pi_trie0.contains(x0)) {
				auto &pi_trie1 = pi_trie0.at(x0);
				for (const auto &pi_off: pi_trie1) {
					auto x1 = pi_info_type_id[pi_off];
					if (it_trie0.contains(x1)) {
						auto &it_trie1 = it_trie0.at(x1);
						interm0_col0.push_back(n_id[n_off]);
						interm0_col1.push_back(n_name[n_off]);
						interm0_col2.push_back(pi_info_type_id[pi_off]);
						interm0_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(0);

		auto ml_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ml_trie0, ml_linked_movie_id);
		auto lt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(lt_trie0, lt_id);
		vector<int> interm1_col0;
		vector<string> interm1_col1;
		vector<int> interm1_col2;
		vector<int> interm1_offsets;
		cnt = 0;
		for (const auto &t_off: t_offsets) {
			auto x0 = t_id[t_off];
			if (ml_trie0.contains(x0)) {
				auto &ml_trie1 = ml_trie0.at(x0);
				for (const auto &ml_off: ml_trie1) {
					auto x1 = ml_link_type_id[ml_off];
					if (lt_trie0.contains(x1)) {
						auto &lt_trie1 = lt_trie0.at(x1);
						interm1_col0.push_back(t_id[t_off]);
						interm1_col1.push_back(t_title[t_off]);
						interm1_col2.push_back(ml_link_type_id[ml_off]);
						interm1_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col0);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col0);
		auto an_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(an_trie0, an_person_id);
		string mn_interm1_col1 = "zzzzzzzz";
		string mn_interm0_col1 = "zzzzzzzz";
		for (const auto &ci_off: ci_offsets) {
			auto x0 = ci_movie_id[ci_off];
			if (interm1_trie0.contains(x0)) {
				auto &interm1_trie1 = interm1_trie0.at(x0);
				auto x1 = ci_person_id[ci_off];
				if (interm0_trie0.contains(x1) && an_trie0.contains(x1)) {
					auto &interm0_trie1 = interm0_trie0.at(x1);
					auto &an_trie1 = an_trie0.at(x1);
					for (const auto &interm1_off: interm1_trie1) {
						mn_interm1_col1 = min(mn_interm1_col1, interm1_col1[interm1_off]);
					}
					for (const auto &interm0_off: interm0_trie1) {
						mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(2);

		if (z == 0)
			cout << mn_interm1_col1 << " | " << mn_interm0_col1 << endl;
		cerr << "*" << " " << flush;
	}
	cerr << endl;

	vector<double> tm{0};
	for (int i = 0; i < 3; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 3; ++i)
		cout << tm[i + 1] - tm[i] << " ms" << endl;
	cout << tm[3] << " ms" << endl;
}
