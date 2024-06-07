#include <iostream>
#include <limits>
#include "load/3c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3c/t.csv");
	load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3c/mi.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3c/k.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		timer.Reset();

		auto mk_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(mk_trie0, mk_movie_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<string> interm0_col2;
		for (const auto &[x0, mk_trie1]: mk_trie0) {
			if (t_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				for (const auto &mk_off: mk_trie1) {
					for (const auto &t_off: t_trie1) {
						interm0_col0.push_back(mk_movie_id[mk_off]);
						interm0_col1.push_back(mk_keyword_id[mk_off]);
						interm0_col2.push_back(t_title[t_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(0);

		auto mi_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(mi_trie0, mi_movie_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
		build_trie(interm0_trie0, interm0_col0, interm0_col1);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(k_trie0, k_id);
		string mn_interm0_col2 = "zzzzzzzz";
		for (const auto &[x0, mi_trie1]: mi_trie0) {
			if (interm0_trie0.contains(x0)) {
				auto &interm0_trie1 = interm0_trie0.at(x0);
				for (const auto &[x1, interm0_trie2]: interm0_trie1) {
					if (k_trie0.contains(x1)) {
						auto &k_trie1 = k_trie0.at(x1);
						for (const auto &interm0_off: interm0_trie2) {
							mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		if (z == 0)
			cout << mn_interm0_col2 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2; ++i)
		cout << tm[i + 1] - tm[i] << " ms" << endl;
	cout << tm[2] << " ms" << endl;
}
