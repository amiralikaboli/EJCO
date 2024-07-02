#include <iostream>
#include <limits>
#include "load/5c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/mi.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/t.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/mc.csv");
	load_it("/Users/s2522996/Documents/free-join/data/imdb_csv/info_type.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/ct.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(mc_trie0, mc_movie_id);
		auto it_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(it_trie0, it_id);
		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(ct_trie0, ct_id);
		string mn_t_title = "zzzzzzzz";
		for (const auto &mi_off: mi_offsets) {
			auto x0 = mi_movie_id[mi_off];
			if (t_trie0.contains(x0) && mc_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				auto &mc_trie1 = mc_trie0.at(x0);
				auto x1 = mi_info_type_id[mi_off];
				if (it_trie0.contains(x1)) {
					auto &it_trie1 = it_trie0.at(x1);
					for (const auto &mc_off: mc_trie1) {
						auto x2 = mc_company_type_id[mc_off];
						if (ct_trie0.contains(x2)) {
							auto &ct_trie1 = ct_trie0.at(x2);
							for (const auto &t_off: t_trie1) {
								mn_t_title = min(mn_t_title, t_title[t_off]);
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
