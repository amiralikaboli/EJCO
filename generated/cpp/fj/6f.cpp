#include "load/6f.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/6f/t.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/6f/k.csv");
    load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
    load_n("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto k_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto k_itrie0 = phmap::flat_hash_map<int, int>();
        auto k_isunq = build_trie(k_vtrie0, k_itrie0, k_offsets, k_id);
        auto t_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto t_itrie0 = phmap::flat_hash_map<int, int>();
        auto t_isunq = build_trie(t_vtrie0, t_itrie0, t_offsets, t_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<string> interm0_col3;
        vector<int> interm0_offsets;
        cnt = 0;
        if (k_isunq == 0 && t_isunq == 0) {
            if (iter == 0)
                cout << "{k: v, t: v}" << endl;
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_vtrie0.contains(x0)) {
                    auto &k_vtrie1 = k_vtrie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_vtrie0.contains(x1)) {
                        auto &t_vtrie1 = t_vtrie0.at(x1);
                        for (const auto &t_off : t_vtrie1) {
                            for (const auto &k_off : k_vtrie1) {
                                interm0_col0.push_back(mk_movie_id[mk_off]);
                                interm0_col1.push_back(mk_keyword_id[mk_off]);
                                interm0_col2.push_back(t_title[t_off]);
                                interm0_col3.push_back(k_keyword[k_off]);
                                interm0_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        } else if (k_isunq == 0 && t_isunq == 1) {
            if (iter == 0)
                cout << "{k: v, t: i}" << endl;
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_vtrie0.contains(x0)) {
                    auto &k_vtrie1 = k_vtrie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_itrie0.contains(x1)) {
                        auto &t_itrie1 = t_itrie0.at(x1);
                        auto &t_off = t_itrie1;
                        for (const auto &k_off : k_vtrie1) {
                            interm0_col0.push_back(mk_movie_id[mk_off]);
                            interm0_col1.push_back(mk_keyword_id[mk_off]);
                            interm0_col2.push_back(t_title[t_off]);
                            interm0_col3.push_back(k_keyword[k_off]);
                            interm0_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else if (k_isunq == 1 && t_isunq == 0) {
            if (iter == 0)
                cout << "{k: i, t: v}" << endl;
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_itrie0.contains(x0)) {
                    auto &k_itrie1 = k_itrie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_vtrie0.contains(x1)) {
                        auto &t_vtrie1 = t_vtrie0.at(x1);
                        for (const auto &t_off : t_vtrie1) {
                            auto &k_off = k_itrie1;
                            interm0_col0.push_back(mk_movie_id[mk_off]);
                            interm0_col1.push_back(mk_keyword_id[mk_off]);
                            interm0_col2.push_back(t_title[t_off]);
                            interm0_col3.push_back(k_keyword[k_off]);
                            interm0_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{k: i, t: i}" << endl;
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_itrie0.contains(x0)) {
                    auto &k_itrie1 = k_itrie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_itrie0.contains(x1)) {
                        auto &t_itrie1 = t_itrie0.at(x1);
                        auto &t_off = t_itrie1;
                        auto &k_off = k_itrie1;
                        interm0_col0.push_back(mk_movie_id[mk_off]);
                        interm0_col1.push_back(mk_keyword_id[mk_off]);
                        interm0_col2.push_back(t_title[t_off]);
                        interm0_col3.push_back(k_keyword[k_off]);
                        interm0_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto interm0_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm0_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm0_isunq = build_trie(interm0_vtrie0, interm0_itrie0, interm0_offsets, interm0_col0);
        auto n_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto n_itrie0 = phmap::flat_hash_map<int, int>();
        auto n_isunq = build_trie(n_vtrie0, n_itrie0, n_offsets, n_id);
        timer.StoreElapsedTime(2);

        string mn_n_name = "zzzzzzzz";
        string mn_interm0_col2 = "zzzzzzzz";
        string mn_interm0_col3 = "zzzzzzzz";
        if (interm0_isunq == 0 && n_isunq == 0) {
            if (iter == 0)
                cout << "{interm0: v, n: v}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_vtrie0.contains(x1)) {
                        auto &n_vtrie1 = n_vtrie0.at(x1);
                        for (const auto &n_off : n_vtrie1) {
                            mn_n_name = min(mn_n_name, n_name[n_off]);
                        }
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                            mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                        }
                    }
                }
            }
        } else if (interm0_isunq == 0 && n_isunq == 1) {
            if (iter == 0)
                cout << "{interm0: v, n: i}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_itrie0.contains(x1)) {
                        auto &n_itrie1 = n_itrie0.at(x1);
                        auto &n_off = n_itrie1;
                        mn_n_name = min(mn_n_name, n_name[n_off]);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                            mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && n_isunq == 0) {
            if (iter == 0)
                cout << "{interm0: i, n: v}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_vtrie0.contains(x1)) {
                        auto &n_vtrie1 = n_vtrie0.at(x1);
                        for (const auto &n_off : n_vtrie1) {
                            mn_n_name = min(mn_n_name, n_name[n_off]);
                        }
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{interm0: i, n: i}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_itrie0.contains(x1)) {
                        auto &n_itrie1 = n_itrie0.at(x1);
                        auto &n_off = n_itrie1;
                        mn_n_name = min(mn_n_name, n_name[n_off]);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_n_name << " | " << mn_interm0_col2 << " | " << mn_interm0_col3 << endl;
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
