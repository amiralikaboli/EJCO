#include "load/22b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/t.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/mi_idx.csv");
    load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/kt.csv");
    load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/it2.csv");
    load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/mc.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/cn.csv");
    load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/k.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/mi.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/it1.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        string IVs;
        timer.Reset();

        auto kt_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(kt_trie0, kt_offsets, kt_id);
        auto mi_idx_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto mi_idx_itrie0 = phmap::flat_hash_map<int, int>();
        auto mi_idx_isunq = build_trie(mi_idx_vtrie0, mi_idx_itrie0, mi_idx_offsets, mi_idx_movie_id);
        auto it2_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it2_trie0, it2_offsets, it2_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<int> interm0_col3;
        vector<string> interm0_col4;
        vector<int> interm0_offsets;
        cnt = 0;
        if (mi_idx_isunq == 0) {
            if (iter == 0)
                IVs += "{mi_idx: v}\n";
            for (const auto &t_off : t_offsets) {
                auto x0 = t_kind_id[t_off];
                if (kt_trie0.contains(x0)) {
                    auto &kt_trie1 = kt_trie0.at(x0);
                    auto x1 = t_id[t_off];
                    if (mi_idx_vtrie0.contains(x1)) {
                        auto &mi_idx_vtrie1 = mi_idx_vtrie0.at(x1);
                        for (const auto &mi_idx_off : mi_idx_vtrie1) {
                            auto x2 = mi_idx_info_type_id[mi_idx_off];
                            if (it2_trie0.contains(x2)) {
                                auto &it2_trie1 = it2_trie0.at(x2);
                                interm0_col0.push_back(t_id[t_off]);
                                interm0_col1.push_back(t_kind_id[t_off]);
                                interm0_col2.push_back(t_title[t_off]);
                                interm0_col3.push_back(mi_idx_info_type_id[mi_idx_off]);
                                interm0_col4.push_back(mi_idx_info[mi_idx_off]);
                                interm0_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                IVs += "{mi_idx: i}\n";
            for (const auto &t_off : t_offsets) {
                auto x0 = t_kind_id[t_off];
                if (kt_trie0.contains(x0)) {
                    auto &kt_trie1 = kt_trie0.at(x0);
                    auto x1 = t_id[t_off];
                    if (mi_idx_itrie0.contains(x1)) {
                        auto &mi_idx_itrie1 = mi_idx_itrie0.at(x1);
                        auto &mi_idx_off = mi_idx_itrie1;
                        auto x2 = mi_idx_info_type_id[mi_idx_off];
                        if (it2_trie0.contains(x2)) {
                            auto &it2_trie1 = it2_trie0.at(x2);
                            interm0_col0.push_back(t_id[t_off]);
                            interm0_col1.push_back(t_kind_id[t_off]);
                            interm0_col2.push_back(t_title[t_off]);
                            interm0_col3.push_back(mi_idx_info_type_id[mi_idx_off]);
                            interm0_col4.push_back(mi_idx_info[mi_idx_off]);
                            interm0_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto ct_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(ct_trie0, ct_offsets, ct_id);
        auto interm0_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm0_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm0_isunq = build_trie(interm0_vtrie0, interm0_itrie0, interm0_offsets, interm0_col0);
        auto cn_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto cn_itrie0 = phmap::flat_hash_map<int, int>();
        auto cn_isunq = build_trie(cn_vtrie0, cn_itrie0, cn_offsets, cn_id);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<int> interm1_col1;
        vector<int> interm1_col2;
        vector<string> interm1_col3;
        vector<string> interm1_col5;
        vector<string> interm1_col7;
        vector<int> interm1_offsets;
        cnt = 0;
        if (interm0_isunq == 0 && cn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: v, cn: v}\n";
            for (const auto &mc_off : mc_offsets) {
                auto x0 = mc_company_type_id[mc_off];
                if (ct_trie0.contains(x0)) {
                    auto &ct_trie1 = ct_trie0.at(x0);
                    auto x1 = mc_movie_id[mc_off];
                    if (interm0_vtrie0.contains(x1)) {
                        auto &interm0_vtrie1 = interm0_vtrie0.at(x1);
                        auto x2 = mc_company_id[mc_off];
                        if (cn_vtrie0.contains(x2)) {
                            auto &cn_vtrie1 = cn_vtrie0.at(x2);
                            for (const auto &cn_off : cn_vtrie1) {
                                for (const auto &interm0_off : interm0_vtrie1) {
                                    interm1_col0.push_back(mc_company_id[mc_off]);
                                    interm1_col1.push_back(mc_company_type_id[mc_off]);
                                    interm1_col2.push_back(mc_movie_id[mc_off]);
                                    interm1_col3.push_back(cn_name[cn_off]);
                                    interm1_col5.push_back(interm0_col2[interm0_off]);
                                    interm1_col7.push_back(interm0_col4[interm0_off]);
                                    interm1_offsets.push_back(cnt++);
                                }
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 0 && cn_isunq == 1) {
            if (iter == 0)
                IVs += "{interm0: v, cn: i}\n";
            for (const auto &mc_off : mc_offsets) {
                auto x0 = mc_company_type_id[mc_off];
                if (ct_trie0.contains(x0)) {
                    auto &ct_trie1 = ct_trie0.at(x0);
                    auto x1 = mc_movie_id[mc_off];
                    if (interm0_vtrie0.contains(x1)) {
                        auto &interm0_vtrie1 = interm0_vtrie0.at(x1);
                        auto x2 = mc_company_id[mc_off];
                        if (cn_itrie0.contains(x2)) {
                            auto &cn_itrie1 = cn_itrie0.at(x2);
                            auto &cn_off = cn_itrie1;
                            for (const auto &interm0_off : interm0_vtrie1) {
                                interm1_col0.push_back(mc_company_id[mc_off]);
                                interm1_col1.push_back(mc_company_type_id[mc_off]);
                                interm1_col2.push_back(mc_movie_id[mc_off]);
                                interm1_col3.push_back(cn_name[cn_off]);
                                interm1_col5.push_back(interm0_col2[interm0_off]);
                                interm1_col7.push_back(interm0_col4[interm0_off]);
                                interm1_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        } else if (interm0_isunq == 1 && cn_isunq == 0) {
            if (iter == 0)
                IVs += "{interm0: i, cn: v}\n";
            for (const auto &mc_off : mc_offsets) {
                auto x0 = mc_company_type_id[mc_off];
                if (ct_trie0.contains(x0)) {
                    auto &ct_trie1 = ct_trie0.at(x0);
                    auto x1 = mc_movie_id[mc_off];
                    if (interm0_itrie0.contains(x1)) {
                        auto &interm0_itrie1 = interm0_itrie0.at(x1);
                        auto x2 = mc_company_id[mc_off];
                        if (cn_vtrie0.contains(x2)) {
                            auto &cn_vtrie1 = cn_vtrie0.at(x2);
                            for (const auto &cn_off : cn_vtrie1) {
                                auto &interm0_off = interm0_itrie1;
                                interm1_col0.push_back(mc_company_id[mc_off]);
                                interm1_col1.push_back(mc_company_type_id[mc_off]);
                                interm1_col2.push_back(mc_movie_id[mc_off]);
                                interm1_col3.push_back(cn_name[cn_off]);
                                interm1_col5.push_back(interm0_col2[interm0_off]);
                                interm1_col7.push_back(interm0_col4[interm0_off]);
                                interm1_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                IVs += "{interm0: i, cn: i}\n";
            for (const auto &mc_off : mc_offsets) {
                auto x0 = mc_company_type_id[mc_off];
                if (ct_trie0.contains(x0)) {
                    auto &ct_trie1 = ct_trie0.at(x0);
                    auto x1 = mc_movie_id[mc_off];
                    if (interm0_itrie0.contains(x1)) {
                        auto &interm0_itrie1 = interm0_itrie0.at(x1);
                        auto x2 = mc_company_id[mc_off];
                        if (cn_itrie0.contains(x2)) {
                            auto &cn_itrie1 = cn_itrie0.at(x2);
                            auto &cn_off = cn_itrie1;
                            auto &interm0_off = interm0_itrie1;
                            interm1_col0.push_back(mc_company_id[mc_off]);
                            interm1_col1.push_back(mc_company_type_id[mc_off]);
                            interm1_col2.push_back(mc_movie_id[mc_off]);
                            interm1_col3.push_back(cn_name[cn_off]);
                            interm1_col5.push_back(interm0_col2[interm0_off]);
                            interm1_col7.push_back(interm0_col4[interm0_off]);
                            interm1_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto k_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(k_trie0, k_offsets, k_id);
        auto interm1_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm1_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm1_isunq = build_trie(interm1_vtrie0, interm1_itrie0, interm1_offsets, interm1_col2);
        timer.StoreElapsedTime(4);

        vector<int> interm2_col0;
        vector<int> interm2_col1;
        vector<string> interm2_col4;
        vector<string> interm2_col6;
        vector<string> interm2_col8;
        vector<int> interm2_offsets;
        cnt = 0;
        if (interm1_isunq == 0) {
            if (iter == 0)
                IVs += "{interm1: v}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (interm1_vtrie0.contains(x1)) {
                        auto &interm1_vtrie1 = interm1_vtrie0.at(x1);
                        for (const auto &interm1_off : interm1_vtrie1) {
                            interm2_col0.push_back(mk_keyword_id[mk_off]);
                            interm2_col1.push_back(mk_movie_id[mk_off]);
                            interm2_col4.push_back(interm1_col3[interm1_off]);
                            interm2_col6.push_back(interm1_col5[interm1_off]);
                            interm2_col8.push_back(interm1_col7[interm1_off]);
                            interm2_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                IVs += "{interm1: i}\n";
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (interm1_itrie0.contains(x1)) {
                        auto &interm1_itrie1 = interm1_itrie0.at(x1);
                        auto &interm1_off = interm1_itrie1;
                        interm2_col0.push_back(mk_keyword_id[mk_off]);
                        interm2_col1.push_back(mk_movie_id[mk_off]);
                        interm2_col4.push_back(interm1_col3[interm1_off]);
                        interm2_col6.push_back(interm1_col5[interm1_off]);
                        interm2_col8.push_back(interm1_col7[interm1_off]);
                        interm2_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(5);

        auto it1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it1_trie0, it1_offsets, it1_id);
        auto interm2_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm2_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm2_isunq = build_trie(interm2_vtrie0, interm2_itrie0, interm2_offsets, interm2_col1);
        timer.StoreElapsedTime(6);

        string mn_interm2_col4 = "zzzzzzzz";
        string mn_interm2_col6 = "zzzzzzzz";
        string mn_interm2_col8 = "zzzzzzzz";
        if (interm2_isunq == 0) {
            if (iter == 0)
                IVs += "{interm2: v}\n";
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_info_type_id[mi_off];
                if (it1_trie0.contains(x0)) {
                    auto &it1_trie1 = it1_trie0.at(x0);
                    auto x1 = mi_movie_id[mi_off];
                    if (interm2_vtrie0.contains(x1)) {
                        auto &interm2_vtrie1 = interm2_vtrie0.at(x1);
                        for (const auto &interm2_off : interm2_vtrie1) {
                            mn_interm2_col4 = min(mn_interm2_col4, interm2_col4[interm2_off]);
                            mn_interm2_col6 = min(mn_interm2_col6, interm2_col6[interm2_off]);
                            mn_interm2_col8 = min(mn_interm2_col8, interm2_col8[interm2_off]);
                        }
                    }
                }
            }
        } else {
            if (iter == 0)
                IVs += "{interm2: i}\n";
            for (const auto &mi_off : mi_offsets) {
                auto x0 = mi_info_type_id[mi_off];
                if (it1_trie0.contains(x0)) {
                    auto &it1_trie1 = it1_trie0.at(x0);
                    auto x1 = mi_movie_id[mi_off];
                    if (interm2_itrie0.contains(x1)) {
                        auto &interm2_itrie1 = interm2_itrie0.at(x1);
                        auto &interm2_off = interm2_itrie1;
                        mn_interm2_col4 = min(mn_interm2_col4, interm2_col4[interm2_off]);
                        mn_interm2_col6 = min(mn_interm2_col6, interm2_col6[interm2_off]);
                        mn_interm2_col8 = min(mn_interm2_col8, interm2_col8[interm2_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(7);

        if (iter == 0) {
            cout << mn_interm2_col4 << " | " << mn_interm2_col6 << " | " << mn_interm2_col8 << endl;
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
