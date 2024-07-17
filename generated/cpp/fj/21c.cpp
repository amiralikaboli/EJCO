#include "load/21c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/t.csv");
    load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/mi.csv");
    load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/mc.csv");
    load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/lt.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/k.csv");
    load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/ct.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/21c/cn.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        unordered_multimap<int, int> ml_trie0(ml_offsets.size());
        build_trie(ml_trie0, ml_movie_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_id[t_off];
            auto ml_range = ml_trie0.equal_range(x0);
            if (ml_range.first != ml_range.second) {
                for (auto ml_it = ml_range.first; ml_it != ml_range.second; ++ml_it) {
                    auto ml_off = ml_it->second;
                    interm0_col0.push_back(t_id[t_off]);
                    interm0_col1.push_back(t_title[t_off]);
                    interm0_col2.push_back(ml_link_type_id[ml_off]);
                    interm0_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(1);

        unordered_multimap<int, int> interm0_trie0(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col0);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<int> interm1_col1;
        vector<string> interm1_col2;
        vector<int> interm1_col3;
        vector<int> interm1_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_movie_id[mk_off];
            auto interm0_range = interm0_trie0.equal_range(x0);
            if (interm0_range.first != interm0_range.second) {
                for (auto interm0_it = interm0_range.first; interm0_it != interm0_range.second; ++interm0_it) {
                    auto interm0_off = interm0_it->second;
                    interm1_col0.push_back(mk_movie_id[mk_off]);
                    interm1_col1.push_back(mk_keyword_id[mk_off]);
                    interm1_col2.push_back(interm0_col1[interm0_off]);
                    interm1_col3.push_back(interm0_col2[interm0_off]);
                    interm1_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(3);

        unordered_multimap<int, int> interm1_trie0(interm1_offsets.size());
        build_trie(interm1_trie0, interm1_col0);
        unordered_multimap<int, int> mc_trie0(mc_offsets.size());
        build_trie(mc_trie0, mc_movie_id);
        unordered_multimap<int, int> lt_trie0(lt_offsets.size());
        build_trie(lt_trie0, lt_id);
        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        auto ct_trie0 = phmap::flat_hash_map<int, bool>(ct_offsets.size());
        build_trie(ct_trie0, ct_id);
        unordered_multimap<int, int> cn_trie0(cn_offsets.size());
        build_trie(cn_trie0, cn_id);
        timer.StoreElapsedTime(4);

        string mn_interm1_col2 = "zzzzzzzz";
        string mn_lt_link = "zzzzzzzz";
        string mn_cn_name = "zzzzzzzz";
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_movie_id[mi_off];
            auto interm1_range = interm1_trie0.equal_range(x0);
            auto mc_range = mc_trie0.equal_range(x0);
            if (interm1_range.first != interm1_range.second && mc_range.first != mc_range.second) {
                for (auto interm1_it = interm1_range.first; interm1_it != interm1_range.second; ++interm1_it) {
                    auto interm1_off = interm1_it->second;
                    auto x1 = interm1_col3[interm1_off];
                    auto lt_range = lt_trie0.equal_range(x1);
                    if (lt_range.first != lt_range.second) {
                        auto x2 = interm1_col1[interm1_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            for (auto mc_it = mc_range.first; mc_it != mc_range.second; ++mc_it) {
                                auto mc_off = mc_it->second;
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    auto cn_range = cn_trie0.equal_range(x4);
                                    if (cn_range.first != cn_range.second) {
                                        mn_interm1_col2 = min(mn_interm1_col2, interm1_col2[interm1_off]);
                                        for (auto lt_it = lt_range.first; lt_it != lt_range.second; ++lt_it) {
                                            auto lt_off = lt_it->second;
                                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                        }
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
        timer.StoreElapsedTime(5);

        if (iter == 0)
            cout << mn_interm1_col2 << " | " << mn_lt_link << " | " << mn_cn_name << endl;
        cout << "*" << " " << flush;
    }
    cout << endl;

    vector<double> tm{0};
    for (int i = 0; i < 2 * 3; ++i)
        tm.push_back(timer.GetMean(i));
    for (int i = 0; i < 2 * 3; i += 2) {
        cout << tm[i + 1] - tm[i] << " + ";
        cout << tm[i + 2] - tm[i + 1] << " = ";
        cout << tm[i + 2] - tm[i] << " ms" << endl;
    }
    cout << tm[2 * 3] << " ms" << endl;
}
