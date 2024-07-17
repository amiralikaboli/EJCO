#include "load/29c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
    load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29c/cct1.csv");
    load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29c/cct2.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29c/t.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29c/cn.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29c/k.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29c/mi.csv");
    load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29c/it.csv");
    load_pi("/Users/s2522996/Documents/free-join/data/imdb_csv/person_info.csv");
    load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
    load_it3("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29c/it3.csv");
    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29c/n.csv");
    load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29c/ci.csv");
    load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
    load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/29c/rt.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cct1_trie0, cct1_id);
        auto cct2_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cct2_trie0, cct2_id);
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

        auto interm0_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(interm0_trie0, interm0_col2);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<string> interm1_col1;
        vector<int> interm1_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_id[t_off];
            if (interm0_trie0.contains(x0)) {
                auto &interm0_trie1 = interm0_trie0.at(x0);
                interm1_col0.push_back(t_id[t_off]);
                interm1_col1.push_back(t_title[t_off]);
                interm1_offsets.push_back(cnt++);
            }
        }
        timer.StoreElapsedTime(3);

        auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(interm1_trie0, interm1_col0);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cn_trie0, cn_id);
        timer.StoreElapsedTime(4);

        vector<int> interm2_col0;
        vector<int> interm2_col1;
        vector<string> interm2_col2;
        vector<int> interm2_offsets;
        cnt = 0;
        for (const auto &mc_off : mc_offsets) {
            auto x0 = mc_movie_id[mc_off];
            if (interm1_trie0.contains(x0)) {
                auto &interm1_trie1 = interm1_trie0.at(x0);
                auto x1 = mc_company_id[mc_off];
                if (cn_trie0.contains(x1)) {
                    auto &cn_trie1 = cn_trie0.at(x1);
                    for (const auto &interm1_off : interm1_trie1) {
                        interm2_col0.push_back(mc_company_id[mc_off]);
                        interm2_col1.push_back(mc_movie_id[mc_off]);
                        interm2_col2.push_back(interm1_col1[interm1_off]);
                        interm2_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(5);

        auto k_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(k_trie0, k_id);
        auto interm2_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(interm2_trie0, interm2_col1);
        timer.StoreElapsedTime(6);

        vector<int> interm3_col0;
        vector<int> interm3_col1;
        vector<string> interm3_col3;
        vector<int> interm3_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_keyword_id[mk_off];
            if (k_trie0.contains(x0)) {
                auto &k_trie1 = k_trie0.at(x0);
                auto x1 = mk_movie_id[mk_off];
                if (interm2_trie0.contains(x1)) {
                    auto &interm2_trie1 = interm2_trie0.at(x1);
                    for (const auto &interm2_off : interm2_trie1) {
                        interm3_col0.push_back(mk_keyword_id[mk_off]);
                        interm3_col1.push_back(mk_movie_id[mk_off]);
                        interm3_col3.push_back(interm2_col2[interm2_off]);
                        interm3_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(7);

        auto it_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it_trie0, it_id);
        auto interm3_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(interm3_trie0, interm3_col1);
        timer.StoreElapsedTime(8);

        vector<int> interm4_col0;
        vector<int> interm4_col1;
        vector<string> interm4_col4;
        vector<int> interm4_offsets;
        cnt = 0;
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_info_type_id[mi_off];
            if (it_trie0.contains(x0)) {
                auto &it_trie1 = it_trie0.at(x0);
                auto x1 = mi_movie_id[mi_off];
                if (interm3_trie0.contains(x1)) {
                    auto &interm3_trie1 = interm3_trie0.at(x1);
                    for (const auto &interm3_off : interm3_trie1) {
                        interm4_col0.push_back(mi_info_type_id[mi_off]);
                        interm4_col1.push_back(mi_movie_id[mi_off]);
                        interm4_col4.push_back(interm3_col3[interm3_off]);
                        interm4_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(9);

        auto it3_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it3_trie0, it3_id);
        auto an_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(an_trie0, an_person_id);
        timer.StoreElapsedTime(10);

        vector<int> interm5_col0;
        vector<int> interm5_col1;
        vector<int> interm5_offsets;
        cnt = 0;
        for (const auto &pi_off : pi_offsets) {
            auto x0 = pi_info_type_id[pi_off];
            if (it3_trie0.contains(x0)) {
                auto &it3_trie1 = it3_trie0.at(x0);
                auto x1 = pi_person_id[pi_off];
                if (an_trie0.contains(x1)) {
                    auto &an_trie1 = an_trie0.at(x1);
                    interm5_col0.push_back(pi_person_id[pi_off]);
                    interm5_col1.push_back(pi_info_type_id[pi_off]);
                    interm5_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(11);

        auto interm5_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(interm5_trie0, interm5_col0);
        timer.StoreElapsedTime(12);

        vector<int> interm6_col0;
        vector<string> interm6_col1;
        vector<int> interm6_offsets;
        cnt = 0;
        for (const auto &n_off : n_offsets) {
            auto x0 = n_id[n_off];
            if (interm5_trie0.contains(x0)) {
                auto &interm5_trie1 = interm5_trie0.at(x0);
                interm6_col0.push_back(n_id[n_off]);
                interm6_col1.push_back(n_name[n_off]);
                interm6_offsets.push_back(cnt++);
            }
        }
        timer.StoreElapsedTime(13);

        auto rt_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(rt_trie0, rt_id);
        auto interm4_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(interm4_trie0, interm4_col1);
        auto interm6_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(interm6_trie0, interm6_col0);
        auto chn_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(chn_trie0, chn_id);
        timer.StoreElapsedTime(14);

        string mn_chn_name = "zzzzzzzz";
        string mn_interm6_col1 = "zzzzzzzz";
        string mn_interm4_col4 = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_role_id[ci_off];
            if (rt_trie0.contains(x0)) {
                auto &rt_trie1 = rt_trie0.at(x0);
                auto x1 = ci_movie_id[ci_off];
                if (interm4_trie0.contains(x1)) {
                    auto &interm4_trie1 = interm4_trie0.at(x1);
                    auto x2 = ci_person_id[ci_off];
                    if (interm6_trie0.contains(x2)) {
                        auto &interm6_trie1 = interm6_trie0.at(x2);
                        auto x3 = ci_person_role_id[ci_off];
                        if (chn_trie0.contains(x3)) {
                            auto &chn_trie1 = chn_trie0.at(x3);
                            for (const auto &chn_off : chn_trie1) {
                                mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                            }
                            for (const auto &interm6_off : interm6_trie1) {
                                mn_interm6_col1 = min(mn_interm6_col1, interm6_col1[interm6_off]);
                            }
                            for (const auto &interm4_off : interm4_trie1) {
                                mn_interm4_col4 = min(mn_interm4_col4, interm4_col4[interm4_off]);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(15);

        if (iter == 0)
            cout << mn_chn_name << " | " << mn_interm6_col1 << " | " << mn_interm4_col4 << endl;
        cout << "*" << " " << flush;
    }
    cout << endl;

    vector<double> tm{0};
    for (int i = 0; i < 2 * 8; ++i)
        tm.push_back(timer.GetMean(i));
    for (int i = 0; i < 2 * 8; i += 2) {
        cout << tm[i + 1] - tm[i] << " + ";
        cout << tm[i + 2] - tm[i + 1] << " = ";
        cout << tm[i + 2] - tm[i] << " ms" << endl;
    }
    cout << tm[2 * 8] << " ms" << endl;
}
