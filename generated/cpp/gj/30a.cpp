#include <iostream>
#include <limits>
#include "load/30a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30a/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30a/cct2.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30a/it2.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30a/t.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30a/k.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30a/mi.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30a/it1.csv");
	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30a/ci.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30a/n.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto cc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(cc_trie0, cc_subject_id, cc_status_id);
		auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cct1_trie0, cct1_id);
		auto cct2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cct2_trie0, cct2_id);
		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_col2;
		for (const auto &[x0, cc_trie1]: cc_trie0) {
			if (cct1_trie0.contains(x0)) {
				auto &cct1_trie1 = cct1_trie0.at(x0);
				for (const auto &[x1, cc_trie2]: cc_trie1) {
					if (cct2_trie0.contains(x1)) {
						auto &cct2_trie1 = cct2_trie0.at(x1);
						for (const auto &cc_off: cc_trie2) {
							interm0_col0.push_back(cc_subject_id[cc_off]);
							interm0_col1.push_back(cc_status_id[cc_off]);
							interm0_col2.push_back(cc_movie_id[cc_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(0);

		auto mi_idx_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx_trie0, mi_idx_info_type_id, mi_idx_movie_id);
		auto it2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(it2_trie0, it2_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(interm0_trie0, interm0_col2);
		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<string> interm1_col2;
		for (const auto &[x0, mi_idx_trie1]: mi_idx_trie0) {
			if (it2_trie0.contains(x0)) {
				auto &it2_trie1 = it2_trie0.at(x0);
				for (const auto &[x1, mi_idx_trie2]: mi_idx_trie1) {
					if (interm0_trie0.contains(x1)) {
						auto &interm0_trie1 = interm0_trie0.at(x1);
						for (const auto &mi_idx_off: mi_idx_trie2) {
							interm1_col0.push_back(mi_idx_info_type_id[mi_idx_off]);
							interm1_col1.push_back(mi_idx_movie_id[mi_idx_off]);
							interm1_col2.push_back(mi_idx_info[mi_idx_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col1);
		vector<int> interm2_col0;
		vector<string> interm2_col1;
		vector<string> interm2_col3;
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (interm1_trie0.contains(x0)) {
				auto &interm1_trie1 = interm1_trie0.at(x0);
				for (const auto &t_off: t_trie1) {
					for (const auto &interm1_off: interm1_trie1) {
						interm2_col0.push_back(t_id[t_off]);
						interm2_col1.push_back(t_title[t_off]);
						interm2_col3.push_back(interm1_col2[interm1_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(2);

		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_keyword_id, mk_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(k_trie0, k_id);
		auto interm2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm2_trie0, interm2_col0);
		vector<int> interm3_col0;
		vector<int> interm3_col1;
		vector<string> interm3_col2;
		vector<string> interm3_col4;
		for (const auto &[x0, mk_trie1]: mk_trie0) {
			if (k_trie0.contains(x0)) {
				auto &k_trie1 = k_trie0.at(x0);
				for (const auto &[x1, mk_trie2]: mk_trie1) {
					if (interm2_trie0.contains(x1)) {
						auto &interm2_trie1 = interm2_trie0.at(x1);
						for (const auto &mk_off: mk_trie2) {
							for (const auto &interm2_off: interm2_trie1) {
								interm3_col0.push_back(mk_keyword_id[mk_off]);
								interm3_col1.push_back(mk_movie_id[mk_off]);
								interm3_col2.push_back(interm2_col1[interm2_off]);
								interm3_col4.push_back(interm2_col3[interm2_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_trie0, mi_info_type_id, mi_movie_id);
		auto it1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(it1_trie0, it1_id);
		auto interm3_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm3_trie0, interm3_col1);
		vector<int> interm4_col0;
		vector<int> interm4_col1;
		vector<string> interm4_col2;
		vector<string> interm4_col4;
		vector<string> interm4_col6;
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (it1_trie0.contains(x0)) {
				auto &it1_trie1 = it1_trie0.at(x0);
				for (const auto &[x1, mi_trie2]: mi_trie1) {
					if (interm3_trie0.contains(x1)) {
						auto &interm3_trie1 = interm3_trie0.at(x1);
						for (const auto &mi_off: mi_trie2) {
							for (const auto &interm3_off: interm3_trie1) {
								interm4_col0.push_back(mi_info_type_id[mi_off]);
								interm4_col1.push_back(mi_movie_id[mi_off]);
								interm4_col2.push_back(mi_info[mi_off]);
								interm4_col4.push_back(interm3_col2[interm3_off]);
								interm4_col6.push_back(interm3_col4[interm3_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(4);

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie(ci_trie0, ci_person_id, ci_movie_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto interm4_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm4_trie0, interm4_col1);
		string mn_n_name = "zzzzzzzz";
		string mn_interm4_col2 = "zzzzzzzz";
		string mn_interm4_col4 = "zzzzzzzz";
		string mn_interm4_col6 = "zzzzzzzz";
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (n_trie0.contains(x0)) {
				auto &n_trie1 = n_trie0.at(x0);
				for (const auto &[x1, ci_trie2]: ci_trie1) {
					if (interm4_trie0.contains(x1)) {
						auto &interm4_trie1 = interm4_trie0.at(x1);
						for (const auto &n_off: n_trie1) {
							mn_n_name = min(mn_n_name, n_name[n_off]);
						}
						for (const auto &interm4_off: interm4_trie1) {
							mn_interm4_col2 = min(mn_interm4_col2, interm4_col2[interm4_off]);
							mn_interm4_col4 = min(mn_interm4_col4, interm4_col4[interm4_off]);
							mn_interm4_col6 = min(mn_interm4_col6, interm4_col6[interm4_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		if (z == 0)
			cout << mn_n_name << " | " << mn_interm4_col2 << " | " << mn_interm4_col4 << " | " << mn_interm4_col6 << endl;
		cerr << "*" << " " << flush;
	}
	cerr << endl;

	vector<double> tm{0};
	for (int i = 0; i < 6; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 6; ++i)
		cout << tm[i + 1] - tm[i] << " ms" << endl;
	cout << tm[6] << " ms" << endl;
}
