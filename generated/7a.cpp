#include <iostream>
#include <limits>
#include "load/7a.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/n.csv");
	load_pi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/pi.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/it.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/t.csv");
	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/lt.csv");
	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_an("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/an.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto pi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(pi_trie0, pi_person_id, pi_info_type_id);
		auto it_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it_trie0, it_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<string> interm0_col1;
		vector<int> interm0_col2;
		for (const auto &[x0, n_trie1]: n_trie0) {
			if (pi_trie0.contains(x0)) {
				auto &pi_trie1 = pi_trie0.at(x0);
				for (const auto &[x1, pi_trie2]: pi_trie1) {
					if (it_trie0.contains(x1)) {
						auto &it_trie1 = it_trie0.at(x1);
						for (const auto &n_off: n_trie1) {
							for (const auto &pi_off: pi_trie2) {
								interm0_col0.push_back(n_id[n_off]);
								interm0_col1.push_back(n_name[n_off]);
								interm0_col2.push_back(pi_info_type_id[pi_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto ml_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(ml_trie0, ml_linked_movie_id, ml_link_type_id);
		auto lt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(lt_trie0, lt_id);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<string> interm1_col1;
		vector<int> interm1_col2;
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (ml_trie0.contains(x0)) {
				auto &ml_trie1 = ml_trie0.at(x0);
				for (const auto &[x1, ml_trie2]: ml_trie1) {
					if (lt_trie0.contains(x1)) {
						auto &lt_trie1 = lt_trie0.at(x1);
						for (const auto &t_off: t_trie1) {
							for (const auto &ml_off: ml_trie2) {
								interm1_col0.push_back(t_id[t_off]);
								interm1_col1.push_back(t_title[t_off]);
								interm1_col2.push_back(ml_link_type_id[ml_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(ci_trie0, ci_movie_id, ci_person_id);
		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col0);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col0);
		auto an_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(an_trie0, an_person_id);
		timer.StoreElapsedTime(4);

		string mn_interm1_col1 = "zzzzzzzz";
		int mn_interm1_col2 = numeric_limits<int>::max();
		string mn_interm0_col1 = "zzzzzzzz";
		int mn_interm0_col2 = numeric_limits<int>::max();
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (interm1_trie0.contains(x0)) {
				auto &interm1_trie1 = interm1_trie0.at(x0);
				for (const auto &[x1, ci_trie2]: ci_trie1) {
					if (interm0_trie0.contains(x1) && an_trie0.contains(x1)) {
						auto &interm0_trie1 = interm0_trie0.at(x1);
						auto &an_trie1 = an_trie0.at(x1);
						for (const auto &interm1_off: interm1_trie1) {
							mn_interm1_col1 = min(mn_interm1_col1, interm1_col1[interm1_off]);
							mn_interm1_col2 = min(mn_interm1_col2, interm1_col2[interm1_off]);
						}
						for (const auto &interm0_off: interm0_trie1) {
							mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
							mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		if (z == 0)
			cout << mn_interm1_col1 << " | " << mn_interm1_col2 << " | " << mn_interm0_col1 << " | " << mn_interm0_col2 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 3 * 2; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 3; i += 2)
		cout << tm[i + 1] - tm[i] << " + " << tm[i + 2] - tm[i + 1] << " = " << tm[i + 2] - tm[i] << " ms" << endl;
	cout << tm[6] << " ms" << endl;
}
