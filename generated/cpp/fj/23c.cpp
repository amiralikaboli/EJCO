#include <iostream>
#include <limits>
#include "load/23c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/cct1.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/t.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/kt.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/cn.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_k("/Users/s2522996/Documents/free-join/data/imdb_csv/keyword.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/mi.csv");
	load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/it1.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cct1_trie0, cct1_id);
		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_offsets;
		cnt = 0;
		for (const auto &cc_off: cc_offsets) {
			auto x0 = cc_status_id[cc_off];
			if (cct1_trie0.contains(x0)) {
				auto &cct1_trie1 = cct1_trie0.at(x0);
				interm0_col0.push_back(cc_status_id[cc_off]);
				interm0_col1.push_back(cc_movie_id[cc_off]);
				interm0_offsets.push_back(cnt++);
			}
		}
		timer.StoreElapsedTime(0);

		auto kt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(kt_trie0, kt_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(interm0_trie0, interm0_col1);
		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<string> interm1_col2;
		vector<string> interm1_col3;
		vector<int> interm1_offsets;
		cnt = 0;
		for (const auto &t_off: t_offsets) {
			auto x0 = t_kind_id[t_off];
			if (kt_trie0.contains(x0)) {
				auto &kt_trie1 = kt_trie0.at(x0);
				auto x1 = t_id[t_off];
				if (interm0_trie0.contains(x1)) {
					auto &interm0_trie1 = interm0_trie0.at(x1);
					for (const auto &kt_off: kt_trie1) {
						interm1_col0.push_back(t_kind_id[t_off]);
						interm1_col1.push_back(t_id[t_off]);
						interm1_col2.push_back(t_title[t_off]);
						interm1_col3.push_back(kt_kind[kt_off]);
						interm1_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(ct_trie0, ct_id);
		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col1);
		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cn_trie0, cn_id);
		vector<int> interm2_col0;
		vector<int> interm2_col1;
		vector<int> interm2_col2;
		vector<string> interm2_col4;
		vector<string> interm2_col5;
		vector<int> interm2_offsets;
		cnt = 0;
		for (const auto &mc_off: mc_offsets) {
			auto x0 = mc_company_type_id[mc_off];
			if (ct_trie0.contains(x0)) {
				auto &ct_trie1 = ct_trie0.at(x0);
				auto x1 = mc_movie_id[mc_off];
				if (interm1_trie0.contains(x1)) {
					auto &interm1_trie1 = interm1_trie0.at(x1);
					auto x2 = mc_company_id[mc_off];
					if (cn_trie0.contains(x2)) {
						auto &cn_trie1 = cn_trie0.at(x2);
						for (const auto &interm1_off: interm1_trie1) {
							interm2_col0.push_back(mc_company_type_id[mc_off]);
							interm2_col1.push_back(mc_company_id[mc_off]);
							interm2_col2.push_back(mc_movie_id[mc_off]);
							interm2_col4.push_back(interm1_col2[interm1_off]);
							interm2_col5.push_back(interm1_col3[interm1_off]);
							interm2_offsets.push_back(cnt++);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(2);

		auto interm2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm2_trie0, interm2_col2);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(k_trie0, k_id);
		vector<int> interm3_col0;
		vector<int> interm3_col1;
		vector<string> interm3_col5;
		vector<string> interm3_col6;
		vector<int> interm3_offsets;
		cnt = 0;
		for (const auto &mk_off: mk_offsets) {
			auto x0 = mk_movie_id[mk_off];
			if (interm2_trie0.contains(x0)) {
				auto &interm2_trie1 = interm2_trie0.at(x0);
				auto x1 = mk_keyword_id[mk_off];
				if (k_trie0.contains(x1)) {
					auto &k_trie1 = k_trie0.at(x1);
					for (const auto &interm2_off: interm2_trie1) {
						interm3_col0.push_back(mk_keyword_id[mk_off]);
						interm3_col1.push_back(mk_movie_id[mk_off]);
						interm3_col5.push_back(interm2_col4[interm2_off]);
						interm3_col6.push_back(interm2_col5[interm2_off]);
						interm3_offsets.push_back(cnt++);
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		auto it1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(it1_trie0, it1_id);
		auto interm3_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm3_trie0, interm3_col1);
		string mn_interm3_col5 = "zzzzzzzz";
		string mn_interm3_col6 = "zzzzzzzz";
		for (const auto &mi_off: mi_offsets) {
			auto x0 = mi_info_type_id[mi_off];
			if (it1_trie0.contains(x0)) {
				auto &it1_trie1 = it1_trie0.at(x0);
				auto x1 = mi_movie_id[mi_off];
				if (interm3_trie0.contains(x1)) {
					auto &interm3_trie1 = interm3_trie0.at(x1);
					for (const auto &interm3_off: interm3_trie1) {
						mn_interm3_col5 = min(mn_interm3_col5, interm3_col5[interm3_off]);
						mn_interm3_col6 = min(mn_interm3_col6, interm3_col6[interm3_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(4);

		if (z == 0)
			cout << mn_interm3_col5 << " | " << mn_interm3_col6 << endl;
		cerr << "*" << " " << flush;
	}
	cerr << endl;

	vector<double> tm{0};
	for (int i = 0; i < 5; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 5; ++i)
		cout << tm[i + 1] - tm[i] << " ms" << endl;
	cout << tm[5] << " ms" << endl;
}
