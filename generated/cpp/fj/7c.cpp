#include "load/7c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/n.csv");
    load_pi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/pi.csv");
    load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/it.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/t.csv");
    load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
    load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/lt.csv");
    load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
    load_an("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7c/an.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int z = 0; z < 1 + 5; ++z) {
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
        vector<string> interm0_col3;
        vector<int> interm0_offsets;
        cnt = 0;
        if (pi_isunq == 0) {
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
                            interm0_col3.push_back(pi_info[pi_off]);
                            interm0_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else {
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
                        interm0_col3.push_back(pi_info[pi_off]);
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
        vector<int> interm1_col1;
        vector<int> interm1_offsets;
        cnt = 0;
        if (pi_isunq == 0 && ml_isunq == 0) {
            for (const auto &t_off : t_offsets) {
                auto x0 = t_id[t_off];
                if (ml_vtrie0.contains(x0)) {
                    auto &ml_vtrie1 = ml_vtrie0.at(x0);
                    for (const auto &ml_off : ml_vtrie1) {
                        auto x1 = ml_link_type_id[ml_off];
                        if (lt_trie0.contains(x1)) {
                            auto &lt_trie1 = lt_trie0.at(x1);
                            interm1_col0.push_back(t_id[t_off]);
                            interm1_col1.push_back(ml_link_type_id[ml_off]);
                            interm1_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else if (pi_isunq == 0 && ml_isunq == 1) {
            for (const auto &t_off : t_offsets) {
                auto x0 = t_id[t_off];
                if (ml_itrie0.contains(x0)) {
                    auto &ml_itrie1 = ml_itrie0.at(x0);
                    auto &ml_off = ml_itrie1;
                    auto x1 = ml_link_type_id[ml_off];
                    if (lt_trie0.contains(x1)) {
                        auto &lt_trie1 = lt_trie0.at(x1);
                        interm1_col0.push_back(t_id[t_off]);
                        interm1_col1.push_back(ml_link_type_id[ml_off]);
                        interm1_offsets.push_back(cnt++);
                    }
                }
            }
        } else if (pi_isunq == 1 && ml_isunq == 0) {
            for (const auto &t_off : t_offsets) {
                auto x0 = t_id[t_off];
                if (ml_vtrie0.contains(x0)) {
                    auto &ml_vtrie1 = ml_vtrie0.at(x0);
                    for (const auto &ml_off : ml_vtrie1) {
                        auto x1 = ml_link_type_id[ml_off];
                        if (lt_trie0.contains(x1)) {
                            auto &lt_trie1 = lt_trie0.at(x1);
                            interm1_col0.push_back(t_id[t_off]);
                            interm1_col1.push_back(ml_link_type_id[ml_off]);
                            interm1_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else {
            for (const auto &t_off : t_offsets) {
                auto x0 = t_id[t_off];
                if (ml_itrie0.contains(x0)) {
                    auto &ml_itrie1 = ml_itrie0.at(x0);
                    auto &ml_off = ml_itrie1;
                    auto x1 = ml_link_type_id[ml_off];
                    if (lt_trie0.contains(x1)) {
                        auto &lt_trie1 = lt_trie0.at(x1);
                        interm1_col0.push_back(t_id[t_off]);
                        interm1_col1.push_back(ml_link_type_id[ml_off]);
                        interm1_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto interm1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(interm1_trie0, interm1_offsets, interm1_col0);
        auto interm0_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm0_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm0_isunq = build_trie(interm0_vtrie0, interm0_itrie0, interm0_offsets, interm0_col0);
        auto an_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(an_trie0, an_offsets, an_person_id);
        timer.StoreElapsedTime(4);

        string mn_interm0_col1 = "zzzzzzzz";
        string mn_interm0_col3 = "zzzzzzzz";
        if (pi_isunq == 0 && ml_isunq == 0 && interm0_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm1_trie0.contains(x0)) {
                    auto &interm1_trie1 = interm1_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (interm0_vtrie0.contains(x1) && an_trie0.contains(x1)) {
                        auto &interm0_vtrie1 = interm0_vtrie0.at(x1);
                        auto &an_trie1 = an_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                        }
                    }
                }
            }
        } else if (pi_isunq == 0 && ml_isunq == 0 && interm0_isunq == 1) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm1_trie0.contains(x0)) {
                    auto &interm1_trie1 = interm1_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (interm0_itrie0.contains(x1) && an_trie0.contains(x1)) {
                        auto &interm0_itrie1 = interm0_itrie0.at(x1);
                        auto &an_trie1 = an_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                    }
                }
            }
        } else if (pi_isunq == 0 && ml_isunq == 1 && interm0_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm1_trie0.contains(x0)) {
                    auto &interm1_trie1 = interm1_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (interm0_vtrie0.contains(x1) && an_trie0.contains(x1)) {
                        auto &interm0_vtrie1 = interm0_vtrie0.at(x1);
                        auto &an_trie1 = an_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                        }
                    }
                }
            }
        } else if (pi_isunq == 0 && ml_isunq == 1 && interm0_isunq == 1) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm1_trie0.contains(x0)) {
                    auto &interm1_trie1 = interm1_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (interm0_itrie0.contains(x1) && an_trie0.contains(x1)) {
                        auto &interm0_itrie1 = interm0_itrie0.at(x1);
                        auto &an_trie1 = an_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                    }
                }
            }
        } else if (pi_isunq == 1 && ml_isunq == 0 && interm0_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm1_trie0.contains(x0)) {
                    auto &interm1_trie1 = interm1_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (interm0_vtrie0.contains(x1) && an_trie0.contains(x1)) {
                        auto &interm0_vtrie1 = interm0_vtrie0.at(x1);
                        auto &an_trie1 = an_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                        }
                    }
                }
            }
        } else if (pi_isunq == 1 && ml_isunq == 0 && interm0_isunq == 1) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm1_trie0.contains(x0)) {
                    auto &interm1_trie1 = interm1_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (interm0_itrie0.contains(x1) && an_trie0.contains(x1)) {
                        auto &interm0_itrie1 = interm0_itrie0.at(x1);
                        auto &an_trie1 = an_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                    }
                }
            }
        } else if (pi_isunq == 1 && ml_isunq == 1 && interm0_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm1_trie0.contains(x0)) {
                    auto &interm1_trie1 = interm1_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (interm0_vtrie0.contains(x1) && an_trie0.contains(x1)) {
                        auto &interm0_vtrie1 = interm0_vtrie0.at(x1);
                        auto &an_trie1 = an_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                        }
                    }
                }
            }
        } else {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm1_trie0.contains(x0)) {
                    auto &interm1_trie1 = interm1_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (interm0_itrie0.contains(x1) && an_trie0.contains(x1)) {
                        auto &interm0_itrie1 = interm0_itrie0.at(x1);
                        auto &an_trie1 = an_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(5);

        if (z == 0)
            cout << mn_interm0_col1 << " | " << mn_interm0_col3 << endl;
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
