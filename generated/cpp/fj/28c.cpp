#include "load/28c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
    load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28c/cct1.csv");
    load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28c/cct2.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28c/mi_idx.csv");
    load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28c/it2.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28c/t.csv");
    load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28c/kt.csv");
    load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28c/mc.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28c/cn.csv");
    load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28c/k.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28c/mi.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/28c/it1.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cct1_trie0, cct1_offsets, cct1_id);
        auto cct2_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cct2_trie0, cct2_offsets, cct2_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<int> interm0_col2;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &cc_off : cc_offsets) {
            auto x0 = cc_subject_id[cc_off];
            if (cct1_trie0.contains(x0)) {
                auto &cct1_trie1 = cct1_trie0.at(x0);
                auto x1 = cc_status_id[cc_off];
                if (cct2_trie0.contains(x1)) {
                    auto &cct2_trie1 = cct2_trie0.at(x1);
                    interm0_col0.push_back(cc_subject_id[cc_off]);
                    interm0_col1.push_back(cc_status_id[cc_off]);
                    interm0_col2.push_back(cc_movie_id[cc_off]);
                    interm0_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto it2_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it2_trie0, it2_offsets, it2_id);
        auto interm0_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(interm0_trie0, interm0_offsets, interm0_col2);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<int> interm1_col1;
        vector<string> interm1_col2;
        vector<int> interm1_offsets;
        cnt = 0;
        for (const auto &mi_idx_off : mi_idx_offsets) {
            auto x0 = mi_idx_info_type_id[mi_idx_off];
            if (it2_trie0.contains(x0)) {
                auto &it2_trie1 = it2_trie0.at(x0);
                auto x1 = mi_idx_movie_id[mi_idx_off];
                if (interm0_trie0.contains(x1)) {
                    auto &interm0_trie1 = interm0_trie0.at(x1);
                    interm1_col0.push_back(mi_idx_info_type_id[mi_idx_off]);
                    interm1_col1.push_back(mi_idx_movie_id[mi_idx_off]);
                    interm1_col2.push_back(mi_idx_info[mi_idx_off]);
                    interm1_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto kt_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(kt_trie0, kt_offsets, kt_id);
        auto interm1_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm1_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm1_isunq = build_trie(interm1_vtrie0, interm1_itrie0, interm1_offsets, interm1_col1);
        timer.StoreElapsedTime(4);

        vector<int> interm2_col0;
        vector<int> interm2_col1;
        vector<string> interm2_col2;
        vector<string> interm2_col4;
        vector<int> interm2_offsets;
        cnt = 0;
        if (interm1_isunq == 0) {
            if (iter == 0)
                cout << "{interm1: v}" << endl;
            for (const auto &t_off : t_offsets) {
                auto x0 = t_kind_id[t_off];
                if (kt_trie0.contains(x0)) {
                    auto &kt_trie1 = kt_trie0.at(x0);
                    auto x1 = t_id[t_off];
                    if (interm1_vtrie0.contains(x1)) {
                        auto &interm1_vtrie1 = interm1_vtrie0.at(x1);
                        for (const auto &interm1_off : interm1_vtrie1) {
                            interm2_col0.push_back(t_kind_id[t_off]);
                            interm2_col1.push_back(t_id[t_off]);
                            interm2_col2.push_back(t_title[t_off]);
                            interm2_col4.push_back(interm1_col2[interm1_off]);
                            interm2_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{interm1: i}" << endl;
            for (const auto &t_off : t_offsets) {
                auto x0 = t_kind_id[t_off];
                if (kt_trie0.contains(x0)) {
                    auto &kt_trie1 = kt_trie0.at(x0);
                    auto x1 = t_id[t_off];
                    if (interm1_itrie0.contains(x1)) {
                        auto &interm1_itrie1 = interm1_itrie0.at(x1);
                        auto &interm1_off = interm1_itrie1;
                        interm2_col0.push_back(t_kind_id[t_off]);
                        interm2_col1.push_back(t_id[t_off]);
                        interm2_col2.push_back(t_title[t_off]);
                        interm2_col4.push_back(interm1_col2[interm1_off]);
                        interm2_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(5);

        auto ct_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(ct_trie0, ct_offsets, ct_id);
        auto interm2_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm2_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm2_isunq = build_trie(interm2_vtrie0, interm2_itrie0, interm2_offsets, interm2_col1);
        auto cn_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto cn_itrie0 = phmap::flat_hash_map<int, int>();
        auto cn_isunq = build_trie(cn_vtrie0, cn_itrie0, cn_offsets, cn_id);
        timer.StoreElapsedTime(6);

        vector<int> interm3_col0;
        vector<int> interm3_col1;
        vector<int> interm3_col2;
        vector<string> interm3_col3;
        vector<string> interm3_col5;
        vector<string> interm3_col7;
        vector<int> interm3_offsets;
        cnt = 0;
        if (interm2_isunq == 0 && cn_isunq == 0) {
            if (iter == 0)
                cout << "{interm2: v, cn: v}" << endl;
            for (const auto &mc_off : mc_offsets) {
                auto x0 = mc_company_type_id[mc_off];
                if (ct_trie0.contains(x0)) {
                    auto &ct_trie1 = ct_trie0.at(x0);
                    auto x1 = mc_movie_id[mc_off];
                    if (interm2_vtrie0.contains(x1)) {
                        auto &interm2_vtrie1 = interm2_vtrie0.at(x1);
                        auto x2 = mc_company_id[mc_off];
                        if (cn_vtrie0.contains(x2)) {
                            auto &cn_vtrie1 = cn_vtrie0.at(x2);
                            for (const auto &cn_off : cn_vtrie1) {
                                for (const auto &interm2_off : interm2_vtrie1) {
                                    interm3_col0.push_back(mc_company_id[mc_off]);
                                    interm3_col1.push_back(mc_company_type_id[mc_off]);
                                    interm3_col2.push_back(mc_movie_id[mc_off]);
                                    interm3_col3.push_back(cn_name[cn_off]);
                                    interm3_col5.push_back(interm2_col2[interm2_off]);
                                    interm3_col7.push_back(interm2_col4[interm2_off]);
                                    interm3_offsets.push_back(cnt++);
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm2_isunq == 0 && cn_isunq == 1) {
            if (iter == 0)
                cout << "{interm2: v, cn: i}" << endl;
            for (const auto &mc_off : mc_offsets) {
                auto x0 = mc_company_type_id[mc_off];
                if (ct_trie0.contains(x0)) {
                    auto &ct_trie1 = ct_trie0.at(x0);
                    auto x1 = mc_movie_id[mc_off];
                    if (interm2_vtrie0.contains(x1)) {
                        auto &interm2_vtrie1 = interm2_vtrie0.at(x1);
                        auto x2 = mc_company_id[mc_off];
                        if (cn_itrie0.contains(x2)) {
                            auto &cn_itrie1 = cn_itrie0.at(x2);
                            auto &cn_off = cn_itrie1;
                            for (const auto &interm2_off : interm2_vtrie1) {
                                interm3_col0.push_back(mc_company_id[mc_off]);
                                interm3_col1.push_back(mc_company_type_id[mc_off]);
                                interm3_col2.push_back(mc_movie_id[mc_off]);
                                interm3_col3.push_back(cn_name[cn_off]);
                                interm3_col5.push_back(interm2_col2[interm2_off]);
                                interm3_col7.push_back(interm2_col4[interm2_off]);
                                interm3_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        } else if (interm2_isunq == 1 && cn_isunq == 0) {
            if (iter == 0)
                cout << "{interm2: i, cn: v}" << endl;
            for (const auto &mc_off : mc_offsets) {
                auto x0 = mc_company_type_id[mc_off];
                if (ct_trie0.contains(x0)) {
                    auto &ct_trie1 = ct_trie0.at(x0);
                    auto x1 = mc_movie_id[mc_off];
                    if (interm2_itrie0.contains(x1)) {
                        auto &interm2_itrie1 = interm2_itrie0.at(x1);
                        auto x2 = mc_company_id[mc_off];
                        if (cn_vtrie0.contains(x2)) {
                            auto &cn_vtrie1 = cn_vtrie0.at(x2);
                            for (const auto &cn_off : cn_vtrie1) {
                                auto &interm2_off = interm2_itrie1;
                                interm3_col0.push_back(mc_company_id[mc_off]);
                                interm3_col1.push_back(mc_company_type_id[mc_off]);
                                interm3_col2.push_back(mc_movie_id[mc_off]);
                                interm3_col3.push_back(cn_name[cn_off]);
                                interm3_col5.push_back(interm2_col2[interm2_off]);
                                interm3_col7.push_back(interm2_col4[interm2_off]);
                                interm3_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{interm2: i, cn: i}" << endl;
            for (const auto &mc_off : mc_offsets) {
                auto x0 = mc_company_type_id[mc_off];
                if (ct_trie0.contains(x0)) {
                    auto &ct_trie1 = ct_trie0.at(x0);
                    auto x1 = mc_movie_id[mc_off];
                    if (interm2_itrie0.contains(x1)) {
                        auto &interm2_itrie1 = interm2_itrie0.at(x1);
                        auto x2 = mc_company_id[mc_off];
                        if (cn_itrie0.contains(x2)) {
                            auto &cn_itrie1 = cn_itrie0.at(x2);
                            auto &cn_off = cn_itrie1;
                            auto &interm2_off = interm2_itrie1;
                            interm3_col0.push_back(mc_company_id[mc_off]);
                            interm3_col1.push_back(mc_company_type_id[mc_off]);
                            interm3_col2.push_back(mc_movie_id[mc_off]);
                            interm3_col3.push_back(cn_name[cn_off]);
                            interm3_col5.push_back(interm2_col2[interm2_off]);
                            interm3_col7.push_back(interm2_col4[interm2_off]);
                            interm3_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(7);

        auto k_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(k_trie0, k_offsets, k_id);
        auto interm3_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm3_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm3_isunq = build_trie(interm3_vtrie0, interm3_itrie0, interm3_offsets, interm3_col2);
        timer.StoreElapsedTime(8);

        vector<int> interm4_col0;
        vector<int> interm4_col1;
        vector<string> interm4_col4;
        vector<string> interm4_col6;
        vector<string> interm4_col8;
        vector<int> interm4_offsets;
        cnt = 0;
        if (interm3_isunq == 0) {
            if (iter == 0)
                cout << "{interm3: v}" << endl;
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (interm3_vtrie0.contains(x1)) {
                        auto &interm3_vtrie1 = interm3_vtrie0.at(x1);
                        for (const auto &interm3_off : interm3_vtrie1) {
                            interm4_col0.push_back(mk_keyword_id[mk_off]);
                            interm4_col1.push_back(mk_movie_id[mk_off]);
                            interm4_col4.push_back(interm3_col3[interm3_off]);
                            interm4_col6.push_back(interm3_col5[interm3_off]);
                            interm4_col8.push_back(interm3_col7[interm3_off]);
                            interm4_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{interm3: i}" << endl;
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (interm3_itrie0.contains(x1)) {
                        auto &interm3_itrie1 = interm3_itrie0.at(x1);
                        auto &interm3_off = interm3_itrie1;
                        interm4_col0.push_back(mk_keyword_id[mk_off]);
                        interm4_col1.push_back(mk_movie_id[mk_off]);
                        interm4_col4.push_back(interm3_col3[interm3_off]);
                        interm4_col6.push_back(interm3_col5[interm3_off]);
                        interm4_col8.push_back(interm3_col7[interm3_off]);
                        interm4_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(9);

        auto it1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it1_trie0, it1_offsets, it1_id);
        auto interm4_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm4_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm4_isunq = build_trie(interm4_vtrie0, interm4_itrie0, interm4_offsets, interm4_col1);
        timer.StoreElapsedTime(10);

        string mn_interm4_col4 = "zzzzzzzz";
        string mn_interm4_col6 = "zzzzzzzz";
        string mn_interm4_col8 = "zzzzzzzz";
        if (interm4_isunq == 0) {
            if (iter == 0)
                cout << "{interm4: v}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_info_type_id[mi_off];
                if (it1_trie0.contains(x0)) {
                    auto &it1_trie1 = it1_trie0.at(x0);
                    auto x1 = mi_movie_id[mi_off];
                    if (interm4_vtrie0.contains(x1)) {
                        auto &interm4_vtrie1 = interm4_vtrie0.at(x1);
                        for (const auto &interm4_off : interm4_vtrie1) {
                            mn_interm4_col4 = min(mn_interm4_col4, interm4_col4[interm4_off]);
                            mn_interm4_col6 = min(mn_interm4_col6, interm4_col6[interm4_off]);
                            mn_interm4_col8 = min(mn_interm4_col8, interm4_col8[interm4_off]);
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                cout << "{interm4: i}" << endl;
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_info_type_id[mi_off];
                if (it1_trie0.contains(x0)) {
                    auto &it1_trie1 = it1_trie0.at(x0);
                    auto x1 = mi_movie_id[mi_off];
                    if (interm4_itrie0.contains(x1)) {
                        auto &interm4_itrie1 = interm4_itrie0.at(x1);
                        auto &interm4_off = interm4_itrie1;
                        mn_interm4_col4 = min(mn_interm4_col4, interm4_col4[interm4_off]);
                        mn_interm4_col6 = min(mn_interm4_col6, interm4_col6[interm4_off]);
                        mn_interm4_col8 = min(mn_interm4_col8, interm4_col8[interm4_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(11);

        if (iter == 0)
            cout << mn_interm4_col4 << " | " << mn_interm4_col6 << " | " << mn_interm4_col8 << endl;
        cout << "*" << " " << flush;
    }
    cout << endl;

    vector<double> tm{0};
    for (int i = 0; i < 2 * 6; ++i)
        tm.push_back(timer.GetMean(i));
    for (int i = 0; i < 2 * 6; i += 2) {
        cout << tm[i + 1] - tm[i] << " + ";
        cout << tm[i + 2] - tm[i + 1] << " = ";
        cout << tm[i + 2] - tm[i] << " ms" << endl;
    }
    cout << tm[2 * 6] << " ms" << endl;
}
