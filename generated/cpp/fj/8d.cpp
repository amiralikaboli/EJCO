#include <iostream>
#include <limits>
#include "load/8d.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8d/cn.csv");
	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n1("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8d/rt.csv");
	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_an1("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(cn_trie0, cn_id);
		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_offsets;
		cnt = 0;
		for (const auto &mc_off: mc_offsets) {
			auto x0 = mc_company_id[mc_off];
			if (cn_trie0.contains(x0)) {
				auto &cn_trie1 = cn_trie0.at(x0);
				interm0_col0.push_back(mc_company_id[mc_off]);
				interm0_col1.push_back(mc_movie_id[mc_off]);
				interm0_offsets.push_back(cnt++);
			}
		}
		timer.StoreElapsedTime(0);

		auto n1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(n1_trie0, n1_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col1);
		auto rt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie_bool(rt_trie0, rt_id);
		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto an1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(an1_trie0, an1_person_id);
		string mn_t_title = "zzzzzzzz";
		string mn_an1_name = "zzzzzzzz";
		for (const auto &ci_off: ci_offsets) {
			auto x0 = ci_person_id[ci_off];
			if (n1_trie0.contains(x0)) {
				auto &n1_trie1 = n1_trie0.at(x0);
				auto x1 = ci_movie_id[ci_off];
				if (interm0_trie0.contains(x1)) {
					auto &interm0_trie1 = interm0_trie0.at(x1);
					auto x2 = ci_role_id[ci_off];
					if (rt_trie0.contains(x2)) {
						auto &rt_trie1 = rt_trie0.at(x2);
						if (t_trie0.contains(x1)) {
							auto &t_trie1 = t_trie0.at(x1);
							if (an1_trie0.contains(x0)) {
								auto &an1_trie1 = an1_trie0.at(x0);
								for (const auto &t_off: t_trie1) {
									mn_t_title = min(mn_t_title, t_title[t_off]);
								}
								for (const auto &an1_off: an1_trie1) {
									mn_an1_name = min(mn_an1_name, an1_name[an1_off]);
								}
							}
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		if (z == 0)
			cout << mn_t_title << " | " << mn_an1_name << endl;
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
