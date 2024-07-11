#include "load/7b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/n.csv");
    load_pi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/pi.csv");
    load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/it.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/t.csv");
    load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
    load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/lt.csv");
    load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
    load_an("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7b/an.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto pi_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto pi_itrie0 = phmap::flat_hash_map<int, int>();
        auto pi_isunq = build_trie(pi_vtrie0, pi_itrie0, pi_offsets, pi_person_id);
        auto it_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it_trie0, it_offsets, it_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<int> interm0_offsets;
        cnt = 0;
        if (pi_isunq == 0) {
            if (iter == 0)
                cout << "{pi: v}" << endl;
            for (const auto &n_off : n_offsets) {
                auto x0 = n_id[n_off];
                if (pi_vtrie0.contains(x0)) {
                    auto &pi_vtrie1 = pi_vtrie0.at(x0);
                    for (const auto &pi_off : pi_vtrie1) {
                        auto x1 = pi_info_type_id[pi_off];
                        if (it_trie0.contains(x1)) {
                            auto &it_trie1 = it_trie0.at(x1);
                            interm0_col0.push_back(n_id[n_off]);
                            interm0_col1.push_back(n_name[n_off]);
                            interm0_col2.push_back(pi_info_type_id[pi_off]);
                            interm0_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{pi: i}" << endl;
            for (const auto &n_off : n_offsets) {
                auto x0 = n_id[n_off];
                if (pi_itrie0.contains(x0)) {
                    auto &pi_itrie1 = pi_itrie0.at(x0);
                    auto &pi_off = pi_itrie1;
                    auto x1 = pi_info_type_id[pi_off];
                    if (it_trie0.contains(x1)) {
                        auto &it_trie1 = it_trie0.at(x1);
                        interm0_col0.push_back(n_id[n_off]);
                        interm0_col1.push_back(n_name[n_off]);
                        interm0_col2.push_back(pi_info_type_id[pi_off]);
                        interm0_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto ml_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto ml_itrie0 = phmap::flat_hash_map<int, int>();
        auto ml_isunq = build_trie(ml_vtrie0, ml_itrie0, ml_offsets, ml_linked_movie_id);
        auto lt_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(lt_trie0, lt_offsets, lt_id);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<string> interm1_col1;
        vector<int> interm1_col2;
        vector<int> interm1_offsets;
        cnt = 0;
        if (ml_isunq == 0) {
            if (iter == 0)
                cout << "{ml: v}" << endl;
            for (const auto &t_off : t_offsets) {
                auto x0 = t_id[t_off];
                if (ml_vtrie0.contains(x0)) {
                    auto &ml_vtrie1 = ml_vtrie0.at(x0);
                    for (const auto &ml_off : ml_vtrie1) {
                        auto x1 = ml_link_type_id[ml_off];
                        if (lt_trie0.contains(x1)) {
                            auto &lt_trie1 = lt_trie0.at(x1);
                            interm1_col0.push_back(t_id[t_off]);
                            interm1_col1.push_back(t_title[t_off]);
                            interm1_col2.push_back(ml_link_type_id[ml_off]);
                            interm1_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{ml: i}" << endl;
            for (const auto &t_off : t_offsets) {
                auto x0 = t_id[t_off];
                if (ml_itrie0.contains(x0)) {
                    auto &ml_itrie1 = ml_itrie0.at(x0);
                    auto &ml_off = ml_itrie1;
                    auto x1 = ml_link_type_id[ml_off];
                    if (lt_trie0.contains(x1)) {
                        auto &lt_trie1 = lt_trie0.at(x1);
                        interm1_col0.push_back(t_id[t_off]);
                        interm1_col1.push_back(t_title[t_off]);
                        interm1_col2.push_back(ml_link_type_id[ml_off]);
                        interm1_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto interm0_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm0_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm0_isunq = build_trie(interm0_vtrie0, interm0_itrie0, interm0_offsets, interm0_col0);
        auto interm1_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm1_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm1_isunq = build_trie(interm1_vtrie0, interm1_itrie0, interm1_offsets, interm1_col0);
        auto an_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(an_trie0, an_offsets, an_person_id);
        timer.StoreElapsedTime(4);

        string mn_interm1_col1 = "zzzzzzzz";
        string mn_interm0_col1 = "zzzzzzzz";
        if (interm0_isunq == 0 && interm1_isunq == 0) {
            if (iter == 0)
                cout << "{interm0: v, interm1: v}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_person_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_vtrie0.contains(x1)) {
                        auto &interm1_vtrie1 = interm1_vtrie0.at(x1);
                        if (an_trie0.contains(x0)) {
                            auto &an_trie1 = an_trie0.at(x0);
                            for (const auto &interm1_off : interm1_vtrie1) {
                                mn_interm1_col1 = min(mn_interm1_col1, interm1_col1[interm1_off]);
                            }
                            for (const auto &interm0_off : interm0_vtrie1) {
                                mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 0 && interm1_isunq == 1) {
            if (iter == 0)
                cout << "{interm0: v, interm1: i}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_person_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_itrie0.contains(x1)) {
                        auto &interm1_itrie1 = interm1_itrie0.at(x1);
                        if (an_trie0.contains(x0)) {
                            auto &an_trie1 = an_trie0.at(x0);
                            auto &interm1_off = interm1_itrie1;
                            mn_interm1_col1 = min(mn_interm1_col1, interm1_col1[interm1_off]);
                            for (const auto &interm0_off : interm0_vtrie1) {
                                mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && interm1_isunq == 0) {
            if (iter == 0)
                cout << "{interm0: i, interm1: v}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_person_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_vtrie0.contains(x1)) {
                        auto &interm1_vtrie1 = interm1_vtrie0.at(x1);
                        if (an_trie0.contains(x0)) {
                            auto &an_trie1 = an_trie0.at(x0);
                            for (const auto &interm1_off : interm1_vtrie1) {
                                mn_interm1_col1 = min(mn_interm1_col1, interm1_col1[interm1_off]);
                            }
                            auto &interm0_off = interm0_itrie1;
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{interm0: i, interm1: i}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_person_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_itrie0.contains(x1)) {
                        auto &interm1_itrie1 = interm1_itrie0.at(x1);
                        if (an_trie0.contains(x0)) {
                            auto &an_trie1 = an_trie0.at(x0);
                            auto &interm1_off = interm1_itrie1;
                            mn_interm1_col1 = min(mn_interm1_col1, interm1_col1[interm1_off]);
                            auto &interm0_off = interm0_itrie1;
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(5);

        if (iter == 0)
            cout << mn_interm1_col1 << " | " << mn_interm0_col1 << endl;
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
