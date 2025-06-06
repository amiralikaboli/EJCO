#include "load/13b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/t.csv");
    load_miidx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
    load_mi("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/kt.csv");
    load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/it2.csv");
    load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/it.csv");
    load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/ct.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/13b/cn.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto miidx_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(miidx_offsets.size());
        for (int i = 0; i < miidx_offsets.size(); ++i)
            miidx_trie0[miidx_movie_id[i]][i] += 1;
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<string> interm0_col3;
        vector<int> interm0_col4;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_id[t_off];
            if (miidx_trie0.contains(x0)) {
                auto &miidx_trie1 = miidx_trie0.at(x0);
                for (const auto &miidx_off : miidx_trie1) {
                    interm0_col0.push_back(t_id[t_off]);
                    interm0_col1.push_back(t_title[t_off]);
                    interm0_col2.push_back(t_kind_id[t_off]);
                    interm0_col3.push_back(miidx_info[miidx_off]);
                    interm0_col4.push_back(miidx_info_type_id[miidx_off]);
                    interm0_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto interm0_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(interm0_offsets.size());
        for (int i = 0; i < interm0_offsets.size(); ++i)
            interm0_trie0[interm0_col0[i]][i] += 1;
        auto mc_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(mc_offsets.size());
        for (int i = 0; i < mc_offsets.size(); ++i)
            mc_trie0[mc_movie_id[i]][i] += 1;
        auto kt_trie0 = phmap::flat_hash_map<int, bool>(kt_offsets.size());
        for (int i = 0; i < kt_offsets.size(); ++i)
            kt_trie0[kt_id[i]] += 1;
        auto it2_trie0 = phmap::flat_hash_map<int, bool>(it2_offsets.size());
        for (int i = 0; i < it2_offsets.size(); ++i)
            it2_trie0[it2_id[i]] += 1;
        auto it_trie0 = phmap::flat_hash_map<int, bool>(it_offsets.size());
        for (int i = 0; i < it_offsets.size(); ++i)
            it_trie0[it_id[i]] += 1;
        auto ct_trie0 = phmap::flat_hash_map<int, bool>(ct_offsets.size());
        for (int i = 0; i < ct_offsets.size(); ++i)
            ct_trie0[ct_id[i]] += 1;
        auto cn_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(cn_offsets.size());
        for (int i = 0; i < cn_offsets.size(); ++i)
            cn_trie0[cn_id[i]][i] += 1;
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
                    if (kt_trie0.contains(x1)) {
                        auto &kt_trie1 = kt_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it2_trie0.contains(x2)) {
                            auto &it2_trie1 = it2_trie0.at(x2);
                            auto x3 = interm0_col4[interm0_off];
                            if (it_trie0.contains(x3)) {
                                auto &it_trie1 = it_trie0.at(x3);
                                for (const auto &mc_off : mc_trie1) {
                                    auto x4 = mc_company_type_id[mc_off];
                                    if (ct_trie0.contains(x4)) {
                                        auto &ct_trie1 = ct_trie0.at(x4);
                                        auto x5 = mc_company_id[mc_off];
                                        if (cn_trie0.contains(x5)) {
                                            auto &cn_trie1 = cn_trie0.at(x5);
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
