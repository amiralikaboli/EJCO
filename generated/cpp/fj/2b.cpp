#include "load/2b.h"
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
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/2b/k.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/2b/cn.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto k_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(k_trie0, k_offsets, k_id);
        auto t_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto t_itrie0 = phmap::flat_hash_map<int, int>();
        auto t_isunq = build_trie(t_vtrie0, t_itrie0, t_offsets, t_id);
        auto mc_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto mc_itrie0 = phmap::flat_hash_map<int, int>();
        auto mc_isunq = build_trie(mc_vtrie0, mc_itrie0, mc_offsets, mc_movie_id);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cn_trie0, cn_offsets, cn_id);
        timer.StoreElapsedTime(0);

        string mn_t_title = "zzzzzzzz";
        if (t_isunq == 0 && mc_isunq == 0) {
            if (iter == 0)
                cout << "{t: v, mc: v}" << endl;
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_vtrie0.contains(x1) && mc_vtrie0.contains(x1)) {
                        auto &t_vtrie1 = t_vtrie0.at(x1);
                        auto &mc_vtrie1 = mc_vtrie0.at(x1);
                        for (const auto &mc_off : mc_vtrie1) {
                            auto x2 = mc_company_id[mc_off];
                            if (cn_trie0.contains(x2)) {
                                auto &cn_trie1 = cn_trie0.at(x2);
                                for (const auto &t_off : t_vtrie1) {
                                    mn_t_title = min(mn_t_title, t_title[t_off]);
                                }
                            }
                        }
                    }
                }
            }
        } else if (t_isunq == 0 && mc_isunq == 1) {
            if (iter == 0)
                cout << "{t: v, mc: i}" << endl;
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_vtrie0.contains(x1) && mc_itrie0.contains(x1)) {
                        auto &t_vtrie1 = t_vtrie0.at(x1);
                        auto &mc_itrie1 = mc_itrie0.at(x1);
                        auto &mc_off = mc_itrie1;
                        auto x2 = mc_company_id[mc_off];
                        if (cn_trie0.contains(x2)) {
                            auto &cn_trie1 = cn_trie0.at(x2);
                            for (const auto &t_off : t_vtrie1) {
                                mn_t_title = min(mn_t_title, t_title[t_off]);
                            }
                        }
                    }
                }
            }
        } else if (t_isunq == 1 && mc_isunq == 0) {
            if (iter == 0)
                cout << "{t: i, mc: v}" << endl;
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_itrie0.contains(x1) && mc_vtrie0.contains(x1)) {
                        auto &t_itrie1 = t_itrie0.at(x1);
                        auto &mc_vtrie1 = mc_vtrie0.at(x1);
                        for (const auto &mc_off : mc_vtrie1) {
                            auto x2 = mc_company_id[mc_off];
                            if (cn_trie0.contains(x2)) {
                                auto &cn_trie1 = cn_trie0.at(x2);
                                auto &t_off = t_itrie1;
                                mn_t_title = min(mn_t_title, t_title[t_off]);
                            }
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{t: i, mc: i}" << endl;
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_itrie0.contains(x1) && mc_itrie0.contains(x1)) {
                        auto &t_itrie1 = t_itrie0.at(x1);
                        auto &mc_itrie1 = mc_itrie0.at(x1);
                        auto &mc_off = mc_itrie1;
                        auto x2 = mc_company_id[mc_off];
                        if (cn_trie0.contains(x2)) {
                            auto &cn_trie1 = cn_trie0.at(x2);
                            auto &t_off = t_itrie1;
                            mn_t_title = min(mn_t_title, t_title[t_off]);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        if (iter == 0)
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
