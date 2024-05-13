#include <iostream>
#include <limits>
#include "load/13b.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/t.csv");
	load_miidx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/kt.csv");
	load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/it2.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/it.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/cn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mi_trie0 = emhash6::HashMap<int, emhash6::HashMap<int, bool>>();
		build_trie_bool(mi_trie0, mi_movie_id, mi_info_type_id);
		auto t_trie0 = emhash6::HashMap<int, emhash6::HashMap<int, vector<int>>>();
		build_trie(t_trie0, t_id, t_kind_id);
		auto miidx_trie0 = emhash6::HashMap<int, emhash6::HashMap<int, vector<int>>>();
		build_trie(miidx_trie0, miidx_movie_id, miidx_info_type_id);
		auto mc_trie0 = emhash6::HashMap<int, emhash6::HashMap<int, emhash6::HashMap<int, bool>>>();
		build_trie_bool(mc_trie0, mc_movie_id, mc_company_type_id, mc_company_id);
		auto kt_trie0 = emhash6::HashMap<int, bool>();
		build_trie_bool(kt_trie0, kt_id);
		auto it2_trie0 = emhash6::HashMap<int, bool>();
		build_trie_bool(it2_trie0, it2_id);
		auto it_trie0 = emhash6::HashMap<int, bool>();
		build_trie_bool(it_trie0, it_id);
		auto ct_trie0 = emhash6::HashMap<int, bool>();
		build_trie_bool(ct_trie0, ct_id);
		auto cn_trie0 = emhash6::HashMap<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzzzzz";
		string mn_miidx_info = "zzzzzzzz";
		string mn_cn_name = "zzzzzzzz";
		for (const auto &[t_trie1, _, x0]: t_trie0) {
			if (miidx_trie0.contains(x0)) {
				auto &miidx_trie1 = miidx_trie0.at(x0);
				if (mi_trie0.contains(x0) && mc_trie0.contains(x0)) {
					auto &mi_trie1 = mi_trie0.at(x0);
					auto &mc_trie1 = mc_trie0.at(x0);
					for (const auto &[t_trie2, _, x2]: t_trie1) {
						if (kt_trie0.contains(x2)) {
							auto &kt_trie1 = kt_trie0.at(x2);
							for (const auto &[mi_trie2, _, x3]: mi_trie1) {
								if (it2_trie0.contains(x3)) {
									auto &it2_trie1 = it2_trie0.at(x3);
									for (const auto &[miidx_trie2, _, x4]: miidx_trie1) {
										if (it_trie0.contains(x4)) {
											auto &it_trie1 = it_trie0.at(x4);
											for (const auto &[mc_trie2, _, x5]: mc_trie1) {
												if (ct_trie0.contains(x5)) {
													auto &ct_trie1 = ct_trie0.at(x5);
													for (const auto &[mc_trie3, _, x6]: mc_trie2) {
														if (cn_trie0.contains(x6)) {
															auto &cn_trie1 = cn_trie0.at(x6);
															for (const auto &t_off: t_trie2) {
																mn_t_title = min(mn_t_title, t_title[t_off]);
															}
															for (const auto &miidx_off: miidx_trie2) {
																mn_miidx_info = min(mn_miidx_info, miidx_info[miidx_off]);
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
				}
			}
		}
		timer.StoreElapsedTime(1);
		if (z == 0)
			cout << mn_t_title << " | " << mn_miidx_info << " | " << mn_cn_name << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
