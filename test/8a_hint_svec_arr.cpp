#include "../generated/cpp/fj/load/8a.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"
#include "../include/small_vector.h"
#include "../include/small_vector2.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8a/mc.csv");
	load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8a/cn.csv");
	load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8a/ci.csv");
	load_n1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8a/n1.csv");
	load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8a/rt.csv");
	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_an1("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int iter = 0; iter < 1 + 5; ++iter) {
		int cnt;
		string IVs;
		timer.Reset();

		auto cn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cn_trie0, cn_id);
		timer.StoreElapsedTime(0);

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

		auto rt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(rt_trie0, rt_id);
		auto n1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(n1_trie0, n1_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(interm0_trie0, interm0_col1);
		auto an1_trie0 = phmap::flat_hash_map<int, sv::small_vector<int, 4>>();
		build_trie<4>(an1_trie0, an1_person_id);
		timer.StoreElapsedTime(1);
		auto t_trie0 = phmap::flat_hash_map<int, small_vector_array<int, 4>>(t_id.size());
		build_trie<4>(t_trie0, t_id);
		timer.StoreElapsedTime(2);

		string mn_t_title = "zzzzzzzz";
		string mn_an1_name = "zzzzzzzz";
		for (const auto &ci_off: ci_offsets) {
			auto x0 = ci_role_id[ci_off];
			if (rt_trie0.contains(x0)) {
				auto &rt_trie1 = rt_trie0.at(x0);
				auto x1 = ci_person_id[ci_off];
				if (n1_trie0.contains(x1)) {
					auto &n1_trie1 = n1_trie0.at(x1);
					auto x2 = ci_movie_id[ci_off];
					if (interm0_trie0.contains(x2)) {
						auto &interm0_trie1 = interm0_trie0.at(x2);
						if (an1_trie0.contains(x1)) {
							auto &an1_trie1 = an1_trie0.at(x1);
							if (t_trie0.contains(x2)) {
								auto &t_trie1 = t_trie0.at(x2);
								for (int t_i = 0; t_i < t_trie1.size(); ++t_i) {
									mn_t_title = min(mn_t_title, t_title[t_trie1[t_i]]);
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
		timer.StoreElapsedTime(3);

		if (iter == 0) {
			cout << mn_t_title << " | " << mn_an1_name << endl;
			cout << IVs;
		}
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
