#include "load/18b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/t.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/mi_idx.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/mi.csv");
    load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/it2.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/it1.csv");
    load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/ci.csv");
    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/18b/n.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto mi_idx_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto mi_idx_itrie0 = phmap::flat_hash_map<int, int>();
        auto mi_idx_isunq = build_trie(mi_idx_vtrie0, mi_idx_itrie0, mi_idx_offsets, mi_idx_movie_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<string> interm0_col3;
        vector<int> interm0_offsets;
        cnt = 0;
        if (mi_idx_isunq == 0) {
            if (iter == 0)
                cout << "{mi_idx: v}" << endl;
            for (const auto &t_off : t_offsets) {
                auto x0 = t_id[t_off];
                if (mi_idx_vtrie0.contains(x0)) {
                    auto &mi_idx_vtrie1 = mi_idx_vtrie0.at(x0);
                    for (const auto &mi_idx_off : mi_idx_vtrie1) {
                        interm0_col0.push_back(t_id[t_off]);
                        interm0_col1.push_back(t_title[t_off]);
                        interm0_col2.push_back(mi_idx_info_type_id[mi_idx_off]);
                        interm0_col3.push_back(mi_idx_info[mi_idx_off]);
                        interm0_offsets.push_back(cnt++);
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{mi_idx: i}" << endl;
            for (const auto &t_off : t_offsets) {
                auto x0 = t_id[t_off];
                if (mi_idx_itrie0.contains(x0)) {
                    auto &mi_idx_itrie1 = mi_idx_itrie0.at(x0);
                    auto &mi_idx_off = mi_idx_itrie1;
                    interm0_col0.push_back(t_id[t_off]);
                    interm0_col1.push_back(t_title[t_off]);
                    interm0_col2.push_back(mi_idx_info_type_id[mi_idx_off]);
                    interm0_col3.push_back(mi_idx_info[mi_idx_off]);
                    interm0_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto interm0_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm0_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm0_isunq = build_trie(interm0_vtrie0, interm0_itrie0, interm0_offsets, interm0_col0);
        auto it2_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it2_trie0, it2_offsets, it2_id);
        auto it1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it1_trie0, it1_offsets, it1_id);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<int> interm1_col1;
        vector<string> interm1_col2;
        vector<int> interm1_col3;
        vector<string> interm1_col4;
        vector<string> interm1_col5;
        vector<int> interm1_offsets;
        cnt = 0;
        if (interm0_isunq == 0) {
            if (iter == 0)
                cout << "{interm0: v}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (it2_trie0.contains(x1)) {
                            auto &it2_trie1 = it2_trie0.at(x1);
                            auto x2 = mi_info_type_id[mi_off];
                            if (it1_trie0.contains(x2)) {
                                auto &it1_trie1 = it1_trie0.at(x2);
                                interm1_col0.push_back(mi_movie_id[mi_off]);
                                interm1_col1.push_back(mi_info_type_id[mi_off]);
                                interm1_col2.push_back(mi_info[mi_off]);
                                interm1_col3.push_back(interm0_col2[interm0_off]);
                                interm1_col4.push_back(interm0_col1[interm0_off]);
                                interm1_col5.push_back(interm0_col3[interm0_off]);
                                interm1_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{interm0: i}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (it2_trie0.contains(x1)) {
                        auto &it2_trie1 = it2_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it1_trie0.contains(x2)) {
                            auto &it1_trie1 = it1_trie0.at(x2);
                            interm1_col0.push_back(mi_movie_id[mi_off]);
                            interm1_col1.push_back(mi_info_type_id[mi_off]);
                            interm1_col2.push_back(mi_info[mi_off]);
                            interm1_col3.push_back(interm0_col2[interm0_off]);
                            interm1_col4.push_back(interm0_col1[interm0_off]);
                            interm1_col5.push_back(interm0_col3[interm0_off]);
                            interm1_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto interm1_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm1_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm1_isunq = build_trie(interm1_vtrie0, interm1_itrie0, interm1_offsets, interm1_col0);
        auto n_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(n_trie0, n_offsets, n_id);
        timer.StoreElapsedTime(4);

        string mn_interm1_col2 = "zzzzzzzz";
        string mn_interm1_col4 = "zzzzzzzz";
        string mn_interm1_col5 = "zzzzzzzz";
        if (interm1_isunq == 0) {
            if (iter == 0)
                cout << "{interm1: v}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm1_vtrie0.contains(x0)) {
                    auto &interm1_vtrie1 = interm1_vtrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_trie0.contains(x1)) {
                        auto &n_trie1 = n_trie0.at(x1);
                        for (const auto &interm1_off : interm1_vtrie1) {
                            mn_interm1_col2 = min(mn_interm1_col2, interm1_col2[interm1_off]);
                            mn_interm1_col4 = min(mn_interm1_col4, interm1_col4[interm1_off]);
                            mn_interm1_col5 = min(mn_interm1_col5, interm1_col5[interm1_off]);
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{interm1: i}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm1_itrie0.contains(x0)) {
                    auto &interm1_itrie1 = interm1_itrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_trie0.contains(x1)) {
                        auto &n_trie1 = n_trie0.at(x1);
                        auto &interm1_off = interm1_itrie1;
                        mn_interm1_col2 = min(mn_interm1_col2, interm1_col2[interm1_off]);
                        mn_interm1_col4 = min(mn_interm1_col4, interm1_col4[interm1_off]);
                        mn_interm1_col5 = min(mn_interm1_col5, interm1_col5[interm1_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(5);

        if (iter == 0)
            cout << mn_interm1_col2 << " | " << mn_interm1_col4 << " | " << mn_interm1_col5 << endl;
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
