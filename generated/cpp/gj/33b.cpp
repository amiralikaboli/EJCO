#include <iostream>
#include <limits>
#include "load/33b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33b/lt.csv");
	load_mi_idx1("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33b/it1.csv");
	load_mi_idx2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33b/mi_idx2.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33b/it2.csv");
	load_t1("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_kt1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33b/kt1.csv");
	load_t2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33b/t2.csv");
	load_kt2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33b/kt2.csv");
	load_mc1("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/33b/cn1.csv");
	load_mc2("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn2("/Users/s2522996/Documents/free-join/data/imdb_csv/company_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ml_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ml_trie0, ml_link_type_id);
		auto lt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(lt_trie0, lt_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_col2;
		for (const auto &[x0, ml_trie1]: ml_trie0) {
			if (lt_trie0.contains(x0)) {
				auto &lt_trie1 = lt_trie0.at(x0);
				for (const auto &ml_off: ml_trie1) {
					interm0_col0.push_back(ml_link_type_id[ml_off]);
					interm0_col1.push_back(ml_movie_id[ml_off]);
					interm0_col2.push_back(ml_linked_movie_id[ml_off]);
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto mi_idx1_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx1_trie0, mi_idx1_info_type_id, mi_idx1_movie_id);
		auto it1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(it1_trie0, it1_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col1);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<string> interm1_col2;
		vector<int> interm1_col4;
		for (const auto &[x0, mi_idx1_trie1]: mi_idx1_trie0) {
			if (it1_trie0.contains(x0)) {
				auto &it1_trie1 = it1_trie0.at(x0);
				for (const auto &[x1, mi_idx1_trie2]: mi_idx1_trie1) {
					if (interm0_trie0.contains(x1)) {
						auto &interm0_trie1 = interm0_trie0.at(x1);
						for (const auto &mi_idx1_off: mi_idx1_trie2) {
							for (const auto &interm0_off: interm0_trie1) {
								interm1_col0.push_back(mi_idx1_info_type_id[mi_idx1_off]);
								interm1_col1.push_back(mi_idx1_movie_id[mi_idx1_off]);
								interm1_col2.push_back(mi_idx1_info[mi_idx1_off]);
								interm1_col4.push_back(interm0_col2[interm0_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		auto mi_idx2_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mi_idx2_trie0, mi_idx2_info_type_id, mi_idx2_movie_id);
		auto it2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(it2_trie0, it2_id);
		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col4);
		timer.StoreElapsedTime(4);

		vector<int> interm2_col0;
		vector<int> interm2_col1;
		vector<string> interm2_col2;
		vector<int> interm2_col4;
		vector<string> interm2_col5;
		for (const auto &[x0, mi_idx2_trie1]: mi_idx2_trie0) {
			if (it2_trie0.contains(x0)) {
				auto &it2_trie1 = it2_trie0.at(x0);
				for (const auto &[x1, mi_idx2_trie2]: mi_idx2_trie1) {
					if (interm1_trie0.contains(x1)) {
						auto &interm1_trie1 = interm1_trie0.at(x1);
						for (const auto &mi_idx2_off: mi_idx2_trie2) {
							for (const auto &interm1_off: interm1_trie1) {
								interm2_col0.push_back(mi_idx2_info_type_id[mi_idx2_off]);
								interm2_col1.push_back(mi_idx2_movie_id[mi_idx2_off]);
								interm2_col2.push_back(mi_idx2_info[mi_idx2_off]);
								interm2_col4.push_back(interm1_col1[interm1_off]);
								interm2_col5.push_back(interm1_col2[interm1_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		auto t1_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(t1_trie0, t1_kind_id, t1_id);
		auto kt1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(kt1_trie0, kt1_id);
		auto interm2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm2_trie0, interm2_col4);
		timer.StoreElapsedTime(6);

		vector<int> interm3_col0;
		vector<int> interm3_col1;
		vector<string> interm3_col2;
		vector<int> interm3_col4;
		vector<string> interm3_col5;
		vector<string> interm3_col7;
		for (const auto &[x0, t1_trie1]: t1_trie0) {
			if (kt1_trie0.contains(x0)) {
				auto &kt1_trie1 = kt1_trie0.at(x0);
				for (const auto &[x1, t1_trie2]: t1_trie1) {
					if (interm2_trie0.contains(x1)) {
						auto &interm2_trie1 = interm2_trie0.at(x1);
						for (const auto &t1_off: t1_trie2) {
							for (const auto &interm2_off: interm2_trie1) {
								interm3_col0.push_back(t1_kind_id[t1_off]);
								interm3_col1.push_back(t1_id[t1_off]);
								interm3_col2.push_back(t1_title[t1_off]);
								interm3_col4.push_back(interm2_col1[interm2_off]);
								interm3_col5.push_back(interm2_col2[interm2_off]);
								interm3_col7.push_back(interm2_col5[interm2_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(7);

		auto t2_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(t2_trie0, t2_kind_id, t2_id);
		auto kt2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(kt2_trie0, kt2_id);
		auto interm3_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm3_trie0, interm3_col4);
		timer.StoreElapsedTime(8);

		vector<int> interm4_col0;
		vector<int> interm4_col1;
		vector<string> interm4_col2;
		vector<int> interm4_col4;
		vector<string> interm4_col5;
		vector<string> interm4_col7;
		vector<string> interm4_col9;
		for (const auto &[x0, t2_trie1]: t2_trie0) {
			if (kt2_trie0.contains(x0)) {
				auto &kt2_trie1 = kt2_trie0.at(x0);
				for (const auto &[x1, t2_trie2]: t2_trie1) {
					if (interm3_trie0.contains(x1)) {
						auto &interm3_trie1 = interm3_trie0.at(x1);
						for (const auto &t2_off: t2_trie2) {
							for (const auto &interm3_off: interm3_trie1) {
								interm4_col0.push_back(t2_kind_id[t2_off]);
								interm4_col1.push_back(t2_id[t2_off]);
								interm4_col2.push_back(t2_title[t2_off]);
								interm4_col4.push_back(interm3_col1[interm3_off]);
								interm4_col5.push_back(interm3_col2[interm3_off]);
								interm4_col7.push_back(interm3_col5[interm3_off]);
								interm4_col9.push_back(interm3_col7[interm3_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(9);

		auto mc1_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mc1_trie0, mc1_company_id, mc1_movie_id);
		auto cn1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn1_trie0, cn1_id);
		auto interm4_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm4_trie0, interm4_col4);
		timer.StoreElapsedTime(10);

		vector<int> interm5_col0;
		vector<int> interm5_col1;
		vector<string> interm5_col2;
		vector<int> interm5_col4;
		vector<string> interm5_col5;
		vector<string> interm5_col7;
		vector<string> interm5_col9;
		vector<string> interm5_col11;
		for (const auto &[x0, mc1_trie1]: mc1_trie0) {
			if (cn1_trie0.contains(x0)) {
				auto &cn1_trie1 = cn1_trie0.at(x0);
				for (const auto &[x1, mc1_trie2]: mc1_trie1) {
					if (interm4_trie0.contains(x1)) {
						auto &interm4_trie1 = interm4_trie0.at(x1);
						for (const auto &mc1_off: mc1_trie2) {
							for (const auto &cn1_off: cn1_trie1) {
								for (const auto &interm4_off: interm4_trie1) {
									interm5_col0.push_back(mc1_company_id[mc1_off]);
									interm5_col1.push_back(mc1_movie_id[mc1_off]);
									interm5_col2.push_back(cn1_name[cn1_off]);
									interm5_col4.push_back(interm4_col1[interm4_off]);
									interm5_col5.push_back(interm4_col2[interm4_off]);
									interm5_col7.push_back(interm4_col5[interm4_off]);
									interm5_col9.push_back(interm4_col7[interm4_off]);
									interm5_col11.push_back(interm4_col9[interm4_off]);
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(11);

		auto mc2_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie(mc2_trie0, mc2_company_id, mc2_movie_id);
		auto cn2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn2_trie0, cn2_id);
		auto interm5_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm5_trie0, interm5_col4);
		timer.StoreElapsedTime(12);

		string mn_cn2_name = "zzzzzzzz";
		string mn_interm5_col2 = "zzzzzzzz";
		string mn_interm5_col5 = "zzzzzzzz";
		string mn_interm5_col7 = "zzzzzzzz";
		string mn_interm5_col9 = "zzzzzzzz";
		string mn_interm5_col11 = "zzzzzzzz";
		for (const auto &[x0, mc2_trie1]: mc2_trie0) {
			if (cn2_trie0.contains(x0)) {
				auto &cn2_trie1 = cn2_trie0.at(x0);
				for (const auto &[x1, mc2_trie2]: mc2_trie1) {
					if (interm5_trie0.contains(x1)) {
						auto &interm5_trie1 = interm5_trie0.at(x1);
						for (const auto &cn2_off: cn2_trie1) {
							mn_cn2_name = min(mn_cn2_name, cn2_name[cn2_off]);
						}
						for (const auto &interm5_off: interm5_trie1) {
							mn_interm5_col2 = min(mn_interm5_col2, interm5_col2[interm5_off]);
							mn_interm5_col5 = min(mn_interm5_col5, interm5_col5[interm5_off]);
							mn_interm5_col7 = min(mn_interm5_col7, interm5_col7[interm5_off]);
							mn_interm5_col9 = min(mn_interm5_col9, interm5_col9[interm5_off]);
							mn_interm5_col11 = min(mn_interm5_col11, interm5_col11[interm5_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(13);

		if (z == 0)
			cout << mn_cn2_name << " | " << mn_interm5_col2 << " | " << mn_interm5_col5 << " | " << mn_interm5_col7 << " | " << mn_interm5_col9 << " | " << mn_interm5_col11 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 7; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 7; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 7] << " ms" << endl;
}
