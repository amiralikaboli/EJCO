#include "load/17a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/17a/k.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/17a/cn.csv");
    load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/17a/n.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        auto t_trie0 = phmap::flat_hash_map<int, bool>(t_offsets.size());
        build_trie(t_trie0, t_id);
        unordered_multimap<int, int> mc_trie0(mc_offsets.size());
        build_trie(mc_trie0, mc_movie_id);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>(cn_offsets.size());
        build_trie(cn_trie0, cn_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<int> interm0_col2;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_keyword_id[mk_off];
            if (k_trie0.contains(x0)) {
                auto &k_trie1 = k_trie0.at(x0);
                auto x1 = mk_movie_id[mk_off];
                auto mc_range = mc_trie0.equal_range(x1);
                if (t_trie0.contains(x1) && mc_range.first != mc_range.second) {
                    auto &t_trie1 = t_trie0.at(x1);
                    for (auto mc_it = mc_range.first; mc_it != mc_range.second; ++mc_it) {
                        auto mc_off = mc_it->second;
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
        timer.StoreElapsedTime(1);

        auto interm0_trie0 = phmap::flat_hash_map<int, bool>(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col0);
        unordered_multimap<int, int> n_trie0(n_offsets.size());
        build_trie(n_trie0, n_id);
        timer.StoreElapsedTime(2);

        string mn_n_name = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_movie_id[ci_off];
            if (interm0_trie0.contains(x0)) {
                auto &interm0_trie1 = interm0_trie0.at(x0);
                auto x1 = ci_person_id[ci_off];
                auto n_range = n_trie0.equal_range(x1);
                if (n_range.first != n_range.second) {
                    for (auto n_it = n_range.first; n_it != n_range.second; ++n_it) {
                        auto n_off = n_it->second;
                        mn_n_name = min(mn_n_name, n_name[n_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_n_name << endl;
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
