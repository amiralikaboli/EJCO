#include <iostream>
#include <limits>
#include "load/20b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20b/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20b/cct2.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20b/t.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20b/kt.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20b/k.csv");
	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20b/n.csv");
	load_chn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20b/chn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> cc_trie0 = {0, cc_offsets.size() - 1};
		pair<int, int> cct1_trie0 = {0, cct1_offsets.size() - 1};
		pair<int, int> cct2_trie0 = {0, cct2_offsets.size() - 1};
		build_trie(cct1_offsets, cct1_id);
		build_trie(cct2_offsets, cct2_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_col2;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int cc_i = cc_trie0.first; cc_i <= cc_trie0.second; ++cc_i) {
			const auto &cc_off = cc_offsets[cc_i];
			auto x0 = cc_subject_id[cc_off];
			auto cct1_trie1 = find_range(cct1_offsets, cct1_id, x0, cct1_trie0);
			if (cct1_trie1.first != -1) {
				auto x1 = cc_status_id[cc_off];
				auto cct2_trie1 = find_range(cct2_offsets, cct2_id, x1, cct2_trie0);
				if (cct2_trie1.first != -1) {
					interm0_col0.push_back(cc_subject_id[cc_off]);
					interm0_col1.push_back(cc_status_id[cc_off]);
					interm0_col2.push_back(cc_movie_id[cc_off]);
					interm0_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> mk_trie0 = {0, mk_offsets.size() - 1};
		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> kt_trie0 = {0, kt_offsets.size() - 1};
		pair<int, int> k_trie0 = {0, k_offsets.size() - 1};
		build_trie(t_offsets, t_id);
		build_trie(kt_offsets, kt_id);
		build_trie(k_offsets, k_id);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<int> interm1_col2;
		vector<string> interm1_col3;
		vector<int> interm1_offsets;
		cnt = 0;
		for (int mk_i = mk_trie0.first; mk_i <= mk_trie0.second; ++mk_i) {
			const auto &mk_off = mk_offsets[mk_i];
			auto x0 = mk_movie_id[mk_off];
			auto t_trie1 = find_range(t_offsets, t_id, x0, t_trie0);
			if (t_trie1.first != -1) {
				for (int t_i = t_trie1.first; t_i <= t_trie1.second; ++t_i) {
					const auto &t_off = t_offsets[t_i];
					auto x1 = t_kind_id[t_off];
					auto kt_trie1 = find_range(kt_offsets, kt_id, x1, kt_trie0);
					if (kt_trie1.first != -1) {
						auto x2 = mk_keyword_id[mk_off];
						auto k_trie1 = find_range(k_offsets, k_id, x2, k_trie0);
						if (k_trie1.first != -1) {
							interm1_col0.push_back(mk_movie_id[mk_off]);
							interm1_col1.push_back(mk_keyword_id[mk_off]);
							interm1_col2.push_back(t_kind_id[t_off]);
							interm1_col3.push_back(t_title[t_off]);
							interm1_offsets.push_back(cnt++);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		pair<int, int> ci_trie0 = {0, ci_offsets.size() - 1};
		pair<int, int> n_trie0 = {0, n_offsets.size() - 1};
		pair<int, int> interm1_trie0 = {0, interm1_offsets.size() - 1};
		pair<int, int> chn_trie0 = {0, chn_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		build_trie(n_offsets, n_id);
		build_trie(chn_offsets, chn_id);
		build_trie(interm1_offsets, interm1_col0);
		build_trie(interm0_offsets, interm0_col2);
		timer.StoreElapsedTime(4);

		string mn_interm1_col3 = "zzzzzzzz";
		for (int ci_i = ci_trie0.first; ci_i <= ci_trie0.second; ++ci_i) {
			const auto &ci_off = ci_offsets[ci_i];
			auto x0 = ci_person_id[ci_off];
			auto n_trie1 = find_range(n_offsets, n_id, x0, n_trie0);
			if (n_trie1.first != -1) {
				auto x1 = ci_person_role_id[ci_off];
				auto chn_trie1 = find_range(chn_offsets, chn_id, x1, chn_trie0);
				if (chn_trie1.first != -1) {
					auto x2 = ci_movie_id[ci_off];
					auto interm1_trie1 = find_range(interm1_offsets, interm1_col0, x2, interm1_trie0);
					auto interm0_trie1 = find_range(interm0_offsets, interm0_col2, x2, interm0_trie0);
					if (interm1_trie1.first != -1 && interm0_trie1.first != -1) {
						for (int interm1_i = interm1_trie1.first; interm1_i <= interm1_trie1.second; ++interm1_i) {
							const auto &interm1_off = interm1_offsets[interm1_i];
							mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		if (z == 0)
			cout << mn_interm1_col3 << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 3; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 3; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 3] << " ms" << endl;
}
