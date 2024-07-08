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

		pair<int, int> t1_trie0 = {0, t1_offsets.size() - 1};
		pair<int, int> ml_trie0 = {0, ml_offsets.size() - 1};
		pair<int, int> t2_trie0 = {0, t2_offsets.size() - 1};
		build_trie(ml_offsets, ml_movie_id);
		build_trie(t2_offsets, t2_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<string> interm0_col1;
		vector<int> interm0_col2;
		vector<int> interm0_col3;
		vector<string> interm0_col4;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int t1_i = t1_trie0.first; t1_i <= t1_trie0.second; ++t1_i) {
			const auto &t1_off = t1_offsets[t1_i];
			auto x0 = t1_id[t1_off];
			auto ml_trie1 = find_range(ml_offsets, ml_movie_id, x0, ml_trie0);
			if (ml_trie1.first != -1) {
				for (int ml_i = ml_trie1.first; ml_i <= ml_trie1.second; ++ml_i) {
					const auto &ml_off = ml_offsets[ml_i];
					auto x1 = ml_linked_movie_id[ml_off];
					auto t2_trie1 = find_range(t2_offsets, t2_id, x1, t2_trie0);
					if (t2_trie1.first != -1) {
						for (int t2_i = t2_trie1.first; t2_i <= t2_trie1.second; ++t2_i) {
							const auto &t2_off = t2_offsets[t2_i];
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

		pair<int, int> mk_trie0 = {0, mk_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		pair<int, int> lt_trie0 = {0, lt_offsets.size() - 1};
		pair<int, int> k_trie0 = {0, k_offsets.size() - 1};
		build_trie(interm0_offsets, interm0_col0);
		build_trie(lt_offsets, lt_id);
		build_trie(k_offsets, k_id);
		timer.StoreElapsedTime(2);

		string mn_interm0_col1 = "zzzzzzzz";
		string mn_interm0_col4 = "zzzzzzzz";
		string mn_lt_link = "zzzzzzzz";
		for (int mk_i = mk_trie0.first; mk_i <= mk_trie0.second; ++mk_i) {
			const auto &mk_off = mk_offsets[mk_i];
			auto x0 = mk_movie_id[mk_off];
			auto interm0_trie1 = find_range(interm0_offsets, interm0_col0, x0, interm0_trie0);
			if (interm0_trie1.first != -1) {
				for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
					const auto &interm0_off = interm0_offsets[interm0_i];
					auto x1 = interm0_col3[interm0_off];
					auto lt_trie1 = find_range(lt_offsets, lt_id, x1, lt_trie0);
					if (lt_trie1.first != -1) {
						auto x2 = mk_keyword_id[mk_off];
						auto k_trie1 = find_range(k_offsets, k_id, x2, k_trie0);
						if (k_trie1.first != -1) {
							mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
							mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
							for (int lt_i = lt_trie1.first; lt_i <= lt_trie1.second; ++lt_i) {
								const auto &lt_off = lt_offsets[lt_i];
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
