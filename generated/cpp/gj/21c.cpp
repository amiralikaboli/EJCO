#include <iostream>
#include <limits>
#include "load/21c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/t.csv");
	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/mi.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/mc.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/lt.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/k.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/cn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto ml_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ml_trie0, ml_movie_id);
		vector<int> interm0_col0;
		vector<string> interm0_col1;
		vector<int> interm0_col2;
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (ml_trie0.contains(x0)) {
				auto &ml_trie1 = ml_trie0.at(x0);
				for (const auto &t_off: t_trie1) {
					for (const auto &ml_off: ml_trie1) {
						interm0_col0.push_back(t_id[t_off]);
						interm0_col1.push_back(t_title[t_off]);
						interm0_col2.push_back(ml_link_type_id[ml_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(0);

		auto mk_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(mk_trie0, mk_movie_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col0);
		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<string> interm1_col2;
		vector<int> interm1_col3;
		for (const auto &[x0, mk_trie1]: mk_trie0) {
			if (interm0_trie0.contains(x0)) {
				auto &interm0_trie1 = interm0_trie0.at(x0);
				for (const auto &mk_off: mk_trie1) {
					for (const auto &interm0_off: interm0_trie1) {
						interm1_col0.push_back(mk_movie_id[mk_off]);
						interm1_col1.push_back(mk_keyword_id[mk_off]);
						interm1_col2.push_back(interm0_col1[interm0_off]);
						interm1_col3.push_back(interm0_col2[interm0_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto mi_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(mi_trie0, mi_movie_id);
		auto interm1_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(interm1_trie0, interm1_col0, interm1_col3, interm1_col1);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_type_id, mc_company_id);
		auto lt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(lt_trie0, lt_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(k_trie0, k_id);
		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(ct_trie0, ct_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		string mn_interm1_col2 = "zzzzzzzz";
		string mn_lt_link = "zzzzzzzz";
		string mn_cn_name = "zzzzzzzz";
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (interm1_trie0.contains(x0) && mc_trie0.contains(x0)) {
				auto &interm1_trie1 = interm1_trie0.at(x0);
				auto &mc_trie1 = mc_trie0.at(x0);
				for (const auto &[x1, interm1_trie2]: interm1_trie1) {
					if (lt_trie0.contains(x1)) {
						auto &lt_trie1 = lt_trie0.at(x1);
						for (const auto &[x2, interm1_trie3]: interm1_trie2) {
							if (k_trie0.contains(x2)) {
								auto &k_trie1 = k_trie0.at(x2);
								for (const auto &[x3, mc_trie2]: mc_trie1) {
									if (ct_trie0.contains(x3)) {
										auto &ct_trie1 = ct_trie0.at(x3);
										for (const auto &[x4, mc_trie3]: mc_trie2) {
											if (cn_trie0.contains(x4)) {
												auto &cn_trie1 = cn_trie0.at(x4);
												for (const auto &interm1_off: interm1_trie3) {
													mn_interm1_col2 = min(mn_interm1_col2, interm1_col2[interm1_off]);
												}
												for (const auto &lt_off: lt_trie1) {
													mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
												}
												for (const auto &cn_off: cn_trie1) {
													mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
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
		timer.StoreElapsedTime(2);

		if (z == 0)
			cout << mn_interm1_col2 << " | " << mn_lt_link << " | " << mn_cn_name << endl;
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
