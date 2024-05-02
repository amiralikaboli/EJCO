#include <iostream>
#include "../include/load.h"
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

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(ci_trie0, ci_movie_id, ci_person_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto ml_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(ml_trie0, ml_linked_movie_id, ml_link_type_id);
		auto lt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(lt_trie0, lt_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto pi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(pi_trie0, pi_person_id, pi_info_type_id);
		auto it_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(it_trie0, it_id);
		auto an_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(an_trie0, an_person_id);
		timer.StoreElapsedTime(0);

		vector<tuple<int, int, int, int, string, string>> res;
		for (const auto &[x0, t_trie1]: t_trie0) {
			if (ml_trie0.contains(x0)) {
				auto &ml_trie1 = ml_trie0.at(x0);
				for (const auto &[x1, ml_trie2]: ml_trie1) {
					if (lt_trie0.contains(x1)) {
						auto &lt_trie1 = lt_trie0.at(x1);
						if (ci_trie0.contains(x0)) {
							auto &ci_trie1 = ci_trie0.at(x0);
							for (const auto &[x3, n_trie1]: n_trie0) {
								if (pi_trie0.contains(x3)) {
									auto &pi_trie1 = pi_trie0.at(x3);
									for (const auto &[x4, pi_trie2]: pi_trie1) {
										if (it_trie0.contains(x4)) {
											auto &it_trie1 = it_trie0.at(x4);
											if (ci_trie1.contains(x3) && an_trie0.contains(x3)) {
												auto &ci_trie2 = ci_trie1.at(x3);
												auto &an_trie1 = an_trie0.at(x3);
												for (const auto &ci_off: ci_trie2) {
													for (const auto &t_off: t_trie1) {
														for (const auto &ml_off: ml_trie2) {
															for (const auto &lt_off: lt_trie1) {
																for (const auto &n_off: n_trie1) {
																	for (const auto &pi_off: pi_trie2) {
																		for (const auto &it_off: it_trie1) {
																			for (const auto &an_off: an_trie1) {
																				res.push_back({x0, x1, x3, x4, t_title[t_off], n_name[n_off]});
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
