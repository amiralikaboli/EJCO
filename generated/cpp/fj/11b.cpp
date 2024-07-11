#include "load/11b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11b/t.csv");
    load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11b/mc.csv");
    load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11b/lt.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11b/k.csv");
    load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11b/ct.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11b/cn.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        string IVs;
        timer.Reset();

        auto ml_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto ml_itrie0 = phmap::flat_hash_map<int, int>();
        auto ml_isunq = build_trie(ml_vtrie0, ml_itrie0, ml_offsets, ml_movie_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<int> interm0_offsets;
        cnt = 0;
        if (ml_isunq == 0) {
            if (iter == 0)
                IVs += "{ml: v}\n";
            for (const auto &t_off : t_offsets) {
                auto x0 = t_id[t_off];
                if (ml_vtrie0.contains(x0)) {
                    auto &ml_vtrie1 = ml_vtrie0.at(x0);
                    for (const auto &ml_off : ml_vtrie1) {
                        interm0_col0.push_back(t_id[t_off]);
                        interm0_col1.push_back(t_title[t_off]);
                        interm0_col2.push_back(ml_link_type_id[ml_off]);
                        interm0_offsets.push_back(cnt++);
                    }
                }
            }
        } else {
            if (iter == 0)
                IVs += "{ml: i}\n";
            for (const auto &t_off : t_offsets) {
                auto x0 = t_id[t_off];
                if (ml_itrie0.contains(x0)) {
                    auto &ml_itrie1 = ml_itrie0.at(x0);
                    auto &ml_off = ml_itrie1;
                    interm0_col0.push_back(t_id[t_off]);
                    interm0_col1.push_back(t_title[t_off]);
                    interm0_col2.push_back(ml_link_type_id[ml_off]);
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
        auto lt_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto lt_itrie0 = phmap::flat_hash_map<int, int>();
        auto lt_isunq = build_trie(lt_vtrie0, lt_itrie0, lt_offsets, lt_id);
        auto k_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(k_trie0, k_offsets, k_id);
        auto ct_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(ct_trie0, ct_offsets, ct_id);
        auto cn_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto cn_itrie0 = phmap::flat_hash_map<int, int>();
        auto cn_isunq = build_trie(cn_vtrie0, cn_itrie0, cn_offsets, cn_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col1 = "zzzzzzzz";
        string mn_lt_link = "zzzzzzzz";
        string mn_cn_name = "zzzzzzzz";
        if (interm0_isunq == 0 && mc_isunq == 0 && lt_isunq == 0 && cn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: v, mc: v, lt: v, cn: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (lt_vtrie0.contains(x1)) {
                            auto &lt_vtrie1 = lt_vtrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                for (const auto &mc_off : mc_vtrie1) {
                                    auto x3 = mc_company_type_id[mc_off];
                                    if (ct_trie0.contains(x3)) {
                                        auto &ct_trie1 = ct_trie0.at(x3);
                                        auto x4 = mc_company_id[mc_off];
                                        if (cn_vtrie0.contains(x4)) {
                                            auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                            for (const auto &lt_off : lt_vtrie1) {
                                                mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                            }
                                            for (const auto &cn_off : cn_vtrie1) {
                                                mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 0 && mc_isunq == 0 && lt_isunq == 0 && cn_isunq == 1) {
            if (iter == 0)
                IVs += "{interm0: v, mc: v, lt: v, cn: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (lt_vtrie0.contains(x1)) {
                            auto &lt_vtrie1 = lt_vtrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                for (const auto &mc_off : mc_vtrie1) {
                                    auto x3 = mc_company_type_id[mc_off];
                                    if (ct_trie0.contains(x3)) {
                                        auto &ct_trie1 = ct_trie0.at(x3);
                                        auto x4 = mc_company_id[mc_off];
                                        if (cn_itrie0.contains(x4)) {
                                            auto &cn_itrie1 = cn_itrie0.at(x4);
                                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                            for (const auto &lt_off : lt_vtrie1) {
                                                mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                            }
                                            auto &cn_off = cn_itrie1;
                                            mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 0 && mc_isunq == 0 && lt_isunq == 1 && cn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: v, mc: v, lt: i, cn: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (lt_itrie0.contains(x1)) {
                            auto &lt_itrie1 = lt_itrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                for (const auto &mc_off : mc_vtrie1) {
                                    auto x3 = mc_company_type_id[mc_off];
                                    if (ct_trie0.contains(x3)) {
                                        auto &ct_trie1 = ct_trie0.at(x3);
                                        auto x4 = mc_company_id[mc_off];
                                        if (cn_vtrie0.contains(x4)) {
                                            auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                            auto &lt_off = lt_itrie1;
                                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                            for (const auto &cn_off : cn_vtrie1) {
                                                mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 0 && mc_isunq == 0 && lt_isunq == 1 && cn_isunq == 1) {
            if (iter == 0)
                IVs += "{interm0: v, mc: v, lt: i, cn: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (lt_itrie0.contains(x1)) {
                            auto &lt_itrie1 = lt_itrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                for (const auto &mc_off : mc_vtrie1) {
                                    auto x3 = mc_company_type_id[mc_off];
                                    if (ct_trie0.contains(x3)) {
                                        auto &ct_trie1 = ct_trie0.at(x3);
                                        auto x4 = mc_company_id[mc_off];
                                        if (cn_itrie0.contains(x4)) {
                                            auto &cn_itrie1 = cn_itrie0.at(x4);
                                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                            auto &lt_off = lt_itrie1;
                                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                            auto &cn_off = cn_itrie1;
                                            mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 0 && mc_isunq == 1 && lt_isunq == 0 && cn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: v, mc: i, lt: v, cn: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (lt_vtrie0.contains(x1)) {
                            auto &lt_vtrie1 = lt_vtrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                auto &mc_off = mc_itrie1;
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_vtrie0.contains(x4)) {
                                        auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        for (const auto &lt_off : lt_vtrie1) {
                                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                        }
                                        for (const auto &cn_off : cn_vtrie1) {
                                            mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 0 && mc_isunq == 1 && lt_isunq == 0 && cn_isunq == 1) {
            if (iter == 0)
                IVs += "{interm0: v, mc: i, lt: v, cn: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (lt_vtrie0.contains(x1)) {
                            auto &lt_vtrie1 = lt_vtrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                auto &mc_off = mc_itrie1;
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_itrie0.contains(x4)) {
                                        auto &cn_itrie1 = cn_itrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        for (const auto &lt_off : lt_vtrie1) {
                                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                        }
                                        auto &cn_off = cn_itrie1;
                                        mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 0 && mc_isunq == 1 && lt_isunq == 1 && cn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: v, mc: i, lt: i, cn: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (lt_itrie0.contains(x1)) {
                            auto &lt_itrie1 = lt_itrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                auto &mc_off = mc_itrie1;
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_vtrie0.contains(x4)) {
                                        auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        auto &lt_off = lt_itrie1;
                                        mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                        for (const auto &cn_off : cn_vtrie1) {
                                            mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 0 && mc_isunq == 1 && lt_isunq == 1 && cn_isunq == 1) {
            if (iter == 0)
                IVs += "{interm0: v, mc: i, lt: i, cn: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (lt_itrie0.contains(x1)) {
                            auto &lt_itrie1 = lt_itrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                auto &mc_off = mc_itrie1;
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_itrie0.contains(x4)) {
                                        auto &cn_itrie1 = cn_itrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        auto &lt_off = lt_itrie1;
                                        mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                        auto &cn_off = cn_itrie1;
                                        mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && mc_isunq == 0 && lt_isunq == 0 && cn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: i, mc: v, lt: v, cn: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (lt_vtrie0.contains(x1)) {
                        auto &lt_vtrie1 = lt_vtrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            for (const auto &mc_off : mc_vtrie1) {
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_vtrie0.contains(x4)) {
                                        auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        for (const auto &lt_off : lt_vtrie1) {
                                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                        }
                                        for (const auto &cn_off : cn_vtrie1) {
                                            mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && mc_isunq == 0 && lt_isunq == 0 && cn_isunq == 1) {
            if (iter == 0)
                IVs += "{interm0: i, mc: v, lt: v, cn: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (lt_vtrie0.contains(x1)) {
                        auto &lt_vtrie1 = lt_vtrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            for (const auto &mc_off : mc_vtrie1) {
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_itrie0.contains(x4)) {
                                        auto &cn_itrie1 = cn_itrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        for (const auto &lt_off : lt_vtrie1) {
                                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                        }
                                        auto &cn_off = cn_itrie1;
                                        mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && mc_isunq == 0 && lt_isunq == 1 && cn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: i, mc: v, lt: i, cn: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (lt_itrie0.contains(x1)) {
                        auto &lt_itrie1 = lt_itrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            for (const auto &mc_off : mc_vtrie1) {
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_vtrie0.contains(x4)) {
                                        auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        auto &lt_off = lt_itrie1;
                                        mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                        for (const auto &cn_off : cn_vtrie1) {
                                            mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && mc_isunq == 0 && lt_isunq == 1 && cn_isunq == 1) {
            if (iter == 0)
                IVs += "{interm0: i, mc: v, lt: i, cn: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (lt_itrie0.contains(x1)) {
                        auto &lt_itrie1 = lt_itrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            for (const auto &mc_off : mc_vtrie1) {
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_itrie0.contains(x4)) {
                                        auto &cn_itrie1 = cn_itrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        auto &lt_off = lt_itrie1;
                                        mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                        auto &cn_off = cn_itrie1;
                                        mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && mc_isunq == 1 && lt_isunq == 0 && cn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: i, mc: i, lt: v, cn: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (lt_vtrie0.contains(x1)) {
                        auto &lt_vtrie1 = lt_vtrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            auto &mc_off = mc_itrie1;
                            auto x3 = mc_company_type_id[mc_off];
                            if (ct_trie0.contains(x3)) {
                                auto &ct_trie1 = ct_trie0.at(x3);
                                auto x4 = mc_company_id[mc_off];
                                if (cn_vtrie0.contains(x4)) {
                                    auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                    mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                    for (const auto &lt_off : lt_vtrie1) {
                                        mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                    }
                                    for (const auto &cn_off : cn_vtrie1) {
                                        mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && mc_isunq == 1 && lt_isunq == 0 && cn_isunq == 1) {
            if (iter == 0)
                IVs += "{interm0: i, mc: i, lt: v, cn: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (lt_vtrie0.contains(x1)) {
                        auto &lt_vtrie1 = lt_vtrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            auto &mc_off = mc_itrie1;
                            auto x3 = mc_company_type_id[mc_off];
                            if (ct_trie0.contains(x3)) {
                                auto &ct_trie1 = ct_trie0.at(x3);
                                auto x4 = mc_company_id[mc_off];
                                if (cn_itrie0.contains(x4)) {
                                    auto &cn_itrie1 = cn_itrie0.at(x4);
                                    mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                    for (const auto &lt_off : lt_vtrie1) {
                                        mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                    }
                                    auto &cn_off = cn_itrie1;
                                    mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && mc_isunq == 1 && lt_isunq == 1 && cn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: i, mc: i, lt: i, cn: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (lt_itrie0.contains(x1)) {
                        auto &lt_itrie1 = lt_itrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            auto &mc_off = mc_itrie1;
                            auto x3 = mc_company_type_id[mc_off];
                            if (ct_trie0.contains(x3)) {
                                auto &ct_trie1 = ct_trie0.at(x3);
                                auto x4 = mc_company_id[mc_off];
                                if (cn_vtrie0.contains(x4)) {
                                    auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                    mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                    auto &lt_off = lt_itrie1;
                                    mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                    for (const auto &cn_off : cn_vtrie1) {
                                        mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                IVs += "{interm0: i, mc: i, lt: i, cn: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (lt_itrie0.contains(x1)) {
                        auto &lt_itrie1 = lt_itrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            auto &mc_off = mc_itrie1;
                            auto x3 = mc_company_type_id[mc_off];
                            if (ct_trie0.contains(x3)) {
                                auto &ct_trie1 = ct_trie0.at(x3);
                                auto x4 = mc_company_id[mc_off];
                                if (cn_itrie0.contains(x4)) {
                                    auto &cn_itrie1 = cn_itrie0.at(x4);
                                    mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                    auto &lt_off = lt_itrie1;
                                    mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                    auto &cn_off = cn_itrie1;
                                    mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                }
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0) {
            cout << mn_interm0_col1 << " | " << mn_lt_link << " | " << mn_cn_name << endl;
            cout << IVs;
        }
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
