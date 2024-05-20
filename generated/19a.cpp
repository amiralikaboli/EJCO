#include <iostream>
#include <limits>
#include "load/19a.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/ci.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/rt.csv");
	load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/n.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/mi.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/mc.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/it.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/19a/cn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>>();
		build_trie_bool(ci_trie0, ci_role_id, ci_person_role_id, ci_person_id, ci_movie_id);
		auto rt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(rt_trie0, rt_id);
		auto chn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(chn_trie0, chn_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto an_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(an_trie0, an_person_id);
		auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mi_trie0, mi_movie_id, mi_info_type_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mc_trie0, mc_movie_id, mc_company_id);
		auto it_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it_trie0, it_id);
		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

		string mn_n_name = "zzzzzzzz";
		string mn_t_title = "zzzzzzzz";
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (t_trie0.contains(x0) && mc_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				auto &mc_trie1 = mc_trie0.at(x0);
				for (const auto &[x1, mi_trie2]: mi_trie1) {
					if (it_trie0.contains(x1)) {
						auto &it_trie1 = it_trie0.at(x1);
						for (const auto &[x2, mc_trie2]: mc_trie1) {
							if (cn_trie0.contains(x2)) {
								auto &cn_trie1 = cn_trie0.at(x2);
								for (const auto &[x3, n_trie1]: n_trie0) {
									if (an_trie0.contains(x3)) {
										auto &an_trie1 = an_trie0.at(x3);
										for (const auto &[x4, ci_trie1]: ci_trie0) {
											if (rt_trie0.contains(x4)) {
												auto &rt_trie1 = rt_trie0.at(x4);
												for (const auto &[x5, ci_trie2]: ci_trie1) {
													if (chn_trie0.contains(x5)) {
														auto &chn_trie1 = chn_trie0.at(x5);
														if (ci_trie2.contains(x3)) {
															auto &ci_trie3 = ci_trie2.at(x3);
															if (ci_trie3.contains(x0)) {
																auto &ci_trie4 = ci_trie3.at(x0);
																for (const auto &n_off: n_trie1) {
																	mn_n_name = min(mn_n_name, n_name[n_off]);
																}
																for (const auto &t_off: t_trie1) {
																	mn_t_title = min(mn_t_title, t_title[t_off]);
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
		}
		timer.StoreElapsedTime(1);
		if (z == 0)
			cout << mn_n_name << " | " << mn_t_title << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
