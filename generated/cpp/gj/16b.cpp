#include <iostream>
#include <limits>
#include "load/16b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16b/k.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16b/cn.csv");
	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
	load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(k_trie0, k_id);
		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		vector<int> interm0_col3;
		for (const auto &[x0, mk_trie1]: mk_trie0) {
			if (t_trie0.contains(x0) && mc_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				auto &mc_trie1 = mc_trie0.at(x0);
				for (const auto &[x1, mk_trie2]: mk_trie1) {
					if (k_trie0.contains(x1)) {
						auto &k_trie1 = k_trie0.at(x1);
						for (const auto &[x2, mc_trie2]: mc_trie1) {
							if (cn_trie0.contains(x2)) {
								auto &cn_trie1 = cn_trie0.at(x2);
								for (const auto &mk_off: mk_trie2) {
									for (const auto &t_off: t_trie1) {
										for (const auto &mc_off: mc_trie2) {
											interm0_col0.push_back(mk_movie_id[mk_off]);
											interm0_col1.push_back(mk_keyword_id[mk_off]);
											interm0_col2.push_back(t_title[t_off]);
											interm0_col3.push_back(mc_company_id[mc_off]);
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

		auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie(ci_trie0, ci_person_id, ci_movie_id);
		auto n_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(n_trie0, n_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col0);
		auto an_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(an_trie0, an_person_id);
		timer.StoreElapsedTime(2);

		string mn_interm0_col2 = "zzzzzzzz";
		string mn_an_name = "zzzzzzzz";
		for (const auto &[x0, ci_trie1]: ci_trie0) {
			if (n_trie0.contains(x0)) {
				auto &n_trie1 = n_trie0.at(x0);
				for (const auto &[x1, ci_trie2]: ci_trie1) {
					if (interm0_trie0.contains(x1)) {
						auto &interm0_trie1 = interm0_trie0.at(x1);
						if (an_trie0.contains(x0)) {
							auto &an_trie1 = an_trie0.at(x0);
							for (const auto &interm0_off: interm0_trie1) {
								mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
							}
							for (const auto &an_off: an_trie1) {
								mn_an_name = min(mn_an_name, an_name[an_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		if (z == 0)
			cout << mn_interm0_col2 << " | " << mn_an_name << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 2; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 2; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 2] << " ms" << endl;
}
