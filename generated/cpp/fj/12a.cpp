#include "load/12a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12a/t.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12a/mi_idx.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12a/mi.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12a/it2.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12a/it1.csv");
    load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12a/ct.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/12a/cn.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto mi_idx_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(mi_idx_trie0, mi_idx_movie_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<string> interm0_col3;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_id[t_off];
            if (mi_idx_trie0.contains(x0)) {
                auto &mi_idx_trie1 = mi_idx_trie0.at(x0);
                for (const auto &mi_idx_off : mi_idx_trie1) {
                    interm0_col0.push_back(t_id[t_off]);
                    interm0_col1.push_back(t_title[t_off]);
                    interm0_col2.push_back(mi_idx_info_type_id[mi_idx_off]);
                    interm0_col3.push_back(mi_idx_info[mi_idx_off]);
                    interm0_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto interm0_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(interm0_trie0, interm0_col0);
        auto mc_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(mc_trie0, mc_movie_id);
        auto it2_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it2_trie0, it2_id);
        auto it1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it1_trie0, it1_id);
        auto ct_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(ct_trie0, ct_id);
        auto cn_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(cn_trie0, cn_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col1 = "zzzzzzzz";
        string mn_interm0_col3 = "zzzzzzzz";
        string mn_cn_name = "zzzzzzzz";
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_movie_id[mi_off];
            if (interm0_trie0.contains(x0) && mc_trie0.contains(x0)) {
                auto &interm0_trie1 = interm0_trie0.at(x0);
                auto &mc_trie1 = mc_trie0.at(x0);
                for (const auto &interm0_off : interm0_trie1) {
                    auto x1 = interm0_col2[interm0_off];
                    if (it2_trie0.contains(x1)) {
                        auto &it2_trie1 = it2_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it1_trie0.contains(x2)) {
                            auto &it1_trie1 = it1_trie0.at(x2);
                            for (const auto &mc_off : mc_trie1) {
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_trie0.contains(x4)) {
                                        auto &cn_trie1 = cn_trie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                                        for (const auto &cn_off : cn_trie1) {
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
