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

        unordered_multimap<int, int> miidx_trie0(miidx_offsets.size());
        build_trie(miidx_trie0, miidx_movie_id);
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
            auto miidx_range = miidx_trie0.equal_range(x0);
            if (miidx_range.first != miidx_range.second) {
                for (auto miidx_it = miidx_range.first; miidx_it != miidx_range.second; ++miidx_it) {
                    auto miidx_off = miidx_it->second;
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

        unordered_multimap<int, int> interm0_trie0(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col0);
        unordered_multimap<int, int> mc_trie0(mc_offsets.size());
        build_trie(mc_trie0, mc_movie_id);
        auto kt_trie0 = phmap::flat_hash_map<int, bool>(kt_offsets.size());
        build_trie(kt_trie0, kt_id);
        auto it2_trie0 = phmap::flat_hash_map<int, bool>(it2_offsets.size());
        build_trie(it2_trie0, it2_id);
        auto it_trie0 = phmap::flat_hash_map<int, bool>(it_offsets.size());
        build_trie(it_trie0, it_id);
        auto ct_trie0 = phmap::flat_hash_map<int, bool>(ct_offsets.size());
        build_trie(ct_trie0, ct_id);
        unordered_multimap<int, int> cn_trie0(cn_offsets.size());
        build_trie(cn_trie0, cn_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col1 = "zzzzzzzz";
        string mn_interm0_col3 = "zzzzzzzz";
        string mn_cn_name = "zzzzzzzz";
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_movie_id[mi_off];
            auto interm0_range = interm0_trie0.equal_range(x0);
            auto mc_range = mc_trie0.equal_range(x0);
            if (interm0_range.first != interm0_range.second && mc_range.first != mc_range.second) {
                for (auto interm0_it = interm0_range.first; interm0_it != interm0_range.second; ++interm0_it) {
                    auto interm0_off = interm0_it->second;
                    auto x1 = interm0_col2[interm0_off];
                    if (kt_trie0.contains(x1)) {
                        auto &kt_trie1 = kt_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it2_trie0.contains(x2)) {
                            auto &it2_trie1 = it2_trie0.at(x2);
                            auto x3 = interm0_col4[interm0_off];
                            if (it_trie0.contains(x3)) {
                                auto &it_trie1 = it_trie0.at(x3);
                                for (auto mc_it = mc_range.first; mc_it != mc_range.second; ++mc_it) {
                                    auto mc_off = mc_it->second;
                                    auto x4 = mc_company_type_id[mc_off];
                                    if (ct_trie0.contains(x4)) {
                                        auto &ct_trie1 = ct_trie0.at(x4);
                                        auto x5 = mc_company_id[mc_off];
                                        auto cn_range = cn_trie0.equal_range(x5);
                                        if (cn_range.first != cn_range.second) {
                                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                            mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                                            for (auto cn_it = cn_range.first; cn_it != cn_range.second; ++cn_it) {
                                                auto cn_off = cn_it->second;
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
