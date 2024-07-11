#include "load/9a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9a/mc.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9a/cn.csv");
    load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9a/ci.csv");
    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9a/n.csv");
    load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9a/rt.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9a/t.csv");
    load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
    load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto cn_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cn_trie0, cn_offsets, cn_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &mc_off : mc_offsets) {
            auto x0 = mc_company_id[mc_off];
            if (cn_trie0.contains(x0)) {
                auto &cn_trie1 = cn_trie0.at(x0);
                interm0_col0.push_back(mc_company_id[mc_off]);
                interm0_col1.push_back(mc_movie_id[mc_off]);
                interm0_offsets.push_back(cnt++);
            }
        }
        timer.StoreElapsedTime(1);

        auto rt_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(rt_trie0, rt_offsets, rt_id);
        auto n_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(n_trie0, n_offsets, n_id);
        auto interm0_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(interm0_trie0, interm0_offsets, interm0_col1);
        auto an_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto an_itrie0 = phmap::flat_hash_map<int, int>();
        auto an_isunq = build_trie(an_vtrie0, an_itrie0, an_offsets, an_person_id);
        auto t_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto t_itrie0 = phmap::flat_hash_map<int, int>();
        auto t_isunq = build_trie(t_vtrie0, t_itrie0, t_offsets, t_id);
        auto chn_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto chn_itrie0 = phmap::flat_hash_map<int, int>();
        auto chn_isunq = build_trie(chn_vtrie0, chn_itrie0, chn_offsets, chn_id);
        timer.StoreElapsedTime(2);

        string mn_t_title = "zzzzzzzz";
        string mn_chn_name = "zzzzzzzz";
        string mn_an_name = "zzzzzzzz";
        if (an_isunq == 0 && t_isunq == 0 && chn_isunq == 0) {
            if (iter == 0)
                cout << "{an: v, t: v, chn: v}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_trie0.contains(x1)) {
                        auto &n_trie1 = n_trie0.at(x1);
                        auto x2 = ci_movie_id[ci_off];
                        if (interm0_trie0.contains(x2)) {
                            auto &interm0_trie1 = interm0_trie0.at(x2);
                            if (an_vtrie0.contains(x1)) {
                                auto &an_vtrie1 = an_vtrie0.at(x1);
                                if (t_vtrie0.contains(x2)) {
                                    auto &t_vtrie1 = t_vtrie0.at(x2);
                                    auto x5 = ci_person_role_id[ci_off];
                                    if (chn_vtrie0.contains(x5)) {
                                        auto &chn_vtrie1 = chn_vtrie0.at(x5);
                                        for (const auto &t_off : t_vtrie1) {
                                            mn_t_title = min(mn_t_title, t_title[t_off]);
                                        }
                                        for (const auto &chn_off : chn_vtrie1) {
                                            mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                        }
                                        for (const auto &an_off : an_vtrie1) {
                                            mn_an_name = min(mn_an_name, an_name[an_off]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (an_isunq == 0 && t_isunq == 0 && chn_isunq == 1) {
            if (iter == 0)
                cout << "{an: v, t: v, chn: i}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_trie0.contains(x1)) {
                        auto &n_trie1 = n_trie0.at(x1);
                        auto x2 = ci_movie_id[ci_off];
                        if (interm0_trie0.contains(x2)) {
                            auto &interm0_trie1 = interm0_trie0.at(x2);
                            if (an_vtrie0.contains(x1)) {
                                auto &an_vtrie1 = an_vtrie0.at(x1);
                                if (t_vtrie0.contains(x2)) {
                                    auto &t_vtrie1 = t_vtrie0.at(x2);
                                    auto x5 = ci_person_role_id[ci_off];
                                    if (chn_itrie0.contains(x5)) {
                                        auto &chn_itrie1 = chn_itrie0.at(x5);
                                        for (const auto &t_off : t_vtrie1) {
                                            mn_t_title = min(mn_t_title, t_title[t_off]);
                                        }
                                        auto &chn_off = chn_itrie1;
                                        mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                        for (const auto &an_off : an_vtrie1) {
                                            mn_an_name = min(mn_an_name, an_name[an_off]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (an_isunq == 0 && t_isunq == 1 && chn_isunq == 0) {
            if (iter == 0)
                cout << "{an: v, t: i, chn: v}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_trie0.contains(x1)) {
                        auto &n_trie1 = n_trie0.at(x1);
                        auto x2 = ci_movie_id[ci_off];
                        if (interm0_trie0.contains(x2)) {
                            auto &interm0_trie1 = interm0_trie0.at(x2);
                            if (an_vtrie0.contains(x1)) {
                                auto &an_vtrie1 = an_vtrie0.at(x1);
                                if (t_itrie0.contains(x2)) {
                                    auto &t_itrie1 = t_itrie0.at(x2);
                                    auto x5 = ci_person_role_id[ci_off];
                                    if (chn_vtrie0.contains(x5)) {
                                        auto &chn_vtrie1 = chn_vtrie0.at(x5);
                                        auto &t_off = t_itrie1;
                                        mn_t_title = min(mn_t_title, t_title[t_off]);
                                        for (const auto &chn_off : chn_vtrie1) {
                                            mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                        }
                                        for (const auto &an_off : an_vtrie1) {
                                            mn_an_name = min(mn_an_name, an_name[an_off]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (an_isunq == 0 && t_isunq == 1 && chn_isunq == 1) {
            if (iter == 0)
                cout << "{an: v, t: i, chn: i}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_trie0.contains(x1)) {
                        auto &n_trie1 = n_trie0.at(x1);
                        auto x2 = ci_movie_id[ci_off];
                        if (interm0_trie0.contains(x2)) {
                            auto &interm0_trie1 = interm0_trie0.at(x2);
                            if (an_vtrie0.contains(x1)) {
                                auto &an_vtrie1 = an_vtrie0.at(x1);
                                if (t_itrie0.contains(x2)) {
                                    auto &t_itrie1 = t_itrie0.at(x2);
                                    auto x5 = ci_person_role_id[ci_off];
                                    if (chn_itrie0.contains(x5)) {
                                        auto &chn_itrie1 = chn_itrie0.at(x5);
                                        auto &t_off = t_itrie1;
                                        mn_t_title = min(mn_t_title, t_title[t_off]);
                                        auto &chn_off = chn_itrie1;
                                        mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                        for (const auto &an_off : an_vtrie1) {
                                            mn_an_name = min(mn_an_name, an_name[an_off]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (an_isunq == 1 && t_isunq == 0 && chn_isunq == 0) {
            if (iter == 0)
                cout << "{an: i, t: v, chn: v}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_trie0.contains(x1)) {
                        auto &n_trie1 = n_trie0.at(x1);
                        auto x2 = ci_movie_id[ci_off];
                        if (interm0_trie0.contains(x2)) {
                            auto &interm0_trie1 = interm0_trie0.at(x2);
                            if (an_itrie0.contains(x1)) {
                                auto &an_itrie1 = an_itrie0.at(x1);
                                if (t_vtrie0.contains(x2)) {
                                    auto &t_vtrie1 = t_vtrie0.at(x2);
                                    auto x5 = ci_person_role_id[ci_off];
                                    if (chn_vtrie0.contains(x5)) {
                                        auto &chn_vtrie1 = chn_vtrie0.at(x5);
                                        for (const auto &t_off : t_vtrie1) {
                                            mn_t_title = min(mn_t_title, t_title[t_off]);
                                        }
                                        for (const auto &chn_off : chn_vtrie1) {
                                            mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                        }
                                        auto &an_off = an_itrie1;
                                        mn_an_name = min(mn_an_name, an_name[an_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (an_isunq == 1 && t_isunq == 0 && chn_isunq == 1) {
            if (iter == 0)
                cout << "{an: i, t: v, chn: i}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_trie0.contains(x1)) {
                        auto &n_trie1 = n_trie0.at(x1);
                        auto x2 = ci_movie_id[ci_off];
                        if (interm0_trie0.contains(x2)) {
                            auto &interm0_trie1 = interm0_trie0.at(x2);
                            if (an_itrie0.contains(x1)) {
                                auto &an_itrie1 = an_itrie0.at(x1);
                                if (t_vtrie0.contains(x2)) {
                                    auto &t_vtrie1 = t_vtrie0.at(x2);
                                    auto x5 = ci_person_role_id[ci_off];
                                    if (chn_itrie0.contains(x5)) {
                                        auto &chn_itrie1 = chn_itrie0.at(x5);
                                        for (const auto &t_off : t_vtrie1) {
                                            mn_t_title = min(mn_t_title, t_title[t_off]);
                                        }
                                        auto &chn_off = chn_itrie1;
                                        mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                        auto &an_off = an_itrie1;
                                        mn_an_name = min(mn_an_name, an_name[an_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (an_isunq == 1 && t_isunq == 1 && chn_isunq == 0) {
            if (iter == 0)
                cout << "{an: i, t: i, chn: v}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_trie0.contains(x1)) {
                        auto &n_trie1 = n_trie0.at(x1);
                        auto x2 = ci_movie_id[ci_off];
                        if (interm0_trie0.contains(x2)) {
                            auto &interm0_trie1 = interm0_trie0.at(x2);
                            if (an_itrie0.contains(x1)) {
                                auto &an_itrie1 = an_itrie0.at(x1);
                                if (t_itrie0.contains(x2)) {
                                    auto &t_itrie1 = t_itrie0.at(x2);
                                    auto x5 = ci_person_role_id[ci_off];
                                    if (chn_vtrie0.contains(x5)) {
                                        auto &chn_vtrie1 = chn_vtrie0.at(x5);
                                        auto &t_off = t_itrie1;
                                        mn_t_title = min(mn_t_title, t_title[t_off]);
                                        for (const auto &chn_off : chn_vtrie1) {
                                            mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                        }
                                        auto &an_off = an_itrie1;
                                        mn_an_name = min(mn_an_name, an_name[an_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{an: i, t: i, chn: i}" << endl;
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (n_trie0.contains(x1)) {
                        auto &n_trie1 = n_trie0.at(x1);
                        auto x2 = ci_movie_id[ci_off];
                        if (interm0_trie0.contains(x2)) {
                            auto &interm0_trie1 = interm0_trie0.at(x2);
                            if (an_itrie0.contains(x1)) {
                                auto &an_itrie1 = an_itrie0.at(x1);
                                if (t_itrie0.contains(x2)) {
                                    auto &t_itrie1 = t_itrie0.at(x2);
                                    auto x5 = ci_person_role_id[ci_off];
                                    if (chn_itrie0.contains(x5)) {
                                        auto &chn_itrie1 = chn_itrie0.at(x5);
                                        auto &t_off = t_itrie1;
                                        mn_t_title = min(mn_t_title, t_title[t_off]);
                                        auto &chn_off = chn_itrie1;
                                        mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                        auto &an_off = an_itrie1;
                                        mn_an_name = min(mn_an_name, an_name[an_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_t_title << " | " << mn_chn_name << " | " << mn_an_name << endl;
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
