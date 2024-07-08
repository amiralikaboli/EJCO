#include <iostream>
#include <limits>
#include "load/32b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_t1("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_t2("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_lt("/Users/s2522996/Documents/free-join/data/imdb_csv/link_type.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/32b/k.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		auto ml_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(ml_trie0, ml_movie_id);
		auto t2_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t2_trie0, t2_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<string> interm0_col1;
		vector<int> interm0_col2;
		vector<int> interm0_col3;
		vector<string> interm0_col4;
		vector<int> interm0_offsets;
		cnt = 0;
		for (const auto &t1_off: t1_offsets) {
			auto x0 = t1_id[t1_off];
			if (ml_trie0.contains(x0)) {
				auto &ml_trie1 = ml_trie0.at(x0);
				for (const auto &ml_off: ml_trie1) {
					auto x1 = ml_linked_movie_id[ml_off];
					if (t2_trie0.contains(x1)) {
						auto &t2_trie1 = t2_trie0.at(x1);
						for (const auto &t2_off: t2_trie1) {
							interm0_col0.push_back(t1_id[t1_off]);
							interm0_col1.push_back(t1_title[t1_off]);
							interm0_col2.push_back(ml_linked_movie_id[ml_off]);
							interm0_col3.push_back(ml_link_type_id[ml_off]);
							interm0_col4.push_back(t2_title[t2_off]);
							interm0_offsets.push_back(cnt++);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col0);
		auto lt_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(lt_trie0, lt_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(k_trie0, k_id);
		timer.StoreElapsedTime(2);

		string mn_interm0_col1 = "zzzzzzzz";
		string mn_interm0_col4 = "zzzzzzzz";
		string mn_lt_link = "zzzzzzzz";
		for (const auto &mk_off: mk_offsets) {
			auto x0 = mk_movie_id[mk_off];
			if (interm0_trie0.contains(x0)) {
				auto &interm0_trie1 = interm0_trie0.at(x0);
				for (const auto &interm0_off: interm0_trie1) {
					auto x1 = interm0_col3[interm0_off];
					if (lt_trie0.contains(x1)) {
						auto &lt_trie1 = lt_trie0.at(x1);
						auto x2 = mk_keyword_id[mk_off];
						if (k_trie0.contains(x2)) {
							auto &k_trie1 = k_trie0.at(x2);
							mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
							mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
							for (const auto &lt_off: lt_trie1) {
								mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		if (z == 0)
			cout << mn_interm0_col1 << " | " << mn_interm0_col4 << " | " << mn_lt_link << endl;
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
