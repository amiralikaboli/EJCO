#include <iostream>
#include <limits>
#include "load/8b.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8b/ci.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8b/n.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8b/mc.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8b/cn.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8b/rt.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8b/t.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(ci_trie0, ci_person_id, ci_movie_id, ci_role_id);
		auto n_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(n_trie0, n_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mc_trie0, mc_company_id, mc_movie_id);
		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cn_trie0, cn_id);
		auto rt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(rt_trie0, rt_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto an_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(an_trie0, an_person_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzzzzz";
		string mn_an_name = "zzzzzzzz";
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (n_trie0.contains(x0)) {
				auto &n_trie1 = n_trie0.at(x0);
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
											if (an_trie0.contains(x0)) {
												auto &an_trie1 = an_trie0.at(x0);
												for (const auto &t_off: t_trie1) {
													mn_t_title = min(mn_t_title, t_title[t_off]);
												}
												for (const auto &an_off: an_trie1) {
													mn_an_name = min(mn_an_name, an_name[an_off]);
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
			cout << mn_t_title << " | " << mn_an_name << endl;
	}
	cerr << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
