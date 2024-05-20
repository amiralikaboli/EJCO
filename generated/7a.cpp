#include <iostream>
#include <limits>
#include "load/7a.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/t.csv");
	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/lt.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/n.csv");
	load_pi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/pi.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/it.csv");
	load_an("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/an.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(ci_trie0, ci_movie_id, ci_person_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto ml_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(ml_trie0, ml_linked_movie_id, ml_link_type_id);
		auto lt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(lt_trie0, lt_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto pi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie_bool(pi_trie0, pi_person_id, pi_info_type_id);
		auto it_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it_trie0, it_id);
		auto an_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(an_trie0, an_person_id);
		timer.StoreElapsedTime(0);

		string mn_t_title = "zzzzzzzz";
		string mn_n_name = "zzzzzzzz";
		for (const auto &[x0, n_trie1]: n_trie0) {
			if (pi_trie0.contains(x0)) {
				auto &pi_trie1 = pi_trie0.at(x0);
				for (const auto &[x1, pi_trie2]: pi_trie1) {
					if (it_trie0.contains(x1)) {
						auto &it_trie1 = it_trie0.at(x1);
						for (const auto &[x2, t_trie1]: t_trie0) {
							if (ml_trie0.contains(x2)) {
								auto &ml_trie1 = ml_trie0.at(x2);
								for (const auto &[x3, ml_trie2]: ml_trie1) {
									if (lt_trie0.contains(x3)) {
										auto &lt_trie1 = lt_trie0.at(x3);
										if (ci_trie0.contains(x2)) {
											auto &ci_trie1 = ci_trie0.at(x2);
											if (ci_trie1.contains(x0) && an_trie0.contains(x0)) {
												auto &ci_trie2 = ci_trie1.at(x0);
												auto &an_trie1 = an_trie0.at(x0);
												for (const auto &t_off: t_trie1) {
													mn_t_title = min(mn_t_title, t_title[t_off]);
												}
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
		}
		timer.StoreElapsedTime(1);
		if (z == 0)
			cout << mn_t_title << " | " << mn_n_name << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	auto build_time = timer.GetMean(0);
	auto total_time = timer.GetMean(1);
	cout << build_time << " ms" << endl;
	cout << total_time - build_time << " ms" << endl;
	cout << total_time << " ms" << endl;
}
