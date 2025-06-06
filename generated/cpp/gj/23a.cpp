#include "load/23a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
    load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/cct1.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/t.csv");
    load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/kt.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/cn.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_k("/Users/s2522996/Documents/free-join/data/imdb_csv/keyword.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/mi.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23a/it1.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int z = 0; z < 1 + 5; ++z) {
        int cnt;
        timer.Reset();

        auto cc_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(cc_trie0, cc_status_id);
        auto cct1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cct1_trie0, cct1_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        for (const auto &[x0, cc_trie1] : cc_trie0) {
            if (cct1_trie0.contains(x0)) {
                auto &cct1_trie1 = cct1_trie0.at(x0);
                for (const auto &cc_off : cc_trie1) {
                    interm0_col0.push_back(cc_status_id[cc_off]);
                    interm0_col1.push_back(cc_movie_id[cc_off]);
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto t_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
        build_trie(t_trie0, t_kind_id, t_id);
        auto kt_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(kt_trie0, kt_id);
        auto interm0_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(interm0_trie0, interm0_col1);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<int> interm1_col1;
        vector<string> interm1_col2;
        vector<string> interm1_col3;
        for (const auto &[x0, t_trie1] : t_trie0) {
            if (kt_trie0.contains(x0)) {
                auto &kt_trie1 = kt_trie0.at(x0);
                for (const auto &[x1, t_trie2] : t_trie1) {
                    if (interm0_trie0.contains(x1)) {
                        auto &interm0_trie1 = interm0_trie0.at(x1);
                        for (const auto &t_off : t_trie2) {
                            for (const auto &kt_off : kt_trie1) {
                                interm1_col0.push_back(t_kind_id[t_off]);
                                interm1_col1.push_back(t_id[t_off]);
                                interm1_col2.push_back(t_title[t_off]);
                                interm1_col3.push_back(kt_kind[kt_off]);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>>();
        build_trie(mc_trie0, mc_company_type_id, mc_company_id, mc_movie_id);
        auto ct_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(ct_trie0, ct_id);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cn_trie0, cn_id);
        auto interm1_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(interm1_trie0, interm1_col1);
        timer.StoreElapsedTime(4);

        vector<int> interm2_col0;
        vector<int> interm2_col1;
        vector<int> interm2_col2;
        vector<string> interm2_col4;
        vector<string> interm2_col5;
        for (const auto &[x0, mc_trie1] : mc_trie0) {
            if (ct_trie0.contains(x0)) {
                auto &ct_trie1 = ct_trie0.at(x0);
                for (const auto &[x1, mc_trie2] : mc_trie1) {
                    if (cn_trie0.contains(x1)) {
                        auto &cn_trie1 = cn_trie0.at(x1);
                        for (const auto &[x2, mc_trie3] : mc_trie2) {
                            if (interm1_trie0.contains(x2)) {
                                auto &interm1_trie1 = interm1_trie0.at(x2);
                                for (const auto &mc_off : mc_trie3) {
                                    for (const auto &interm1_off : interm1_trie1) {
                                        interm2_col0.push_back(mc_company_type_id[mc_off]);
                                        interm2_col1.push_back(mc_company_id[mc_off]);
                                        interm2_col2.push_back(mc_movie_id[mc_off]);
                                        interm2_col4.push_back(interm1_col2[interm1_off]);
                                        interm2_col5.push_back(interm1_col3[interm1_off]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(5);

        auto mk_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
        build_trie(mk_trie0, mk_keyword_id, mk_movie_id);
        auto k_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(k_trie0, k_id);
        auto interm2_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(interm2_trie0, interm2_col2);
        timer.StoreElapsedTime(6);

        vector<int> interm3_col0;
        vector<int> interm3_col1;
        vector<string> interm3_col5;
        vector<string> interm3_col6;
        for (const auto &[x0, mk_trie1] : mk_trie0) {
            if (k_trie0.contains(x0)) {
                auto &k_trie1 = k_trie0.at(x0);
                for (const auto &[x1, mk_trie2] : mk_trie1) {
                    if (interm2_trie0.contains(x1)) {
                        auto &interm2_trie1 = interm2_trie0.at(x1);
                        for (const auto &mk_off : mk_trie2) {
                            for (const auto &interm2_off : interm2_trie1) {
                                interm3_col0.push_back(mk_keyword_id[mk_off]);
                                interm3_col1.push_back(mk_movie_id[mk_off]);
                                interm3_col5.push_back(interm2_col4[interm2_off]);
                                interm3_col6.push_back(interm2_col5[interm2_off]);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(7);

        auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
        build_trie(mi_trie0, mi_info_type_id, mi_movie_id);
        auto it1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it1_trie0, it1_id);
        auto interm3_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(interm3_trie0, interm3_col1);
        timer.StoreElapsedTime(8);

        string mn_interm3_col5 = "zzzzzzzz";
        string mn_interm3_col6 = "zzzzzzzz";
        for (const auto &[x0, mi_trie1] : mi_trie0) {
            if (it1_trie0.contains(x0)) {
                auto &it1_trie1 = it1_trie0.at(x0);
                for (const auto &[x1, mi_trie2] : mi_trie1) {
                    if (interm3_trie0.contains(x1)) {
                        auto &interm3_trie1 = interm3_trie0.at(x1);
                        for (const auto &interm3_off : interm3_trie1) {
                            mn_interm3_col5 = min(mn_interm3_col5, interm3_col5[interm3_off]);
                            mn_interm3_col6 = min(mn_interm3_col6, interm3_col6[interm3_off]);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(9);

        if (z == 0)
            cout << mn_interm3_col5 << " | " << mn_interm3_col6 << endl;
        cout << "*" << " " << flush;
    }
    cout << endl;

    vector<double> tm{0};
    for (int i = 0; i < 2 * 5; ++i)
        tm.push_back(timer.GetMean(i));
    for (int i = 0; i < 2 * 5; i += 2) {
        cout << tm[i + 1] - tm[i] << " + ";
        cout << tm[i + 2] - tm[i + 1] << " = ";
        cout << tm[i + 2] - tm[i] << " ms" << endl;
    }
    cout << tm[2 * 5] << " ms" << endl;
}
