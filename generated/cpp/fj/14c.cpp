#include "load/14c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14c/t.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14c/mi_idx.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14c/mi.csv");
    load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14c/kt.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14c/k.csv");
    load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14c/it2.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/14c/it1.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        unordered_multimap<int, int> t_trie0(t_offsets.size());
        build_trie(t_trie0, t_id);
        unordered_multimap<int, int> mi_idx_trie0(mi_idx_offsets.size());
        build_trie(mi_idx_trie0, mi_idx_movie_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<int> interm0_col3;
        vector<int> interm0_col4;
        vector<string> interm0_col5;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_movie_id[mk_off];
            auto t_range = t_trie0.equal_range(x0);
            auto mi_idx_range = mi_idx_trie0.equal_range(x0);
            if (t_range.first != t_range.second && mi_idx_range.first != mi_idx_range.second) {
                for (auto t_it = t_range.first; t_it != t_range.second; ++t_it) {
                    auto t_off = t_it->second;
                    for (auto mi_idx_it = mi_idx_range.first; mi_idx_it != mi_idx_range.second; ++mi_idx_it) {
                        auto mi_idx_off = mi_idx_it->second;
                        interm0_col0.push_back(mk_movie_id[mk_off]);
                        interm0_col1.push_back(mk_keyword_id[mk_off]);
                        interm0_col2.push_back(t_title[t_off]);
                        interm0_col3.push_back(t_kind_id[t_off]);
                        interm0_col4.push_back(mi_idx_info_type_id[mi_idx_off]);
                        interm0_col5.push_back(mi_idx_info[mi_idx_off]);
                        interm0_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        unordered_multimap<int, int> interm0_trie0(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col0);
        auto kt_trie0 = phmap::flat_hash_map<int, bool>(kt_offsets.size());
        build_trie(kt_trie0, kt_id);
        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        auto it2_trie0 = phmap::flat_hash_map<int, bool>(it2_offsets.size());
        build_trie(it2_trie0, it2_id);
        auto it1_trie0 = phmap::flat_hash_map<int, bool>(it1_offsets.size());
        build_trie(it1_trie0, it1_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col2 = "zzzzzzzz";
        string mn_interm0_col5 = "zzzzzzzz";
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_movie_id[mi_off];
            auto interm0_range = interm0_trie0.equal_range(x0);
            if (interm0_range.first != interm0_range.second) {
                for (auto interm0_it = interm0_range.first; interm0_it != interm0_range.second; ++interm0_it) {
                    auto interm0_off = interm0_it->second;
                    auto x1 = interm0_col3[interm0_off];
                    if (kt_trie0.contains(x1)) {
                        auto &kt_trie1 = kt_trie0.at(x1);
                        auto x2 = interm0_col1[interm0_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            auto x3 = interm0_col4[interm0_off];
                            if (it2_trie0.contains(x3)) {
                                auto &it2_trie1 = it2_trie0.at(x3);
                                auto x4 = mi_info_type_id[mi_off];
                                if (it1_trie0.contains(x4)) {
                                    auto &it1_trie1 = it1_trie0.at(x4);
                                    mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                                    mn_interm0_col5 = min(mn_interm0_col5, interm0_col5[interm0_off]);
                                }
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_interm0_col2 << " | " << mn_interm0_col5 << endl;
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
