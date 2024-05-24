#include <iostream>
#include <limits>
#include "load/10a.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/10a/ci.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/10a/rt.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/10a/t.csv");
	load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/10a/cn.csv");
	load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(ci_trie0, ci_role_id, ci_movie_id, ci_person_role_id);
		auto rt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(rt_trie0, rt_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(mc_trie0, mc_movie_id, mc_company_type_id, mc_company_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(ct_trie0, ct_id);
		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cn_trie0, cn_id);
		auto chn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(chn_trie0, chn_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzzzzz";
		string mn_chn_name = "zzzzzzzz";
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (mc_trie0.contains(x0)) {
				auto &mc_trie1 = mc_trie0.at(x0);
				for (const auto &[x1, mc_trie2]: mc_trie1) {
					if (ct_trie0.contains(x1)) {
						auto &ct_trie1 = ct_trie0.at(x1);
						for (const auto &[x2, mc_trie3]: mc_trie2) {
							if (cn_trie0.contains(x2)) {
								auto &cn_trie1 = cn_trie0.at(x2);
								for (const auto &[x3, rt_trie1]: rt_trie0) {
									if (ci_trie0.contains(x3)) {
										auto &ci_trie1 = ci_trie0.at(x3);
										if (ci_trie1.contains(x0)) {
											auto &ci_trie2 = ci_trie1.at(x0);
											for (const auto &[x5, ci_trie3]: ci_trie2) {
												if (chn_trie0.contains(x5)) {
													auto &chn_trie1 = chn_trie0.at(x5);
													for (const auto &t_off: t_trie1) {
														mn_t_title = min(mn_t_title, t_title[t_off]);
													}
													for (const auto &chn_off: chn_trie1) {
														mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
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
			cout << mn_t_title << " | " << mn_chn_name << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
