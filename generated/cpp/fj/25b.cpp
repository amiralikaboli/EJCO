#include "load/25b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/t.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/mi.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/k.csv");
    load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/it2.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/it1.csv");
    load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/ci.csv");
    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/25b/n.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto t_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(t_offsets.size());
        for (int i = 0; i < t_offsets.size(); ++i)
            t_trie0[t_id[i]][i] += 1;
        auto mi_idx_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(mi_idx_offsets.size());
        for (int i = 0; i < mi_idx_offsets.size(); ++i)
            mi_idx_trie0[mi_idx_movie_id[i]][i] += 1;
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<int> interm0_col3;
        vector<string> interm0_col4;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_movie_id[mk_off];
            if (t_trie0.contains(x0) && mi_idx_trie0.contains(x0)) {
                auto &t_trie1 = t_trie0.at(x0);
                auto &mi_idx_trie1 = mi_idx_trie0.at(x0);
                for (const auto &t_off : t_trie1) {
                    for (const auto &mi_idx_off : mi_idx_trie1) {
                        interm0_col0.push_back(mk_movie_id[mk_off]);
                        interm0_col1.push_back(mk_keyword_id[mk_off]);
                        interm0_col2.push_back(t_title[t_off]);
                        interm0_col3.push_back(mi_idx_info_type_id[mi_idx_off]);
                        interm0_col4.push_back(mi_idx_info[mi_idx_off]);
                        interm0_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto interm0_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(interm0_offsets.size());
        for (int i = 0; i < interm0_offsets.size(); ++i)
            interm0_trie0[interm0_col0[i]][i] += 1;
        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        for (int i = 0; i < k_offsets.size(); ++i)
            k_trie0[k_id[i]] += 1;
        auto it2_trie0 = phmap::flat_hash_map<int, bool>(it2_offsets.size());
        for (int i = 0; i < it2_offsets.size(); ++i)
            it2_trie0[it2_id[i]] += 1;
        auto it1_trie0 = phmap::flat_hash_map<int, bool>(it1_offsets.size());
        for (int i = 0; i < it1_offsets.size(); ++i)
            it1_trie0[it1_id[i]] += 1;
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<int> interm1_col1;
        vector<string> interm1_col2;
        vector<int> interm1_col3;
        vector<int> interm1_col4;
        vector<string> interm1_col5;
        vector<string> interm1_col6;
        vector<int> interm1_offsets;
        cnt = 0;
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_movie_id[mi_off];
            if (interm0_trie0.contains(x0)) {
                auto &interm0_trie1 = interm0_trie0.at(x0);
                for (const auto &interm0_off : interm0_trie1) {
                    auto x1 = interm0_col1[interm0_off];
                    if (k_trie0.contains(x1)) {
                        auto &k_trie1 = k_trie0.at(x1);
                        auto x2 = interm0_col3[interm0_off];
                        if (it2_trie0.contains(x2)) {
                            auto &it2_trie1 = it2_trie0.at(x2);
                            auto x3 = mi_info_type_id[mi_off];
                            if (it1_trie0.contains(x3)) {
                                auto &it1_trie1 = it1_trie0.at(x3);
                                interm1_col0.push_back(mi_movie_id[mi_off]);
                                interm1_col1.push_back(mi_info_type_id[mi_off]);
                                interm1_col2.push_back(mi_info[mi_off]);
                                interm1_col3.push_back(interm0_col1[interm0_off]);
                                interm1_col4.push_back(interm0_col3[interm0_off]);
                                interm1_col5.push_back(interm0_col2[interm0_off]);
                                interm1_col6.push_back(interm0_col4[interm0_off]);
                                interm1_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto interm1_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(interm1_offsets.size());
        for (int i = 0; i < interm1_offsets.size(); ++i)
            interm1_trie0[interm1_col0[i]][i] += 1;
        auto n_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(n_offsets.size());
        for (int i = 0; i < n_offsets.size(); ++i)
            n_trie0[n_id[i]][i] += 1;
        timer.StoreElapsedTime(4);

        string mn_n_name = "zzzzzzzz";
        string mn_interm1_col2 = "zzzzzzzz";
        string mn_interm1_col5 = "zzzzzzzz";
        string mn_interm1_col6 = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_movie_id[ci_off];
            if (interm1_trie0.contains(x0)) {
                auto &interm1_trie1 = interm1_trie0.at(x0);
                auto x1 = ci_person_id[ci_off];
                if (n_trie0.contains(x1)) {
                    auto &n_trie1 = n_trie0.at(x1);
                    for (const auto &n_off : n_trie1) {
                        mn_n_name = min(mn_n_name, n_name[n_off]);
                    }
                    for (const auto &interm1_off : interm1_trie1) {
                        mn_interm1_col2 = min(mn_interm1_col2, interm1_col2[interm1_off]);
                        mn_interm1_col5 = min(mn_interm1_col5, interm1_col5[interm1_off]);
                        mn_interm1_col6 = min(mn_interm1_col6, interm1_col6[interm1_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(5);

        if (iter == 0)
            cout << mn_n_name << " | " << mn_interm1_col2 << " | " << mn_interm1_col5 << " | " << mn_interm1_col6 << endl;
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
