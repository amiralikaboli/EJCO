#include <iostream>
#include <limits>
#include "load/2d.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/2d/k.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/2d/cn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie(mk_trie0, mk_movie_id, mk_keyword_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
		build_trie(mc_trie0, mc_movie_id, mc_company_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(k_trie0, k_id);
		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cn_trie0, cn_id);
		string mn_t_title = "zzzzzzzz";
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
								for (const auto &t_off: t_trie1) {
									mn_t_title = min(mn_t_title, t_title[t_off]);
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(0);

		if (z == 0)
			cout << mn_t_title << endl;
		cerr << "*" << " " << flush;
	}
	cerr << endl;

	vector<double> tm{0};
	for (int i = 0; i < 1; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 1; ++i)
		cout << tm[i + 1] - tm[i] << " ms" << endl;
	cout << tm[1] << " ms" << endl;
}
