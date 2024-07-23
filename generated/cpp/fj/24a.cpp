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

        auto t_trie0 = phmap::flat_hash_map<int, small_vector_vecptr<int, 4>>(t_offsets.size());
        build_trie<4>(t_trie0, t_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_movie_id[mk_off];
            if (t_trie0.contains(x0)) {
                auto &t_trie1 = t_trie0.at(x0);
                for (int t_i = 0; t_i < t_trie1.size(); ++t_i) {
                    auto t_off = t_trie1[t_i];
                    interm0_col0.push_back(mk_movie_id[mk_off]);
                    interm0_col1.push_back(mk_keyword_id[mk_off]);
                    interm0_col2.push_back(t_title[t_off]);
                    interm0_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto interm0_trie0 = phmap::flat_hash_map<int, small_vector_vecptr<int, 4>>(interm0_offsets.size());
        build_trie<4>(interm0_trie0, interm0_col0);
        auto mc_trie0 = phmap::flat_hash_map<int, small_vector_vecptr<int, 4>>(mc_offsets.size());
        build_trie<4>(mc_trie0, mc_movie_id);
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
            if (interm0_trie0.contains(x0) && mc_trie0.contains(x0)) {
                auto &interm0_trie1 = interm0_trie0.at(x0);
                auto &mc_trie1 = mc_trie0.at(x0);
                for (int interm0_i = 0; interm0_i < interm0_trie1.size(); ++interm0_i) {
                    auto interm0_off = interm0_trie1[interm0_i];
                    auto x1 = interm0_col1[interm0_off];
                    if (k_trie0.contains(x1)) {
                        auto &k_trie1 = k_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it_trie0.contains(x2)) {
                            auto &it_trie1 = it_trie0.at(x2);
                            for (int mc_i = 0; mc_i < mc_trie1.size(); ++mc_i) {
                                auto mc_off = mc_trie1[mc_i];
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
        auto interm1_trie0 = phmap::flat_hash_map<int, small_vector_vecptr<int, 4>>(interm1_offsets.size());
        build_trie<4>(interm1_trie0, interm1_col0);
        auto interm2_trie0 = phmap::flat_hash_map<int, small_vector_vecptr<int, 4>>(interm2_offsets.size());
        build_trie<4>(interm2_trie0, interm2_col0);
        auto chn_trie0 = phmap::flat_hash_map<int, small_vector_vecptr<int, 4>>(chn_offsets.size());
        build_trie<4>(chn_trie0, chn_id);
        timer.StoreElapsedTime(6);

        string mn_chn_name = "zzzzzzzz";
        string mn_interm2_col1 = "zzzzzzzz";
        string mn_interm1_col3 = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_role_id[ci_off];
            if (rt_trie0.contains(x0)) {
                auto &rt_trie1 = rt_trie0.at(x0);
                auto x1 = ci_movie_id[ci_off];
                if (interm1_trie0.contains(x1)) {
                    auto &interm1_trie1 = interm1_trie0.at(x1);
                    auto x2 = ci_person_id[ci_off];
                    if (interm2_trie0.contains(x2)) {
                        auto &interm2_trie1 = interm2_trie0.at(x2);
                        auto x3 = ci_person_role_id[ci_off];
                        if (chn_trie0.contains(x3)) {
                            auto &chn_trie1 = chn_trie0.at(x3);
                            for (int chn_i = 0; chn_i < chn_trie1.size(); ++chn_i) {
                                auto chn_off = chn_trie1[chn_i];
                                mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                            }
                            for (int interm2_i = 0; interm2_i < interm2_trie1.size(); ++interm2_i) {
                                auto interm2_off = interm2_trie1[interm2_i];
                                mn_interm2_col1 = min(mn_interm2_col1, interm2_col1[interm2_off]);
                            }
                            for (int interm1_i = 0; interm1_i < interm1_trie1.size(); ++interm1_i) {
                                auto interm1_off = interm1_trie1[interm1_i];
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
