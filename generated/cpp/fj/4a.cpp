#include "load/4a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4a/t.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4a/mi_idx.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4a/k.csv");
    load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4a/it.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        string IVs;
        timer.Reset();

        auto k_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(k_trie0, k_offsets, k_id);
        auto mi_idx_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto mi_idx_itrie0 = phmap::flat_hash_map<int, int>();
        auto mi_idx_isunq = build_trie(mi_idx_vtrie0, mi_idx_itrie0, mi_idx_offsets, mi_idx_movie_id);
        auto t_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto t_itrie0 = phmap::flat_hash_map<int, int>();
        auto t_isunq = build_trie(t_vtrie0, t_itrie0, t_offsets, t_id);
        auto it_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it_trie0, it_offsets, it_id);
        timer.StoreElapsedTime(0);

        string mn_t_title = "zzzzzzzz";
        string mn_mi_idx_info = "zzzzzzzz";
        if (mi_idx_isunq == 0 && t_isunq == 0) {
            if (iter == 0)
                IVs += "{mi_idx: v, t: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (mi_idx_vtrie0.contains(x1) && t_vtrie0.contains(x1)) {
                        auto &mi_idx_vtrie1 = mi_idx_vtrie0.at(x1);
                        auto &t_vtrie1 = t_vtrie0.at(x1);
                        for (const auto &mi_idx_off : mi_idx_vtrie1) {
                            auto x2 = mi_idx_info_type_id[mi_idx_off];
                            if (it_trie0.contains(x2)) {
                                auto &it_trie1 = it_trie0.at(x2);
                                for (const auto &t_off : t_vtrie1) {
                                    mn_t_title = min(mn_t_title, t_title[t_off]);
                                }
                                mn_mi_idx_info = min(mn_mi_idx_info, mi_idx_info[mi_idx_off]);
                            }
                        }
                    }
                }
            }
        } else if (mi_idx_isunq == 0 && t_isunq == 1) {
            if (iter == 0)
                IVs += "{mi_idx: v, t: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (mi_idx_vtrie0.contains(x1) && t_itrie0.contains(x1)) {
                        auto &mi_idx_vtrie1 = mi_idx_vtrie0.at(x1);
                        auto &t_itrie1 = t_itrie0.at(x1);
                        for (const auto &mi_idx_off : mi_idx_vtrie1) {
                            auto x2 = mi_idx_info_type_id[mi_idx_off];
                            if (it_trie0.contains(x2)) {
                                auto &it_trie1 = it_trie0.at(x2);
                                auto &t_off = t_itrie1;
                                mn_t_title = min(mn_t_title, t_title[t_off]);
                                mn_mi_idx_info = min(mn_mi_idx_info, mi_idx_info[mi_idx_off]);
                            }
                        }
                    }
                }
            }
        } else if (mi_idx_isunq == 1 && t_isunq == 0) {
            if (iter == 0)
                IVs += "{mi_idx: i, t: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (mi_idx_itrie0.contains(x1) && t_vtrie0.contains(x1)) {
                        auto &mi_idx_itrie1 = mi_idx_itrie0.at(x1);
                        auto &t_vtrie1 = t_vtrie0.at(x1);
                        auto &mi_idx_off = mi_idx_itrie1;
                        auto x2 = mi_idx_info_type_id[mi_idx_off];
                        if (it_trie0.contains(x2)) {
                            auto &it_trie1 = it_trie0.at(x2);
                            for (const auto &t_off : t_vtrie1) {
                                mn_t_title = min(mn_t_title, t_title[t_off]);
                            }
                            mn_mi_idx_info = min(mn_mi_idx_info, mi_idx_info[mi_idx_off]);
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                IVs += "{mi_idx: i, t: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (mi_idx_itrie0.contains(x1) && t_itrie0.contains(x1)) {
                        auto &mi_idx_itrie1 = mi_idx_itrie0.at(x1);
                        auto &t_itrie1 = t_itrie0.at(x1);
                        auto &mi_idx_off = mi_idx_itrie1;
                        auto x2 = mi_idx_info_type_id[mi_idx_off];
                        if (it_trie0.contains(x2)) {
                            auto &it_trie1 = it_trie0.at(x2);
                            auto &t_off = t_itrie1;
                            mn_t_title = min(mn_t_title, t_title[t_off]);
                            mn_mi_idx_info = min(mn_mi_idx_info, mi_idx_info[mi_idx_off]);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        if (iter == 0) {
            cout << mn_t_title << " | " << mn_mi_idx_info << endl;
            cout << IVs;
        }
        cout << "*" << " " << flush;
    }
    cout << endl;

    vector<double> tm{0};
    for (int i = 0; i < 2 * 1; ++i)
        tm.push_back(timer.GetMean(i));
    for (int i = 0; i < 2 * 1; i += 2) {
        cout << tm[i + 1] - tm[i] << " + ";
        cout << tm[i + 2] - tm[i + 1] << " = ";
        cout << tm[i + 2] - tm[i] << " ms" << endl;
    }
    cout << tm[2 * 1] << " ms" << endl;
}
