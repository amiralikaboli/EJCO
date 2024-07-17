#include "load/23c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_cc("/Users/s2522996/Documents/free-join/data/imdb_csv/complete_cast.csv");
    load_cct1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/cct1.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/t.csv");
    load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/kt.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/cn.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_k("/Users/s2522996/Documents/free-join/data/imdb_csv/keyword.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/mi.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/23c/it1.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto cct1_trie0 = phmap::flat_hash_map<int, bool>(cct1_offsets.size());
        build_trie(cct1_trie0, cct1_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &cc_off : cc_offsets) {
            auto x0 = cc_status_id[cc_off];
            if (cct1_trie0.contains(x0)) {
                auto &cct1_trie1 = cct1_trie0.at(x0);
                interm0_col0.push_back(cc_status_id[cc_off]);
                interm0_col1.push_back(cc_movie_id[cc_off]);
                interm0_offsets.push_back(cnt++);
            }
        }
        timer.StoreElapsedTime(1);

        unordered_multimap<int, int> kt_trie0(kt_offsets.size());
        build_trie(kt_trie0, kt_id);
        auto interm0_trie0 = phmap::flat_hash_map<int, bool>(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col1);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<int> interm1_col1;
        vector<string> interm1_col2;
        vector<string> interm1_col3;
        vector<int> interm1_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_kind_id[t_off];
            auto kt_range = kt_trie0.equal_range(x0);
            if (kt_range.first != kt_range.second) {
                auto x1 = t_id[t_off];
                if (interm0_trie0.contains(x1)) {
                    auto &interm0_trie1 = interm0_trie0.at(x1);
                    for (auto kt_it = kt_range.first; kt_it != kt_range.second; ++kt_it) {
                        auto kt_off = kt_it->second;
                        interm1_col0.push_back(t_kind_id[t_off]);
                        interm1_col1.push_back(t_id[t_off]);
                        interm1_col2.push_back(t_title[t_off]);
                        interm1_col3.push_back(kt_kind[kt_off]);
                        interm1_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto ct_trie0 = phmap::flat_hash_map<int, bool>(ct_offsets.size());
        build_trie(ct_trie0, ct_id);
        unordered_multimap<int, int> interm1_trie0(interm1_offsets.size());
        build_trie(interm1_trie0, interm1_col1);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>(cn_offsets.size());
        build_trie(cn_trie0, cn_id);
        timer.StoreElapsedTime(4);

        vector<int> interm2_col0;
        vector<int> interm2_col1;
        vector<int> interm2_col2;
        vector<string> interm2_col4;
        vector<string> interm2_col5;
        vector<int> interm2_offsets;
        cnt = 0;
        for (const auto &mc_off : mc_offsets) {
            auto x0 = mc_company_type_id[mc_off];
            if (ct_trie0.contains(x0)) {
                auto &ct_trie1 = ct_trie0.at(x0);
                auto x1 = mc_movie_id[mc_off];
                auto interm1_range = interm1_trie0.equal_range(x1);
                if (interm1_range.first != interm1_range.second) {
                    auto x2 = mc_company_id[mc_off];
                    if (cn_trie0.contains(x2)) {
                        auto &cn_trie1 = cn_trie0.at(x2);
                        for (auto interm1_it = interm1_range.first; interm1_it != interm1_range.second; ++interm1_it) {
                            auto interm1_off = interm1_it->second;
                            interm2_col0.push_back(mc_company_type_id[mc_off]);
                            interm2_col1.push_back(mc_company_id[mc_off]);
                            interm2_col2.push_back(mc_movie_id[mc_off]);
                            interm2_col4.push_back(interm1_col2[interm1_off]);
                            interm2_col5.push_back(interm1_col3[interm1_off]);
                            interm2_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(5);

        unordered_multimap<int, int> interm2_trie0(interm2_offsets.size());
        build_trie(interm2_trie0, interm2_col2);
        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        timer.StoreElapsedTime(6);

        vector<int> interm3_col0;
        vector<int> interm3_col1;
        vector<string> interm3_col5;
        vector<string> interm3_col6;
        vector<int> interm3_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_movie_id[mk_off];
            auto interm2_range = interm2_trie0.equal_range(x0);
            if (interm2_range.first != interm2_range.second) {
                auto x1 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x1)) {
                    auto &k_trie1 = k_trie0.at(x1);
                    for (auto interm2_it = interm2_range.first; interm2_it != interm2_range.second; ++interm2_it) {
                        auto interm2_off = interm2_it->second;
                        interm3_col0.push_back(mk_keyword_id[mk_off]);
                        interm3_col1.push_back(mk_movie_id[mk_off]);
                        interm3_col5.push_back(interm2_col4[interm2_off]);
                        interm3_col6.push_back(interm2_col5[interm2_off]);
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

        string mn_interm3_col5 = "zzzzzzzz";
        string mn_interm3_col6 = "zzzzzzzz";
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_info_type_id[mi_off];
            if (it1_trie0.contains(x0)) {
                auto &it1_trie1 = it1_trie0.at(x0);
                auto x1 = mi_movie_id[mi_off];
                auto interm3_range = interm3_trie0.equal_range(x1);
                if (interm3_range.first != interm3_range.second) {
                    for (auto interm3_it = interm3_range.first; interm3_it != interm3_range.second; ++interm3_it) {
                        auto interm3_off = interm3_it->second;
                        mn_interm3_col5 = min(mn_interm3_col5, interm3_col5[interm3_off]);
                        mn_interm3_col6 = min(mn_interm3_col6, interm3_col6[interm3_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(9);

        if (iter == 0)
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
