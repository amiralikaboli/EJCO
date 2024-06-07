#include <iostream>
#include <limits>
#include "load/1a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1a/mc.csv");
	load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1a/it.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1a/ct.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		auto mi_idx_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(mi_idx_trie0, mi_idx_movie_id);
		vector<int> interm0_col0;
		vector<string> interm0_col1;
		vector<int> interm0_col2;
		vector<int> interm0_col3;
		vector<int> interm0_offsets;
		cnt = 0;
		for (const auto &t_off: t_offsets) {
			auto x0 = t_id[t_off];
			if (mi_idx_trie0.contains(x0)) {
				auto &mi_idx_trie1 = mi_idx_trie0.at(x0);
				for (const auto &mi_idx_off: mi_idx_trie1) {
					interm0_col0.push_back(t_id[t_off]);
					interm0_col1.push_back(t_title[t_off]);
					interm0_col2.push_back(t_production_year[t_off]);
					interm0_col3.push_back(mi_idx_info_type_id[mi_idx_off]);
					interm0_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(0);

		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col0);
		auto it_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(it_trie0, it_id);
		auto ct_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(ct_trie0, ct_id);
		string mn_mc_note = "zzzzzzzz";
		string mn_interm0_col1 = "zzzzzzzz";
		int mn_interm0_col2 = numeric_limits<int>::max();
		for (const auto &mc_off: mc_offsets) {
			auto x0 = mc_movie_id[mc_off];
			if (interm0_trie0.contains(x0)) {
				auto &interm0_trie1 = interm0_trie0.at(x0);
				for (const auto &interm0_off: interm0_trie1) {
					auto x1 = interm0_col3[interm0_off];
					if (it_trie0.contains(x1)) {
						auto &it_trie1 = it_trie0.at(x1);
						auto x2 = mc_company_type_id[mc_off];
						if (ct_trie0.contains(x2)) {
							auto &ct_trie1 = ct_trie0.at(x2);
							mn_mc_note = min(mn_mc_note, mc_note[mc_off]);
							mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
							mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		if (z == 0)
			cout << mn_mc_note << " | " << mn_interm0_col1 << " | " << mn_interm0_col2 << endl;
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
