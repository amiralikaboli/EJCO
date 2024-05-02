#include <iostream>
#include "load/16a.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16a/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16a/k.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16a/cn.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(ci_trie0, ci_person_id, ci_movie_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		auto an_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(an_trie0, an_person_id);
		timer.StoreElapsedTime(0);

		vector<tuple<int, int, int, int, string, string>> res;
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (n_trie0.contains(x0)) {
				auto &n_trie1 = n_trie0.at(x0);
				for (const auto &[x1, mk_trie1]: mk_trie0) {
					if (t_trie0.contains(x1) && mc_trie0.contains(x1)) {
						auto &t_trie1 = t_trie0.at(x1);
						auto &mc_trie1 = mc_trie0.at(x1);
						for (const auto &[x2, mk_trie2]: mk_trie1) {
							if (k_trie0.contains(x2)) {
								auto &k_trie1 = k_trie0.at(x2);
								for (const auto &[x3, mc_trie2]: mc_trie1) {
									if (cn_trie0.contains(x3)) {
										auto &cn_trie1 = cn_trie0.at(x3);
										if (ci_trie1.contains(x1)) {
											auto &ci_trie2 = ci_trie1.at(x1);
											if (an_trie0.contains(x0)) {
												auto &an_trie1 = an_trie0.at(x0);
												for (const auto &ci_off: ci_trie2) {
													for (const auto &n_off: n_trie1) {
														for (const auto &mk_off: mk_trie2) {
															for (const auto &t_off: t_trie1) {
																for (const auto &mc_off: mc_trie2) {
																	for (const auto &k_off: k_trie1) {
																		for (const auto &cn_off: cn_trie1) {
																			for (const auto &an_off: an_trie1) {
																				res.push_back({x0, x1, x2, x3, t_title[t_off], an_name[an_off]});
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
