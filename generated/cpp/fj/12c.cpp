#include "load/12c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/t.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/mi_idx.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/mi.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/it2.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/it1.csv");
    load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/ct.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12c/cn.csv");
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
        auto mc_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto mc_itrie0 = phmap::flat_hash_map<int, int>();
        auto mc_isunq = build_trie(mc_vtrie0, mc_itrie0, mc_offsets, mc_movie_id);
        auto it2_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it2_trie0, it2_offsets, it2_id);
        auto it1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it1_trie0, it1_offsets, it1_id);
        auto ct_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(ct_trie0, ct_offsets, ct_id);
        auto cn_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto cn_itrie0 = phmap::flat_hash_map<int, int>();
        auto cn_isunq = build_trie(cn_vtrie0, cn_itrie0, cn_offsets, cn_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col1 = "zzzzzzzz";
        string mn_interm0_col3 = "zzzzzzzz";
        string mn_cn_name = "zzzzzzzz";
        if (interm0_isunq == 0 && mc_isunq == 0 && cn_isunq == 0) {
            if (iter == 0)
                cout << "{interm0: v, mc: v, cn: v}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_vtrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (it2_trie0.contains(x1)) {
                            auto &it2_trie1 = it2_trie0.at(x1);
                            auto x2 = mi_info_type_id[mi_off];
                            if (it1_trie0.contains(x2)) {
                                auto &it1_trie1 = it1_trie0.at(x2);
                                for (const auto &mc_off : mc_vtrie1) {
                                    auto x3 = mc_company_type_id[mc_off];
                                    if (ct_trie0.contains(x3)) {
                                        auto &ct_trie1 = ct_trie0.at(x3);
                                        auto x4 = mc_company_id[mc_off];
                                        if (cn_vtrie0.contains(x4)) {
                                            auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                            mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
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
        } else if (interm0_isunq == 0 && mc_isunq == 0 && cn_isunq == 1) {
            if (iter == 0)
                cout << "{interm0: v, mc: v, cn: i}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_vtrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (it2_trie0.contains(x1)) {
                            auto &it2_trie1 = it2_trie0.at(x1);
                            auto x2 = mi_info_type_id[mi_off];
                            if (it1_trie0.contains(x2)) {
                                auto &it1_trie1 = it1_trie0.at(x2);
                                for (const auto &mc_off : mc_vtrie1) {
                                    auto x3 = mc_company_type_id[mc_off];
                                    if (ct_trie0.contains(x3)) {
                                        auto &ct_trie1 = ct_trie0.at(x3);
                                        auto x4 = mc_company_id[mc_off];
                                        if (cn_itrie0.contains(x4)) {
                                            auto &cn_itrie1 = cn_itrie0.at(x4);
                                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                            mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
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
        } else if (interm0_isunq == 0 && mc_isunq == 1 && cn_isunq == 0) {
            if (iter == 0)
                cout << "{interm0: v, mc: i, cn: v}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_vtrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (it2_trie0.contains(x1)) {
                            auto &it2_trie1 = it2_trie0.at(x1);
                            auto x2 = mi_info_type_id[mi_off];
                            if (it1_trie0.contains(x2)) {
                                auto &it1_trie1 = it1_trie0.at(x2);
                                auto &mc_off = mc_itrie1;
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_vtrie0.contains(x4)) {
                                        auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
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
        } else if (interm0_isunq == 0 && mc_isunq == 1 && cn_isunq == 1) {
            if (iter == 0)
                cout << "{interm0: v, mc: i, cn: i}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_vtrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col2[interm0_off];
                        if (it2_trie0.contains(x1)) {
                            auto &it2_trie1 = it2_trie0.at(x1);
                            auto x2 = mi_info_type_id[mi_off];
                            if (it1_trie0.contains(x2)) {
                                auto &it1_trie1 = it1_trie0.at(x2);
                                auto &mc_off = mc_itrie1;
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_itrie0.contains(x4)) {
                                        auto &cn_itrie1 = cn_itrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                                        auto &cn_off = cn_itrie1;
                                        mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && mc_isunq == 0 && cn_isunq == 0) {
            if (iter == 0)
                cout << "{interm0: i, mc: v, cn: v}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_itrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (it2_trie0.contains(x1)) {
                        auto &it2_trie1 = it2_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it1_trie0.contains(x2)) {
                            auto &it1_trie1 = it1_trie0.at(x2);
                            for (const auto &mc_off : mc_vtrie1) {
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_vtrie0.contains(x4)) {
                                        auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
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
        } else if (interm0_isunq == 1 && mc_isunq == 0 && cn_isunq == 1) {
            if (iter == 0)
                cout << "{interm0: i, mc: v, cn: i}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_itrie0.contains(x0) && mc_vtrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_vtrie1 = mc_vtrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (it2_trie0.contains(x1)) {
                        auto &it2_trie1 = it2_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it1_trie0.contains(x2)) {
                            auto &it1_trie1 = it1_trie0.at(x2);
                            for (const auto &mc_off : mc_vtrie1) {
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_itrie0.contains(x4)) {
                                        auto &cn_itrie1 = cn_itrie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                                        auto &cn_off = cn_itrie1;
                                        mn_cn_name = min(mn_cn_name, cn_name[cn_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && mc_isunq == 1 && cn_isunq == 0) {
            if (iter == 0)
                cout << "{interm0: i, mc: i, cn: v}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_itrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (it2_trie0.contains(x1)) {
                        auto &it2_trie1 = it2_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it1_trie0.contains(x2)) {
                            auto &it1_trie1 = it1_trie0.at(x2);
                            auto &mc_off = mc_itrie1;
                            auto x3 = mc_company_type_id[mc_off];
                            if (ct_trie0.contains(x3)) {
                                auto &ct_trie1 = ct_trie0.at(x3);
                                auto x4 = mc_company_id[mc_off];
                                if (cn_vtrie0.contains(x4)) {
                                    auto &cn_vtrie1 = cn_vtrie0.at(x4);
                                    mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                    mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
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
                cout << "{interm0: i, mc: i, cn: i}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_movie_id[mi_off];
                if (interm0_itrie0.contains(x0) && mc_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &mc_itrie1 = mc_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col2[interm0_off];
                    if (it2_trie0.contains(x1)) {
                        auto &it2_trie1 = it2_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it1_trie0.contains(x2)) {
                            auto &it1_trie1 = it1_trie0.at(x2);
                            auto &mc_off = mc_itrie1;
                            auto x3 = mc_company_type_id[mc_off];
                            if (ct_trie0.contains(x3)) {
                                auto &ct_trie1 = ct_trie0.at(x3);
                                auto x4 = mc_company_id[mc_off];
                                if (cn_itrie0.contains(x4)) {
                                    auto &cn_itrie1 = cn_itrie0.at(x4);
                                    mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                    mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
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

        if (iter == 0)
            cout << mn_interm0_col1 << " | " << mn_interm0_col3 << " | " << mn_cn_name << endl;
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
