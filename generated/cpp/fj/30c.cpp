#include "load/30c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
    load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30c/cct1.csv");
    load_cct2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30c/cct2.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
    load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30c/it2.csv");
    load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30c/k.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30c/mi.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30c/it1.csv");
    load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30c/ci.csv");
    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/30c/n.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto cct1_trie0 = phmap::flat_hash_map<int, bool>(cct1_offsets.size());
        build_trie(cct1_trie0, cct1_id);
        auto cct2_trie0 = phmap::flat_hash_map<int, bool>(cct2_offsets.size());
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

        auto it2_trie0 = phmap::flat_hash_map<int, bool>(it2_offsets.size());
        build_trie(it2_trie0, it2_id);
        auto interm0_trie0 = phmap::flat_hash_map<int, bool>(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col2);
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

        unordered_multimap<int, int> interm1_trie0(interm1_offsets.size());
        build_trie(interm1_trie0, interm1_col1);
        timer.StoreElapsedTime(4);

        vector<int> interm2_col0;
        vector<string> interm2_col1;
        vector<string> interm2_col3;
        vector<int> interm2_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_id[t_off];
            auto interm1_range = interm1_trie0.equal_range(x0);
            if (interm1_range.first != interm1_range.second) {
                for (auto interm1_it = interm1_range.first; interm1_it != interm1_range.second; ++interm1_it) {
                    auto interm1_off = interm1_it->second;
                    interm2_col0.push_back(t_id[t_off]);
                    interm2_col1.push_back(t_title[t_off]);
                    interm2_col3.push_back(interm1_col2[interm1_off]);
                    interm2_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(5);

        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        unordered_multimap<int, int> interm2_trie0(interm2_offsets.size());
        build_trie(interm2_trie0, interm2_col0);
        timer.StoreElapsedTime(6);

        vector<int> interm3_col0;
        vector<int> interm3_col1;
        vector<string> interm3_col2;
        vector<string> interm3_col4;
        vector<int> interm3_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_keyword_id[mk_off];
            if (k_trie0.contains(x0)) {
                auto &k_trie1 = k_trie0.at(x0);
                auto x1 = mk_movie_id[mk_off];
                auto interm2_range = interm2_trie0.equal_range(x1);
                if (interm2_range.first != interm2_range.second) {
                    for (auto interm2_it = interm2_range.first; interm2_it != interm2_range.second; ++interm2_it) {
                        auto interm2_off = interm2_it->second;
                        interm3_col0.push_back(mk_keyword_id[mk_off]);
                        interm3_col1.push_back(mk_movie_id[mk_off]);
                        interm3_col2.push_back(interm2_col1[interm2_off]);
                        interm3_col4.push_back(interm2_col3[interm2_off]);
                        interm3_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(7);

        auto it1_trie0 = phmap::flat_hash_map<int, bool>(it1_offsets.size());
        build_trie(it1_trie0, it1_id);
        unordered_multimap<int, int> interm3_trie0(interm3_offsets.size());
        build_trie(interm3_trie0, interm3_col1);
        timer.StoreElapsedTime(8);

        vector<int> interm4_col0;
        vector<int> interm4_col1;
        vector<string> interm4_col2;
        vector<string> interm4_col4;
        vector<string> interm4_col6;
        vector<int> interm4_offsets;
        cnt = 0;
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_info_type_id[mi_off];
            if (it1_trie0.contains(x0)) {
                auto &it1_trie1 = it1_trie0.at(x0);
                auto x1 = mi_movie_id[mi_off];
                auto interm3_range = interm3_trie0.equal_range(x1);
                if (interm3_range.first != interm3_range.second) {
                    for (auto interm3_it = interm3_range.first; interm3_it != interm3_range.second; ++interm3_it) {
                        auto interm3_off = interm3_it->second;
                        interm4_col0.push_back(mi_info_type_id[mi_off]);
                        interm4_col1.push_back(mi_movie_id[mi_off]);
                        interm4_col2.push_back(mi_info[mi_off]);
                        interm4_col4.push_back(interm3_col2[interm3_off]);
                        interm4_col6.push_back(interm3_col4[interm3_off]);
                        interm4_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(9);

        unordered_multimap<int, int> interm4_trie0(interm4_offsets.size());
        build_trie(interm4_trie0, interm4_col1);
        unordered_multimap<int, int> n_trie0(n_offsets.size());
        build_trie(n_trie0, n_id);
        timer.StoreElapsedTime(10);

        string mn_n_name = "zzzzzzzz";
        string mn_interm4_col2 = "zzzzzzzz";
        string mn_interm4_col4 = "zzzzzzzz";
        string mn_interm4_col6 = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_movie_id[ci_off];
            auto interm4_range = interm4_trie0.equal_range(x0);
            if (interm4_range.first != interm4_range.second) {
                auto x1 = ci_person_id[ci_off];
                auto n_range = n_trie0.equal_range(x1);
                if (n_range.first != n_range.second) {
                    for (auto n_it = n_range.first; n_it != n_range.second; ++n_it) {
                        auto n_off = n_it->second;
                        mn_n_name = min(mn_n_name, n_name[n_off]);
                    }
                    for (auto interm4_it = interm4_range.first; interm4_it != interm4_range.second; ++interm4_it) {
                        auto interm4_off = interm4_it->second;
                        mn_interm4_col2 = min(mn_interm4_col2, interm4_col2[interm4_off]);
                        mn_interm4_col4 = min(mn_interm4_col4, interm4_col4[interm4_off]);
                        mn_interm4_col6 = min(mn_interm4_col6, interm4_col6[interm4_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(11);

        if (iter == 0)
            cout << mn_n_name << " | " << mn_interm4_col2 << " | " << mn_interm4_col4 << " | " << mn_interm4_col6 << endl;
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
