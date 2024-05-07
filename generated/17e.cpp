#include <iostream>
#include <limits>
#include "load/17e.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/17e/k.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/17e/cn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(ci_trie0, ci_person_id, ci_movie_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(mc_trie0, mc_movie_id, mc_company_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(k_trie0, k_id);
		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

		string mn_n_name = "zzzzzzzz";
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
											for (const auto &n_off: n_trie1) {
												mn_n_name = min(mn_n_name, n_name[n_off]);
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
			cout << mn_n_name << endl;
	}
	cerr << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
