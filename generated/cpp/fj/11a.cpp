#include <iostream>
#include <limits>
#include "load/11a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/t.csv");
	load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/mc.csv");
	load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/lt.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/k.csv");
	load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/ct.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/cn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		pair<int, int> t_trie0 = {0, t_offsets.size() - 1};
		pair<int, int> ml_trie0 = {0, ml_offsets.size() - 1};
		build_trie(ml_offsets, ml_movie_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<string> interm0_col1;
		vector<int> interm0_col2;
		vector<int> interm0_offsets;
		cnt = 0;
		for (int t_i = t_trie0.first; t_i <= t_trie0.second; ++t_i) {
			const auto &t_off = t_offsets[t_i];
			auto x0 = t_id[t_off];
			auto ml_trie1 = find_range(ml_offsets, ml_movie_id, x0, ml_trie0);
			if (ml_trie1.first != -1) {
				for (int ml_i = ml_trie1.first; ml_i <= ml_trie1.second; ++ml_i) {
					const auto &ml_off = ml_offsets[ml_i];
					interm0_col0.push_back(t_id[t_off]);
					interm0_col1.push_back(t_title[t_off]);
					interm0_col2.push_back(ml_link_type_id[ml_off]);
					interm0_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(1);

		pair<int, int> mk_trie0 = {0, mk_offsets.size() - 1};
		pair<int, int> interm0_trie0 = {0, interm0_offsets.size() - 1};
		pair<int, int> mc_trie0 = {0, mc_offsets.size() - 1};
		pair<int, int> lt_trie0 = {0, lt_offsets.size() - 1};
		pair<int, int> k_trie0 = {0, k_offsets.size() - 1};
		pair<int, int> ct_trie0 = {0, ct_offsets.size() - 1};
		pair<int, int> cn_trie0 = {0, cn_offsets.size() - 1};
		build_trie(interm0_offsets, interm0_col0);
		build_trie(mc_offsets, mc_movie_id);
		build_trie(lt_offsets, lt_id);
		build_trie(k_offsets, k_id);
		build_trie(ct_offsets, ct_id);
		build_trie(cn_offsets, cn_id);
		timer.StoreElapsedTime(2);

		string mn_interm0_col1 = "zzzzzzzz";
		string mn_lt_link = "zzzzzzzz";
		string mn_cn_name = "zzzzzzzz";
		for (int mk_i = mk_trie0.first; mk_i <= mk_trie0.second; ++mk_i) {
			const auto &mk_off = mk_offsets[mk_i];
			auto x0 = mk_movie_id[mk_off];
			auto interm0_trie1 = find_range(interm0_offsets, interm0_col0, x0, interm0_trie0);
			auto mc_trie1 = find_range(mc_offsets, mc_movie_id, x0, mc_trie0);
			if (interm0_trie1.first != -1 && mc_trie1.first != -1) {
				for (int interm0_i = interm0_trie1.first; interm0_i <= interm0_trie1.second; ++interm0_i) {
					const auto &interm0_off = interm0_offsets[interm0_i];
					auto x1 = interm0_col2[interm0_off];
					auto lt_trie1 = find_range(lt_offsets, lt_id, x1, lt_trie0);
					if (lt_trie1.first != -1) {
						auto x2 = mk_keyword_id[mk_off];
						auto k_trie1 = find_range(k_offsets, k_id, x2, k_trie0);
						if (k_trie1.first != -1) {
							for (int mc_i = mc_trie1.first; mc_i <= mc_trie1.second; ++mc_i) {
								const auto &mc_off = mc_offsets[mc_i];
								auto x3 = mc_company_type_id[mc_off];
								auto ct_trie1 = find_range(ct_offsets, ct_id, x3, ct_trie0);
								if (ct_trie1.first != -1) {
									auto x4 = mc_company_id[mc_off];
									auto cn_trie1 = find_range(cn_offsets, cn_id, x4, cn_trie0);
									if (cn_trie1.first != -1) {
										mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
										for (int lt_i = lt_trie1.first; lt_i <= lt_trie1.second; ++lt_i) {
											const auto &lt_off = lt_offsets[lt_i];
											mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
										}
										for (int cn_i = cn_trie1.first; cn_i <= cn_trie1.second; ++cn_i) {
											const auto &cn_off = cn_offsets[cn_i];
											mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
										}
									}
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(3);

		if (z == 0)
			cout << mn_interm0_col1 << " | " << mn_lt_link << " | " << mn_cn_name << endl;
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
