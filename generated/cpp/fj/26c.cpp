#include "load/26c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
    load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26c/cct1.csv");
    load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26c/cct2.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
    load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26c/it2.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26c/t.csv");
    load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26c/kt.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26c/k.csv");
    load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
    load_n("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
    load_chn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/26c/chn.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto cct1_trie0 = phmap::flat_hash_map<int, bool>(cct1_offsets.size());
        for (int i = 0; i < cct1_offsets.size(); ++i)
            cct1_trie0[cct1_id[i]] += 1;
        auto cct2_trie0 = phmap::flat_hash_map<int, bool>(cct2_offsets.size());
        for (int i = 0; i < cct2_offsets.size(); ++i)
            cct2_trie0[cct2_id[i]] += 1;
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

        auto it2_trie0 = phmap::flat_hash_map<int, bool>(it2_offsets.size());
        for (int i = 0; i < it2_offsets.size(); ++i)
            it2_trie0[it2_id[i]] += 1;
        auto interm0_trie0 = phmap::flat_hash_map<int, bool>(interm0_offsets.size());
        for (int i = 0; i < interm0_offsets.size(); ++i)
            interm0_trie0[interm0_col2[i]] += 1;
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

        auto kt_trie0 = phmap::flat_hash_map<int, bool>(kt_offsets.size());
        for (int i = 0; i < kt_offsets.size(); ++i)
            kt_trie0[kt_id[i]] += 1;
        auto interm1_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(interm1_offsets.size());
        for (int i = 0; i < interm1_offsets.size(); ++i)
            interm1_trie0[interm1_col1[i]][i] += 1;
        timer.StoreElapsedTime(4);

        vector<int> interm2_col0;
        vector<int> interm2_col1;
        vector<string> interm2_col2;
        vector<string> interm2_col4;
        vector<int> interm2_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_kind_id[t_off];
            if (kt_trie0.contains(x0)) {
                auto &kt_trie1 = kt_trie0.at(x0);
                auto x1 = t_id[t_off];
                if (interm1_trie0.contains(x1)) {
                    auto &interm1_trie1 = interm1_trie0.at(x1);
                    for (const auto &interm1_off : interm1_trie1) {
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

        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        for (int i = 0; i < k_offsets.size(); ++i)
            k_trie0[k_id[i]] += 1;
        auto interm2_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(interm2_offsets.size());
        for (int i = 0; i < interm2_offsets.size(); ++i)
            interm2_trie0[interm2_col1[i]][i] += 1;
        timer.StoreElapsedTime(6);

        vector<int> interm3_col0;
        vector<int> interm3_col1;
        vector<string> interm3_col3;
        vector<string> interm3_col5;
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
                        interm3_col5.push_back(interm2_col4[interm2_off]);
                        interm3_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(7);

        auto interm3_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(interm3_offsets.size());
        for (int i = 0; i < interm3_offsets.size(); ++i)
            interm3_trie0[interm3_col1[i]][i] += 1;
        auto chn_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(chn_offsets.size());
        for (int i = 0; i < chn_offsets.size(); ++i)
            chn_trie0[chn_id[i]][i] += 1;
        auto n_trie0 = phmap::flat_hash_map<int, bool>(n_offsets.size());
        for (int i = 0; i < n_offsets.size(); ++i)
            n_trie0[n_id[i]] += 1;
        timer.StoreElapsedTime(8);

        string mn_chn_name = "zzzzzzzz";
        string mn_interm3_col3 = "zzzzzzzz";
        string mn_interm3_col5 = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_movie_id[ci_off];
            if (interm3_trie0.contains(x0)) {
                auto &interm3_trie1 = interm3_trie0.at(x0);
                auto x1 = ci_person_role_id[ci_off];
                if (chn_trie0.contains(x1)) {
                    auto &chn_trie1 = chn_trie0.at(x1);
                    auto x2 = ci_person_id[ci_off];
                    if (n_trie0.contains(x2)) {
                        auto &n_trie1 = n_trie0.at(x2);
                        for (const auto &chn_off : chn_trie1) {
                            mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                        }
                        for (const auto &interm3_off : interm3_trie1) {
                            mn_interm3_col3 = min(mn_interm3_col3, interm3_col3[interm3_off]);
                            mn_interm3_col5 = min(mn_interm3_col5, interm3_col5[interm3_off]);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(9);

        if (iter == 0)
            cout << mn_chn_name << " | " << mn_interm3_col3 << " | " << mn_interm3_col5 << endl;
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
