#include <iostream>
#include <limits>
#include "load/20c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
	load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20c/cct1.csv");
	load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20c/cct2.csv");
	load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
	load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20c/t.csv");
	load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20c/kt.csv");
	load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20c/k.csv");
	load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
	load_n("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
	load_chn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/20c/chn.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int z = 0; z < 1 + 5; ++z) {
		int cnt;
		timer.Reset();

		auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cct1_trie0, cct1_id);
		auto cct2_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(cct2_trie0, cct2_id);
		timer.StoreElapsedTime(0);

		vector<int> interm0_col0;
		vector<int> interm0_col1;
		vector<int> interm0_col2;
		vector<int> interm0_offsets;
		cnt = 0;
		for (const auto &cc_off: cc_offsets) {
			auto x0 = cc_subject_id[cc_off];
			if (cct1_trie0.contains(x0)) {
				auto &cct1_trie1 = cct1_trie0.at(x0);
				auto x1 = cc_status_id[cc_off];
				if (cct2_trie0.contains(x1)) {
					auto &cct2_trie1 = cct2_trie0.at(x1);
					interm0_col0.push_back(cc_subject_id[cc_off]);
					interm0_col1.push_back(cc_status_id[cc_off]);
					interm0_col2.push_back(cc_movie_id[cc_off]);
					interm0_offsets.push_back(cnt++);
				}
			}
		}
		timer.StoreElapsedTime(1);

		auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(t_trie0, t_id);
		auto kt_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(kt_trie0, kt_id);
		auto k_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(k_trie0, k_id);
		timer.StoreElapsedTime(2);

		vector<int> interm1_col0;
		vector<int> interm1_col1;
		vector<int> interm1_col2;
		vector<string> interm1_col3;
		vector<int> interm1_offsets;
		cnt = 0;
		for (const auto &mk_off: mk_offsets) {
			auto x0 = mk_movie_id[mk_off];
			if (t_trie0.contains(x0)) {
				auto &t_trie1 = t_trie0.at(x0);
				for (const auto &t_off: t_trie1) {
					auto x1 = t_kind_id[t_off];
					if (kt_trie0.contains(x1)) {
						auto &kt_trie1 = kt_trie0.at(x1);
						auto x2 = mk_keyword_id[mk_off];
						if (k_trie0.contains(x2)) {
							auto &k_trie1 = k_trie0.at(x2);
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

		auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(interm1_trie0, interm1_col0);
		auto interm0_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(interm0_trie0, interm0_col2);
		auto chn_trie0 = phmap::flat_hash_map<int, bool>();
		build_trie(chn_trie0, chn_id);
		auto n_trie0 = phmap::flat_hash_map<int, vector<int>>();
		build_trie(n_trie0, n_id);
		timer.StoreElapsedTime(4);

		string mn_n_name = "zzzzzzzz";
		string mn_interm1_col3 = "zzzzzzzz";
		for (const auto &ci_off: ci_offsets) {
			auto x0 = ci_movie_id[ci_off];
			if (interm1_trie0.contains(x0) && interm0_trie0.contains(x0)) {
				auto &interm1_trie1 = interm1_trie0.at(x0);
				auto &interm0_trie1 = interm0_trie0.at(x0);
				auto x1 = ci_person_role_id[ci_off];
				if (chn_trie0.contains(x1)) {
					auto &chn_trie1 = chn_trie0.at(x1);
					auto x2 = ci_person_id[ci_off];
					if (n_trie0.contains(x2)) {
						auto &n_trie1 = n_trie0.at(x2);
						for (const auto &n_off: n_trie1) {
							mn_n_name = min(mn_n_name, n_name[n_off]);
						}
						for (const auto &interm1_off: interm1_trie1) {
							mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(5);

		if (z == 0)
			cout << mn_n_name << " | " << mn_interm1_col3 << endl;
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
