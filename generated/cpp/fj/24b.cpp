#include "load/24b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/t.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/mi.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/k.csv");
    load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/it.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/cn.csv");
    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/n.csv");
    load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
    load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/ci.csv");
    load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
    load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24b/rt.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        string IVs;
        timer.Reset();

        auto t_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto t_itrie0 = phmap::flat_hash_map<int, int>();
        auto t_isunq = build_trie(t_vtrie0, t_itrie0, t_offsets, t_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<int> interm0_offsets;
        cnt = 0;
        if (t_isunq == 0) {
            if (iter == 0)
                IVs += "{t: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (t_vtrie0.contains(x0)) {
                    auto &t_vtrie1 = t_vtrie0.at(x0);
                    for (const auto &t_off : t_vtrie1) {
                        interm0_col0.push_back(mk_movie_id[mk_off]);
                        interm0_col1.push_back(mk_keyword_id[mk_off]);
                        interm0_col2.push_back(t_title[t_off]);
                        interm0_offsets.push_back(cnt++);
                    }
                }
            }
        } else {
            if (iter == 0)
                IVs += "{t: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (t_itrie0.contains(x0)) {
                    auto &t_itrie1 = t_itrie0.at(x0);
                    auto &t_off = t_itrie1;
                    interm0_col0.push_back(mk_movie_id[mk_off]);
                    interm0_col1.push_back(mk_keyword_id[mk_off]);
                    interm0_col2.push_back(t_title[t_off]);
                    interm0_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto interm0_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm0_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm0_isunq = build_trie(interm0_vtrie0, interm0_itrie0, interm0_offsets, interm0_col0);
        auto mc_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto mc_itrie0 = phmap::flat_hash_map<int, int>();
        auto mc_isunq = build_trie(mc_vtrie0, mc_itrie0, mc_offsets, mc_movie_id);
        auto k_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(k_trie0, k_offsets, k_id);
        auto it_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it_trie0, it_offsets, it_id);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cn_trie0, cn_offsets, cn_id);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<int> interm1_col1;
        vector<int> interm1_col2;
        vector<string> interm1_col3;
        vector<int> interm1_col4;
        vector<int> interm1_offsets;
        cnt = 0;
        if (interm0_isunq == 0 && mc_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: v, mc: v}\n";
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_vtrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col1[interm0_off];
                        if (k_trie0.contains(x1)) {
                            auto &k_trie1 = k_trie0.at(x1);
                            auto x2 = mi_info_type_id[mi_off];
                            if (it_trie0.contains(x2)) {
                                auto &it_trie1 = it_trie0.at(x2);
                                for (const auto &mc_off : mc_vtrie1) {
                                    auto x3 = mc_company_id[mc_off];
                                    if (cn_trie0.contains(x3)) {
                                        auto &cn_trie1 = cn_trie0.at(x3);
                                        interm1_col0.push_back(mi_movie_id[mi_off]);
                                        interm1_col1.push_back(mi_info_type_id[mi_off]);
                                        interm1_col2.push_back(interm0_col1[interm0_off]);
                                        interm1_col3.push_back(interm0_col2[interm0_off]);
                                        interm1_col4.push_back(mc_company_id[mc_off]);
                                        interm1_offsets.push_back(cnt++);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 0 && mc_isunq == 1) {
            if (iter == 0)
                IVs += "{interm0: v, mc: i}\n";
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_vtrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col1[interm0_off];
                        if (k_trie0.contains(x1)) {
                            auto &k_trie1 = k_trie0.at(x1);
                            auto x2 = mi_info_type_id[mi_off];
                            if (it_trie0.contains(x2)) {
                                auto &it_trie1 = it_trie0.at(x2);
                                auto &mc_off = mc_itrie1;
                                auto x3 = mc_company_id[mc_off];
                                if (cn_trie0.contains(x3)) {
                                    auto &cn_trie1 = cn_trie0.at(x3);
                                    interm1_col0.push_back(mi_movie_id[mi_off]);
                                    interm1_col1.push_back(mi_info_type_id[mi_off]);
                                    interm1_col2.push_back(interm0_col1[interm0_off]);
                                    interm1_col3.push_back(interm0_col2[interm0_off]);
                                    interm1_col4.push_back(mc_company_id[mc_off]);
                                    interm1_offsets.push_back(cnt++);
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && mc_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: i, mc: v}\n";
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_itrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col1[interm0_off];
                    if (k_trie0.contains(x1)) {
                        auto &k_trie1 = k_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it_trie0.contains(x2)) {
                            auto &it_trie1 = it_trie0.at(x2);
                            for (const auto &mc_off : mc_vtrie1) {
                                auto x3 = mc_company_id[mc_off];
                                if (cn_trie0.contains(x3)) {
                                    auto &cn_trie1 = cn_trie0.at(x3);
                                    interm1_col0.push_back(mi_movie_id[mi_off]);
                                    interm1_col1.push_back(mi_info_type_id[mi_off]);
                                    interm1_col2.push_back(interm0_col1[interm0_off]);
                                    interm1_col3.push_back(interm0_col2[interm0_off]);
                                    interm1_col4.push_back(mc_company_id[mc_off]);
                                    interm1_offsets.push_back(cnt++);
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                IVs += "{interm0: i, mc: i}\n";
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_itrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col1[interm0_off];
                    if (k_trie0.contains(x1)) {
                        auto &k_trie1 = k_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it_trie0.contains(x2)) {
                            auto &it_trie1 = it_trie0.at(x2);
                            auto &mc_off = mc_itrie1;
                            auto x3 = mc_company_id[mc_off];
                            if (cn_trie0.contains(x3)) {
                                auto &cn_trie1 = cn_trie0.at(x3);
                                interm1_col0.push_back(mi_movie_id[mi_off]);
                                interm1_col1.push_back(mi_info_type_id[mi_off]);
                                interm1_col2.push_back(interm0_col1[interm0_off]);
                                interm1_col3.push_back(interm0_col2[interm0_off]);
                                interm1_col4.push_back(mc_company_id[mc_off]);
                                interm1_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto an_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(an_trie0, an_offsets, an_person_id);
        timer.StoreElapsedTime(4);

        vector<int> interm2_col0;
        vector<string> interm2_col1;
        vector<int> interm2_offsets;
        cnt = 0;
        for (const auto &n_off : n_offsets) {
            auto x0 = n_id[n_off];
            if (an_trie0.contains(x0)) {
                auto &an_trie1 = an_trie0.at(x0);
                interm2_col0.push_back(n_id[n_off]);
                interm2_col1.push_back(n_name[n_off]);
                interm2_offsets.push_back(cnt++);
            }
        }
        timer.StoreElapsedTime(5);

        auto rt_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(rt_trie0, rt_offsets, rt_id);
        auto interm1_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm1_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm1_isunq = build_trie(interm1_vtrie0, interm1_itrie0, interm1_offsets, interm1_col0);
        auto interm2_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm2_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm2_isunq = build_trie(interm2_vtrie0, interm2_itrie0, interm2_offsets, interm2_col0);
        auto chn_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto chn_itrie0 = phmap::flat_hash_map<int, int>();
        auto chn_isunq = build_trie(chn_vtrie0, chn_itrie0, chn_offsets, chn_id);
        timer.StoreElapsedTime(6);

        string mn_chn_name = "zzzzzzzz";
        string mn_interm2_col1 = "zzzzzzzz";
        string mn_interm1_col3 = "zzzzzzzz";
        if (interm1_isunq == 0 && interm2_isunq == 0 && chn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm1: v, interm2: v, chn: v}\n";
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_vtrie0.contains(x1)) {
                        auto &interm1_vtrie1 = interm1_vtrie0.at(x1);
                        auto x2 = ci_person_id[ci_off];
                        if (interm2_vtrie0.contains(x2)) {
                            auto &interm2_vtrie1 = interm2_vtrie0.at(x2);
                            auto x3 = ci_person_role_id[ci_off];
                            if (chn_vtrie0.contains(x3)) {
                                auto &chn_vtrie1 = chn_vtrie0.at(x3);
                                for (const auto &chn_off : chn_vtrie1) {
                                    mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                }
                                for (const auto &interm2_off : interm2_vtrie1) {
                                    mn_interm2_col1 = min(mn_interm2_col1, interm2_col1[interm2_off]);
                                }
                                for (const auto &interm1_off : interm1_vtrie1) {
                                    mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm1_isunq == 0 && interm2_isunq == 0 && chn_isunq == 1) {
            if (iter == 0)
                IVs += "{interm1: v, interm2: v, chn: i}\n";
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_vtrie0.contains(x1)) {
                        auto &interm1_vtrie1 = interm1_vtrie0.at(x1);
                        auto x2 = ci_person_id[ci_off];
                        if (interm2_vtrie0.contains(x2)) {
                            auto &interm2_vtrie1 = interm2_vtrie0.at(x2);
                            auto x3 = ci_person_role_id[ci_off];
                            if (chn_itrie0.contains(x3)) {
                                auto &chn_itrie1 = chn_itrie0.at(x3);
                                auto &chn_off = chn_itrie1;
                                mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                for (const auto &interm2_off : interm2_vtrie1) {
                                    mn_interm2_col1 = min(mn_interm2_col1, interm2_col1[interm2_off]);
                                }
                                for (const auto &interm1_off : interm1_vtrie1) {
                                    mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm1_isunq == 0 && interm2_isunq == 1 && chn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm1: v, interm2: i, chn: v}\n";
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_vtrie0.contains(x1)) {
                        auto &interm1_vtrie1 = interm1_vtrie0.at(x1);
                        auto x2 = ci_person_id[ci_off];
                        if (interm2_itrie0.contains(x2)) {
                            auto &interm2_itrie1 = interm2_itrie0.at(x2);
                            auto x3 = ci_person_role_id[ci_off];
                            if (chn_vtrie0.contains(x3)) {
                                auto &chn_vtrie1 = chn_vtrie0.at(x3);
                                for (const auto &chn_off : chn_vtrie1) {
                                    mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                }
                                auto &interm2_off = interm2_itrie1;
                                mn_interm2_col1 = min(mn_interm2_col1, interm2_col1[interm2_off]);
                                for (const auto &interm1_off : interm1_vtrie1) {
                                    mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm1_isunq == 0 && interm2_isunq == 1 && chn_isunq == 1) {
            if (iter == 0)
                IVs += "{interm1: v, interm2: i, chn: i}\n";
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_vtrie0.contains(x1)) {
                        auto &interm1_vtrie1 = interm1_vtrie0.at(x1);
                        auto x2 = ci_person_id[ci_off];
                        if (interm2_itrie0.contains(x2)) {
                            auto &interm2_itrie1 = interm2_itrie0.at(x2);
                            auto x3 = ci_person_role_id[ci_off];
                            if (chn_itrie0.contains(x3)) {
                                auto &chn_itrie1 = chn_itrie0.at(x3);
                                auto &chn_off = chn_itrie1;
                                mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                auto &interm2_off = interm2_itrie1;
                                mn_interm2_col1 = min(mn_interm2_col1, interm2_col1[interm2_off]);
                                for (const auto &interm1_off : interm1_vtrie1) {
                                    mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm1_isunq == 1 && interm2_isunq == 0 && chn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm1: i, interm2: v, chn: v}\n";
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_itrie0.contains(x1)) {
                        auto &interm1_itrie1 = interm1_itrie0.at(x1);
                        auto x2 = ci_person_id[ci_off];
                        if (interm2_vtrie0.contains(x2)) {
                            auto &interm2_vtrie1 = interm2_vtrie0.at(x2);
                            auto x3 = ci_person_role_id[ci_off];
                            if (chn_vtrie0.contains(x3)) {
                                auto &chn_vtrie1 = chn_vtrie0.at(x3);
                                for (const auto &chn_off : chn_vtrie1) {
                                    mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                }
                                for (const auto &interm2_off : interm2_vtrie1) {
                                    mn_interm2_col1 = min(mn_interm2_col1, interm2_col1[interm2_off]);
                                }
                                auto &interm1_off = interm1_itrie1;
                                mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
                            }
                        }
                    }
                }
            }
        } else if (interm1_isunq == 1 && interm2_isunq == 0 && chn_isunq == 1) {
            if (iter == 0)
                IVs += "{interm1: i, interm2: v, chn: i}\n";
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_itrie0.contains(x1)) {
                        auto &interm1_itrie1 = interm1_itrie0.at(x1);
                        auto x2 = ci_person_id[ci_off];
                        if (interm2_vtrie0.contains(x2)) {
                            auto &interm2_vtrie1 = interm2_vtrie0.at(x2);
                            auto x3 = ci_person_role_id[ci_off];
                            if (chn_itrie0.contains(x3)) {
                                auto &chn_itrie1 = chn_itrie0.at(x3);
                                auto &chn_off = chn_itrie1;
                                mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                for (const auto &interm2_off : interm2_vtrie1) {
                                    mn_interm2_col1 = min(mn_interm2_col1, interm2_col1[interm2_off]);
                                }
                                auto &interm1_off = interm1_itrie1;
                                mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
                            }
                        }
                    }
                }
            }
        } else if (interm1_isunq == 1 && interm2_isunq == 1 && chn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm1: i, interm2: i, chn: v}\n";
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_itrie0.contains(x1)) {
                        auto &interm1_itrie1 = interm1_itrie0.at(x1);
                        auto x2 = ci_person_id[ci_off];
                        if (interm2_itrie0.contains(x2)) {
                            auto &interm2_itrie1 = interm2_itrie0.at(x2);
                            auto x3 = ci_person_role_id[ci_off];
                            if (chn_vtrie0.contains(x3)) {
                                auto &chn_vtrie1 = chn_vtrie0.at(x3);
                                for (const auto &chn_off : chn_vtrie1) {
                                    mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                }
                                auto &interm2_off = interm2_itrie1;
                                mn_interm2_col1 = min(mn_interm2_col1, interm2_col1[interm2_off]);
                                auto &interm1_off = interm1_itrie1;
                                mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
                            }
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                IVs += "{interm1: i, interm2: i, chn: i}\n";
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_role_id[ci_off];
                if (rt_trie0.contains(x0)) {
                    auto &rt_trie1 = rt_trie0.at(x0);
                    auto x1 = ci_movie_id[ci_off];
                    if (interm1_itrie0.contains(x1)) {
                        auto &interm1_itrie1 = interm1_itrie0.at(x1);
                        auto x2 = ci_person_id[ci_off];
                        if (interm2_itrie0.contains(x2)) {
                            auto &interm2_itrie1 = interm2_itrie0.at(x2);
                            auto x3 = ci_person_role_id[ci_off];
                            if (chn_itrie0.contains(x3)) {
                                auto &chn_itrie1 = chn_itrie0.at(x3);
                                auto &chn_off = chn_itrie1;
                                mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                                auto &interm2_off = interm2_itrie1;
                                mn_interm2_col1 = min(mn_interm2_col1, interm2_col1[interm2_off]);
                                auto &interm1_off = interm1_itrie1;
                                mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(7);

        if (iter == 0) {
            cout << mn_chn_name << " | " << mn_interm2_col1 << " | " << mn_interm1_col3 << endl;
            cout << IVs;
        }
        cout << "*" << " " << flush;
    }
    cout << endl;

    vector<double> tm{0};
    for (int i = 0; i < 2 * 4; ++i)
        tm.push_back(timer.GetMean(i));
    for (int i = 0; i < 2 * 4; i += 2) {
        cout << tm[i + 1] - tm[i] << " + ";
        cout << tm[i + 2] - tm[i + 1] << " = ";
        cout << tm[i + 2] - tm[i] << " ms" << endl;
    }
    cout << tm[2 * 4] << " ms" << endl;
}
