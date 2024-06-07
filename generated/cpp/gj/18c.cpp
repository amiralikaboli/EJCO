#include <iostream>
#include <limits>
#include "load/18c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18c/mi.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18c/it2.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18c/it1.csv");
	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18c/ci.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18c/n.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mi_idx_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(mi_idx_trie0, mi_idx_movie_id);
		vector<int> interm0_col0;
		vector<string> interm0_col1;
		vector<int> interm0_col2;
		vector<string> interm0_col3;
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (mi_idx_trie0.contains(x0)) {
				auto &mi_idx_trie1 = mi_idx_trie0.at(x0);
				for (const auto &t_off: t_trie1) {
					for (const auto &mi_idx_off: mi_idx_trie1) {
						interm0_col0.push_back(t_id[t_off]);
						interm0_col1.push_back(t_title[t_off]);
						interm0_col2.push_back(mi_idx_info_type_id[mi_idx_off]);
						interm0_col3.push_back(mi_idx_info[mi_idx_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(0);

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_movie_id, mi_info_type_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(interm0_trie0, interm0_col0, interm0_col2);
		auto it2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it2_trie0, it2_id);
		auto it1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it1_trie0, it1_id);
		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<string> interm1_col2;
		vector<int> interm1_col3;
		vector<string> interm1_col4;
		vector<string> interm1_col5;
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (interm0_trie0.contains(x0)) {
				auto &interm0_trie1 = interm0_trie0.at(x0);
				for (const auto &[x1, interm0_trie2]: interm0_trie1) {
					if (it2_trie0.contains(x1)) {
						auto &it2_trie1 = it2_trie0.at(x1);
						for (const auto &[x2, mi_trie2]: mi_trie1) {
							if (it1_trie0.contains(x2)) {
								auto &it1_trie1 = it1_trie0.at(x2);
								for (const auto &mi_off: mi_trie2) {
									for (const auto &interm0_off: interm0_trie2) {
										interm1_col0.push_back(mi_movie_id[mi_off]);
										interm1_col1.push_back(mi_info_type_id[mi_off]);
										interm1_col2.push_back(mi_info[mi_off]);
										interm1_col3.push_back(interm0_col2[interm0_off]);
										interm1_col4.push_back(interm0_col1[interm0_off]);
										interm1_col5.push_back(interm0_col3[interm0_off]);
									}
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(ci_trie0, ci_person_id, ci_movie_id);
		auto n_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(n_trie0, n_id);
		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col0);
		string mn_interm1_col2 = "zzzzzzzz";
		string mn_interm1_col4 = "zzzzzzzz";
		string mn_interm1_col5 = "zzzzzzzz";
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (n_trie0.contains(x0)) {
				auto &n_trie1 = n_trie0.at(x0);
				for (const auto &[x1, ci_trie2]: ci_trie1) {
					if (interm1_trie0.contains(x1)) {
						auto &interm1_trie1 = interm1_trie0.at(x1);
						for (const auto &interm1_off: interm1_trie1) {
							mn_interm1_col2 = min(mn_interm1_col2, interm1_col2[interm1_off]);
							mn_interm1_col4 = min(mn_interm1_col4, interm1_col4[interm1_off]);
							mn_interm1_col5 = min(mn_interm1_col5, interm1_col5[interm1_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(2);

		if (z == 0)
			cout << mn_interm1_col2 << " | " << mn_interm1_col4 << " | " << mn_interm1_col5 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 3; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 3; ++i)
		cout << tm[i + 1] - tm[i] << " ms" << endl;
	cout << tm[3] << " ms" << endl;
}
