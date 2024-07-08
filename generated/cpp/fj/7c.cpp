#include <iostream>
#include <limits>
#include "load/7c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/n.csv");
	load_pi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/pi.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/it.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/t.csv");
	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/lt.csv");
	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_an("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/an.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> n_trie0 = {0, n_offsets.size() - 1};
		pair<int, int> pi_trie0 = {0, pi_offsets.size() - 1};
		pair<int, int> it_trie0 = {0, it_offsets.size() - 1};
		build_trie(pi_offsets, pi_person_id);
		build_trie(it_offsets, it_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<string> interm0_col1;
		vector<int> interm0_col2;
		vector<string> interm0_col3;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int n_i = n_trie0.first; n_i <= n_trie0.second; ++n_i) {
			const auto &n_off = n_offsets[n_i];
			auto x0 = n_id[n_off];
			auto pi_trie1 = find_range(pi_offsets, pi_person_id, x0, pi_trie0);
			if (pi_trie1.first != -1) {
				for (int pi_i = pi_trie1.first; pi_i <= pi_trie1.second; ++pi_i) {
					const auto &pi_off = pi_offsets[pi_i];
					auto x1 = pi_info_type_id[pi_off];
					auto it_trie1 = find_range(it_offsets, it_id, x1, it_trie0);
					if (it_trie1.first != -1) {
						interm0_col0.push_back(n_id[n_off]);
						interm0_col1.push_back(n_name[n_off]);
						interm0_col2.push_back(pi_info_type_id[pi_off]);
						interm0_col3.push_back(pi_info[pi_off]);
						interm0_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> ml_trie0 = {0, ml_offsets.size() - 1};
		pair<int, int> lt_trie0 = {0, lt_offsets.size() - 1};
		build_trie(ml_offsets, ml_linked_movie_id);
		build_trie(lt_offsets, lt_id);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<int> interm1_offsets;
		cnt = 0;
		for (int t_i = t_trie0.first; t_i <= t_trie0.second; ++t_i) {
			const auto &t_off = t_offsets[t_i];
			auto x0 = t_id[t_off];
			auto ml_trie1 = find_range(ml_offsets, ml_linked_movie_id, x0, ml_trie0);
			if (ml_trie1.first != -1) {
				for (int ml_i = ml_trie1.first; ml_i <= ml_trie1.second; ++ml_i) {
					const auto &ml_off = ml_offsets[ml_i];
					auto x1 = ml_link_type_id[ml_off];
					auto lt_trie1 = find_range(lt_offsets, lt_id, x1, lt_trie0);
					if (lt_trie1.first != -1) {
						interm1_col0.push_back(t_id[t_off]);
						interm1_col1.push_back(ml_link_type_id[ml_off]);
						interm1_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		pair<int, int> ci_trie0 = {0, ci_offsets.size() - 1};
		pair<int, int> interm1_trie0 = {0, interm1_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		pair<int, int> an_trie0 = {0, an_offsets.size() - 1};
		build_trie(interm1_offsets, interm1_col0);
		build_trie(interm0_offsets, interm0_col0);
		build_trie(an_offsets, an_person_id);
		timer.StoreElapsedTime(4);

		string mn_interm0_col1 = "zzzzzzzz";
		string mn_interm0_col3 = "zzzzzzzz";
		for (int ci_i = ci_trie0.first; ci_i <= ci_trie0.second; ++ci_i) {
			const auto &ci_off = ci_offsets[ci_i];
			auto x0 = ci_movie_id[ci_off];
			auto interm1_trie1 = find_range(interm1_offsets, interm1_col0, x0, interm1_trie0);
			if (interm1_trie1.first != -1) {
				auto x1 = ci_person_id[ci_off];
				auto interm0_trie1 = find_range(interm0_offsets, interm0_col0, x1, interm0_trie0);
				auto an_trie1 = find_range(an_offsets, an_person_id, x1, an_trie0);
				if (interm0_trie1.first != -1 && an_trie1.first != -1) {
					for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
						const auto &interm0_off = interm0_offsets[interm0_i];
						mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
						mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		if (z == 0)
			cout << mn_interm0_col1 << " | " << mn_interm0_col3 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 3; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 3; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 3] << " ms" << endl;
}
