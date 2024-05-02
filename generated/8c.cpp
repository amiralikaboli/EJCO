#include <iostream>
#include "8c_load.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n1("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8c/cn.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8c/rt.csv");
	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_a1("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
		build_trie(ci_trie0, ci_person_id, ci_movie_id, ci_role_id);
		auto n1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n1_trie0, n1_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mc_trie0, mc_company_id, mc_movie_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		auto rt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(rt_trie0, rt_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto a1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(a1_trie0, a1_person_id);
		timer.StoreElapsedTime(0);

		vector<tuple<int, int, int, int, string, string>> res;
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (n1_trie0.contains(x0)) {
				auto &n1_trie1 = n1_trie0.at(x0);
				for (const auto &[x1, mc_trie1]: mc_trie0) {
					if (cn_trie0.contains(x1)) {
						auto &cn_trie1 = cn_trie0.at(x1);
						for (const auto &[x2, ci_trie2]: ci_trie1) {
							if (mc_trie1.contains(x2)) {
								auto &mc_trie2 = mc_trie1.at(x2);
								for (const auto &[x3, ci_trie3]: ci_trie2) {
									if (rt_trie0.contains(x3)) {
										auto &rt_trie1 = rt_trie0.at(x3);
										if (t_trie0.contains(x2)) {
											auto &t_trie1 = t_trie0.at(x2);
											if (a1_trie0.contains(x0)) {
												auto &a1_trie1 = a1_trie0.at(x0);
												for (const auto &ci_off: ci_trie3) {
													for (const auto &n1_off: n1_trie1) {
														for (const auto &mc_off: mc_trie2) {
															for (const auto &cn_off: cn_trie1) {
																for (const auto &rt_off: rt_trie1) {
																	for (const auto &t_off: t_trie1) {
																		for (const auto &a1_off: a1_trie1) {
																			res.push_back({x0, x1, x2, x3, t_title[t_off], a1_name[a1_off]});
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
			}
		}
		timer.StoreElapsedTime(1);
		cerr << "*" << " ";
		if (z == 0)
			cout << res.size() << endl;
	}

	cerr << endl;
	cout << timer.GetMean(0) << " ms" << endl;
	cout << timer.GetMean(1) << " ms" << endl;
}
