#include "load/5c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/mi.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/t.csv");
    load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/mc.csv");
    load_it("/Users/s2522996/Documents/free-join/data/imdb_csv/info_type.csv");
    load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/ct.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int z = 0; z < 1 + 5; ++z) {
        int cnt;
        timer.Reset();

        auto it_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it_trie0, it_offsets, it_id);
        auto mc_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto mc_itrie0 = phmap::flat_hash_map<int, int>();
        auto mc_isunq = build_trie(mc_vtrie0, mc_itrie0, mc_offsets, mc_movie_id);
        auto t_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto t_itrie0 = phmap::flat_hash_map<int, int>();
        auto t_isunq = build_trie(t_vtrie0, t_itrie0, t_offsets, t_id);
        auto ct_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(ct_trie0, ct_offsets, ct_id);
        timer.StoreElapsedTime(0);

        string mn_t_title = "zzzzzzzz";
        if (mc_isunq == 0 && t_isunq == 0) {
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_info_type_id[mi_off];
                if (it_trie0.contains(x0)) {
                    auto &it_trie1 = it_trie0.at(x0);
                    auto x1 = mi_movie_id[mi_off];
                    if (mc_vtrie0.contains(x1) && t_vtrie0.contains(x1)) {
                        auto &mc_vtrie1 = mc_vtrie0.at(x1);
                        auto &t_vtrie1 = t_vtrie0.at(x1);
                        for (const auto &mc_off : mc_vtrie1) {
                            auto x2 = mc_company_type_id[mc_off];
                            if (ct_trie0.contains(x2)) {
                                auto &ct_trie1 = ct_trie0.at(x2);
                                for (const auto &t_off : t_vtrie1) {
                                    mn_t_title = min(mn_t_title, t_title[t_off]);
                                }
                            }
                        }
                    }
                }
            }
        } else if (mc_isunq == 0 && t_isunq == 1) {
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_info_type_id[mi_off];
                if (it_trie0.contains(x0)) {
                    auto &it_trie1 = it_trie0.at(x0);
                    auto x1 = mi_movie_id[mi_off];
                    if (mc_vtrie0.contains(x1) && t_itrie0.contains(x1)) {
                        auto &mc_vtrie1 = mc_vtrie0.at(x1);
                        auto &t_itrie1 = t_itrie0.at(x1);
                        for (const auto &mc_off : mc_vtrie1) {
                            auto x2 = mc_company_type_id[mc_off];
                            if (ct_trie0.contains(x2)) {
                                auto &ct_trie1 = ct_trie0.at(x2);
                                auto &t_off = t_itrie1;
                                mn_t_title = min(mn_t_title, t_title[t_off]);
                            }
                        }
                    }
                }
            }
        } else if (mc_isunq == 1 && t_isunq == 0) {
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_info_type_id[mi_off];
                if (it_trie0.contains(x0)) {
                    auto &it_trie1 = it_trie0.at(x0);
                    auto x1 = mi_movie_id[mi_off];
                    if (mc_itrie0.contains(x1) && t_vtrie0.contains(x1)) {
                        auto &mc_itrie1 = mc_itrie0.at(x1);
                        auto &t_vtrie1 = t_vtrie0.at(x1);
                        auto &mc_off = mc_itrie1;
                        auto x2 = mc_company_type_id[mc_off];
                        if (ct_trie0.contains(x2)) {
                            auto &ct_trie1 = ct_trie0.at(x2);
                            for (const auto &t_off : t_vtrie1) {
                                mn_t_title = min(mn_t_title, t_title[t_off]);
                            }
                        }
                    }
                }
            }
        } else {
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_info_type_id[mi_off];
                if (it_trie0.contains(x0)) {
                    auto &it_trie1 = it_trie0.at(x0);
                    auto x1 = mi_movie_id[mi_off];
                    if (mc_itrie0.contains(x1) && t_itrie0.contains(x1)) {
                        auto &mc_itrie1 = mc_itrie0.at(x1);
                        auto &t_itrie1 = t_itrie0.at(x1);
                        auto &mc_off = mc_itrie1;
                        auto x2 = mc_company_type_id[mc_off];
                        if (ct_trie0.contains(x2)) {
                            auto &ct_trie1 = ct_trie0.at(x2);
                            auto &t_off = t_itrie1;
                            mn_t_title = min(mn_t_title, t_title[t_off]);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        if (z == 0)
            cout << mn_t_title << endl;
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
