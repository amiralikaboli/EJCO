#include <iostream>
#include <limits>
#include "load/14b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/t.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/mi_idx.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/mi.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/kt.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/k.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/it2.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14b/it1.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mk_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(mk_trie0, mk_movie_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mi_idx_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(mi_idx_trie0, mi_idx_movie_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		vector<int> interm0_col3;
		vector<int> interm0_col4;
		vector<string> interm0_col5;
		for (const auto &[x0, mk_trie1]: mk_trie0) {
			if (t_trie0.contains(x0) && mi_idx_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				auto &mi_idx_trie1 = mi_idx_trie0.at(x0);
				for (const auto &mk_off: mk_trie1) {
					for (const auto &t_off: t_trie1) {
						for (const auto &mi_idx_off: mi_idx_trie1) {
							interm0_col0.push_back(mk_movie_id[mk_off]);
							interm0_col1.push_back(mk_keyword_id[mk_off]);
							interm0_col2.push_back(t_title[t_off]);
							interm0_col3.push_back(t_kind_id[t_off]);
							interm0_col4.push_back(mi_idx_info_type_id[mi_idx_off]);
							interm0_col5.push_back(mi_idx_info[mi_idx_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie(mi_trie0, mi_movie_id, mi_info_type_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>>();
		build_trie(interm0_trie0, interm0_col0, interm0_col3, interm0_col1, interm0_col4);
		auto kt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(kt_trie0, kt_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(k_trie0, k_id);
		auto it2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(it2_trie0, it2_id);
		auto it1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(it1_trie0, it1_id);
		timer.StoreElapsedTime(2);

		string mn_interm0_col2 = "zzzzzzzz";
		string mn_interm0_col5 = "zzzzzzzz";
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (interm0_trie0.contains(x0)) {
				auto &interm0_trie1 = interm0_trie0.at(x0);
				for (const auto &[x1, interm0_trie2]: interm0_trie1) {
					if (kt_trie0.contains(x1)) {
						auto &kt_trie1 = kt_trie0.at(x1);
						for (const auto &[x2, interm0_trie3]: interm0_trie2) {
							if (k_trie0.contains(x2)) {
								auto &k_trie1 = k_trie0.at(x2);
								for (const auto &[x3, interm0_trie4]: interm0_trie3) {
									if (it2_trie0.contains(x3)) {
										auto &it2_trie1 = it2_trie0.at(x3);
										for (const auto &[x4, mi_trie2]: mi_trie1) {
											if (it1_trie0.contains(x4)) {
												auto &it1_trie1 = it1_trie0.at(x4);
												for (const auto &interm0_off: interm0_trie4) {
													mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
													mn_interm0_col5 = min(mn_interm0_col5, interm0_col5[interm0_off]);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		if (z == 0)
			cout << mn_interm0_col2 << " | " << mn_interm0_col5 << endl;
		cerr << "*" << " " << flush;
	}
	cerr << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 2; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 2; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 2] << " ms" << endl;
}
