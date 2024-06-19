#include <iostream>
#include <limits>
#include "load/17f.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/17f/k.csv");
	load_cn("/Users/s2522996/Documents/free-join/data/imdb_csv/company_name.csv");
	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/17f/n.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto mc_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(mc_trie0, mc_movie_id);
		auto k_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(k_trie0, k_id);
		auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(cn_trie0, cn_id);
		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_col2;
		vector<int> interm0_offsets;
		cnt = 0;
		for (const auto &mk_off: mk_offsets) {
			auto x0 = mk_movie_id[mk_off];
			if (t_trie0.contains(x0) && mc_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				auto &mc_trie1 = mc_trie0.at(x0);
				auto x1 = mk_keyword_id[mk_off];
				if (k_trie0.contains(x1)) {
					auto &k_trie1 = k_trie0.at(x1);
					for (const auto &mc_off: mc_trie1) {
						auto x2 = mc_company_id[mc_off];
						if (cn_trie0.contains(x2)) {
							auto &cn_trie1 = cn_trie0.at(x2);
							interm0_col0.push_back(mk_movie_id[mk_off]);
							interm0_col1.push_back(mk_keyword_id[mk_off]);
							interm0_col2.push_back(mc_company_id[mc_off]);
							interm0_offsets.push_back(cnt++);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(0);

		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm0_trie0, interm0_col0);
		string mn_n_name = "zzzzzzzz";
		for (const auto &ci_off: ci_offsets) {
			auto x0 = ci_person_id[ci_off];
			if (n_trie0.contains(x0)) {
				auto &n_trie1 = n_trie0.at(x0);
				auto x1 = ci_movie_id[ci_off];
				if (interm0_trie0.contains(x1)) {
					auto &interm0_trie1 = interm0_trie0.at(x1);
					for (const auto &n_off: n_trie1) {
						mn_n_name = min(mn_n_name, n_name[n_off]);
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		if (z == 0)
			cout << mn_n_name << endl;
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
