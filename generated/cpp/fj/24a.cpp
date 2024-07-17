#include "load/24a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/t.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/mi.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/k.csv");
    load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/it.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/cn.csv");
    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/n.csv");
    load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
    load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/ci.csv");
    load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
    load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/24a/rt.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        unordered_multimap<int, int> t_trie0(t_offsets.size());
        build_trie(t_trie0, t_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_movie_id[mk_off];
            auto t_range = t_trie0.equal_range(x0);
            if (t_range.first != t_range.second) {
                for (auto t_it = t_range.first; t_it != t_range.second; ++t_it) {
                    auto t_off = t_it->second;
                    interm0_col0.push_back(mk_movie_id[mk_off]);
                    interm0_col1.push_back(mk_keyword_id[mk_off]);
                    interm0_col2.push_back(t_title[t_off]);
                    interm0_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(1);

        unordered_multimap<int, int> interm0_trie0(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col0);
        unordered_multimap<int, int> mc_trie0(mc_offsets.size());
        build_trie(mc_trie0, mc_movie_id);
        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        auto it_trie0 = phmap::flat_hash_map<int, bool>(it_offsets.size());
        build_trie(it_trie0, it_id);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>(cn_offsets.size());
        build_trie(cn_trie0, cn_id);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<int> interm1_col1;
        vector<int> interm1_col2;
        vector<string> interm1_col3;
        vector<int> interm1_col4;
        vector<int> interm1_offsets;
        cnt = 0;
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_movie_id[mi_off];
            auto interm0_range = interm0_trie0.equal_range(x0);
            auto mc_range = mc_trie0.equal_range(x0);
            if (interm0_range.first != interm0_range.second && mc_range.first != mc_range.second) {
                for (auto interm0_it = interm0_range.first; interm0_it != interm0_range.second; ++interm0_it) {
                    auto interm0_off = interm0_it->second;
                    auto x1 = interm0_col1[interm0_off];
                    if (k_trie0.contains(x1)) {
                        auto &k_trie1 = k_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it_trie0.contains(x2)) {
                            auto &it_trie1 = it_trie0.at(x2);
                            for (auto mc_it = mc_range.first; mc_it != mc_range.second; ++mc_it) {
                                auto mc_off = mc_it->second;
                                auto x3 = mc_company_id[mc_off];
                                if (cn_trie0.contains(x3)) {
                                    auto &cn_trie1 = cn_trie0.at(x3);
                                    interm1_col0.push_back(mi_movie_id[mi_off]);
                                    interm1_col1.push_back(mi_info_type_id[mi_off]);
                                    interm1_col2.push_back(interm0_col1[interm0_off]);
                                    interm1_col3.push_back(interm0_col2[interm0_off]);
                                    interm1_col4.push_back(mc_company_id[mc_off]);
                                    interm1_offsets.push_back(cnt++);
                                }
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto an_trie0 = phmap::flat_hash_map<int, bool>(an_offsets.size());
        build_trie(an_trie0, an_person_id);
        timer.StoreElapsedTime(4);

        vector<int> interm2_col0;
        vector<string> interm2_col1;
        vector<int> interm2_offsets;
        cnt = 0;
        for (const auto &n_off : n_offsets) {
            auto x0 = n_id[n_off];
            if (an_trie0.contains(x0)) {
                auto &an_trie1 = an_trie0.at(x0);
                interm2_col0.push_back(n_id[n_off]);
                interm2_col1.push_back(n_name[n_off]);
                interm2_offsets.push_back(cnt++);
            }
        }
        timer.StoreElapsedTime(5);

        auto rt_trie0 = phmap::flat_hash_map<int, bool>(rt_offsets.size());
        build_trie(rt_trie0, rt_id);
        unordered_multimap<int, int> interm1_trie0(interm1_offsets.size());
        build_trie(interm1_trie0, interm1_col0);
        unordered_multimap<int, int> interm2_trie0(interm2_offsets.size());
        build_trie(interm2_trie0, interm2_col0);
        unordered_multimap<int, int> chn_trie0(chn_offsets.size());
        build_trie(chn_trie0, chn_id);
        timer.StoreElapsedTime(6);

        string mn_chn_name = "zzzzzzzz";
        string mn_interm2_col1 = "zzzzzzzz";
        string mn_interm1_col3 = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_role_id[ci_off];
            if (rt_trie0.contains(x0)) {
                auto &rt_trie1 = rt_trie0.at(x0);
                auto x1 = ci_movie_id[ci_off];
                auto interm1_range = interm1_trie0.equal_range(x1);
                if (interm1_range.first != interm1_range.second) {
                    auto x2 = ci_person_id[ci_off];
                    auto interm2_range = interm2_trie0.equal_range(x2);
                    if (interm2_range.first != interm2_range.second) {
                        auto x3 = ci_person_role_id[ci_off];
                        auto chn_range = chn_trie0.equal_range(x3);
                        if (chn_range.first != chn_range.second) {
                            for (auto chn_it = chn_range.first; chn_it != chn_range.second; ++chn_it) {
                                auto chn_off = chn_it->second;
                                mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                            }
                            for (auto interm2_it = interm2_range.first; interm2_it != interm2_range.second; ++interm2_it) {
                                auto interm2_off = interm2_it->second;
                                mn_interm2_col1 = min(mn_interm2_col1, interm2_col1[interm2_off]);
                            }
                            for (auto interm1_it = interm1_range.first; interm1_it != interm1_range.second; ++interm1_it) {
                                auto interm1_off = interm1_it->second;
                                mn_interm1_col3 = min(mn_interm1_col3, interm1_col3[interm1_off]);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(7);

        if (iter == 0)
            cout << mn_chn_name << " | " << mn_interm2_col1 << " | " << mn_interm1_col3 << endl;
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
