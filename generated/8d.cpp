#include <iostream>
#include <limits>
#include "load/8d.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n1("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8d/cn.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8d/rt.csv");
	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_an1("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
		build_trie_bool(ci_trie0, ci_person_id, ci_movie_id, ci_role_id);
		auto n1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(n1_trie0, n1_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mc_trie0, mc_company_id, mc_movie_id);
		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cn_trie0, cn_id);
		auto rt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(rt_trie0, rt_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto an1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(an1_trie0, an1_person_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzzzzz";
		string mn_an1_name = "zzzzzzzz";
		for (const auto &[x0, cn_trie1]: cn_trie0) {
			if (mc_trie0.contains(x0)) {
				auto &mc_trie1 = mc_trie0.at(x0);
				for (const auto &[x1, ci_trie1]: ci_trie0) {
					if (n1_trie0.contains(x1)) {
						auto &n1_trie1 = n1_trie0.at(x1);
						for (const auto &[x2, ci_trie2]: ci_trie1) {
							if (mc_trie1.contains(x2)) {
								auto &mc_trie2 = mc_trie1.at(x2);
								for (const auto &[x3, rt_trie1]: rt_trie0) {
									if (ci_trie2.contains(x3)) {
										auto &ci_trie3 = ci_trie2.at(x3);
										if (t_trie0.contains(x2)) {
											auto &t_trie1 = t_trie0.at(x2);
											if (an1_trie0.contains(x1)) {
												auto &an1_trie1 = an1_trie0.at(x1);
												for (const auto &t_off: t_trie1) {
													mn_t_title = min(mn_t_title, t_title[t_off]);
												}
												for (const auto &an1_off: an1_trie1) {
													mn_an1_name = min(mn_an1_name, an1_name[an1_off]);
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
			cout << mn_t_title << " | " << mn_an1_name << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
