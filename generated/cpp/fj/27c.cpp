#include <iostream>
#include <limits>
#include "load/27c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27c/lt.csv");
	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27c/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27c/cct2.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27c/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27c/mc.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27c/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27c/cn.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27c/k.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/27c/mi.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		auto lt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(lt_trie0, lt_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		vector<int> interm0_offsets;
		cnt = 0;
		for (const auto &ml_off: ml_offsets) {
			auto x0 = ml_link_type_id[ml_off];
			if (lt_trie0.contains(x0)) {
				auto &lt_trie1 = lt_trie0.at(x0);
				for (const auto &lt_off: lt_trie1) {
					interm0_col0.push_back(ml_link_type_id[ml_off]);
					interm0_col1.push_back(ml_movie_id[ml_off]);
					interm0_col2.push_back(lt_link[lt_off]);
					interm0_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cct1_trie0, cct1_id);
		auto cct2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cct2_trie0, cct2_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col1);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<int> interm1_col2;
		vector<string> interm1_col4;
		vector<int> interm1_offsets;
		cnt = 0;
		for (const auto &cc_off: cc_offsets) {
			auto x0 = cc_subject_id[cc_off];
			if (cct1_trie0.contains(x0)) {
				auto &cct1_trie1 = cct1_trie0.at(x0);
				auto x1 = cc_status_id[cc_off];
				if (cct2_trie0.contains(x1)) {
					auto &cct2_trie1 = cct2_trie0.at(x1);
					auto x2 = cc_movie_id[cc_off];
					if (interm0_trie0.contains(x2)) {
						auto &interm0_trie1 = interm0_trie0.at(x2);
						for (const auto &interm0_off: interm0_trie1) {
							interm1_col0.push_back(cc_subject_id[cc_off]);
							interm1_col1.push_back(cc_status_id[cc_off]);
							interm1_col2.push_back(cc_movie_id[cc_off]);
							interm1_col4.push_back(interm0_col2[interm0_off]);
							interm1_offsets.push_back(cnt++);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col2);
		timer.StoreElapsedTime(4);

		vector<int> interm2_col0;
		vector<string> interm2_col1;
		vector<string> interm2_col5;
		vector<int> interm2_offsets;
		cnt = 0;
		for (const auto &t_off: t_offsets) {
			auto x0 = t_id[t_off];
			if (interm1_trie0.contains(x0)) {
				auto &interm1_trie1 = interm1_trie0.at(x0);
				for (const auto &interm1_off: interm1_trie1) {
					interm2_col0.push_back(t_id[t_off]);
					interm2_col1.push_back(t_title[t_off]);
					interm2_col5.push_back(interm1_col4[interm1_off]);
					interm2_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(5);

		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(ct_trie0, ct_id);
		auto interm2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm2_trie0, interm2_col0);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		timer.StoreElapsedTime(6);

		vector<int> interm3_col0;
		vector<int> interm3_col1;
		vector<int> interm3_col2;
		vector<string> interm3_col3;
		vector<string> interm3_col4;
		vector<string> interm3_col8;
		vector<int> interm3_offsets;
		cnt = 0;
		for (const auto &mc_off: mc_offsets) {
			auto x0 = mc_company_type_id[mc_off];
			if (ct_trie0.contains(x0)) {
				auto &ct_trie1 = ct_trie0.at(x0);
				auto x1 = mc_movie_id[mc_off];
				if (interm2_trie0.contains(x1)) {
					auto &interm2_trie1 = interm2_trie0.at(x1);
					auto x2 = mc_company_id[mc_off];
					if (cn_trie0.contains(x2)) {
						auto &cn_trie1 = cn_trie0.at(x2);
						for (const auto &cn_off: cn_trie1) {
							for (const auto &interm2_off: interm2_trie1) {
								interm3_col0.push_back(mc_company_type_id[mc_off]);
								interm3_col1.push_back(mc_company_id[mc_off]);
								interm3_col2.push_back(mc_movie_id[mc_off]);
								interm3_col3.push_back(cn_name[cn_off]);
								interm3_col4.push_back(interm2_col1[interm2_off]);
								interm3_col8.push_back(interm2_col5[interm2_off]);
								interm3_offsets.push_back(cnt++);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(7);

		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(k_trie0, k_id);
		auto interm3_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm3_trie0, interm3_col2);
		timer.StoreElapsedTime(8);

		vector<int> interm4_col0;
		vector<int> interm4_col1;
		vector<string> interm4_col4;
		vector<string> interm4_col5;
		vector<string> interm4_col9;
		vector<int> interm4_offsets;
		cnt = 0;
		for (const auto &mk_off: mk_offsets) {
			auto x0 = mk_keyword_id[mk_off];
			if (k_trie0.contains(x0)) {
				auto &k_trie1 = k_trie0.at(x0);
				auto x1 = mk_movie_id[mk_off];
				if (interm3_trie0.contains(x1)) {
					auto &interm3_trie1 = interm3_trie0.at(x1);
					for (const auto &interm3_off: interm3_trie1) {
						interm4_col0.push_back(mk_keyword_id[mk_off]);
						interm4_col1.push_back(mk_movie_id[mk_off]);
						interm4_col4.push_back(interm3_col3[interm3_off]);
						interm4_col5.push_back(interm3_col4[interm3_off]);
						interm4_col9.push_back(interm3_col8[interm3_off]);
						interm4_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(9);

		auto interm4_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm4_trie0, interm4_col1);
		timer.StoreElapsedTime(10);

		string mn_interm4_col4 = "zzzzzzzz";
		string mn_interm4_col5 = "zzzzzzzz";
		string mn_interm4_col9 = "zzzzzzzz";
		for (const auto &mi_off: mi_offsets) {
			auto x0 = mi_movie_id[mi_off];
			if (interm4_trie0.contains(x0)) {
				auto &interm4_trie1 = interm4_trie0.at(x0);
				for (const auto &interm4_off: interm4_trie1) {
					mn_interm4_col4 = min(mn_interm4_col4, interm4_col4[interm4_off]);
					mn_interm4_col5 = min(mn_interm4_col5, interm4_col5[interm4_off]);
					mn_interm4_col9 = min(mn_interm4_col9, interm4_col9[interm4_off]);
				}
			}
		}
		timer.StoreElapsedTime(11);

		if (z == 0)
			cout << mn_interm4_col4 << " | " << mn_interm4_col5 << " | " << mn_interm4_col9 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 6; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 6; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 6] << " ms" << endl;
}
