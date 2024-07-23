#include "load/22b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/t.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/mi_idx.csv");
    load_kt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/kt.csv");
    load_it2("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/it2.csv");
    load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/mc.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/cn.csv");
    load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/k.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/mi.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/22b/it1.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto kt_trie0 = phmap::flat_hash_map<int, bool>(kt_offsets.size());
        build_trie(kt_trie0, kt_id);
        auto mi_idx_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(mi_idx_offsets.size());
        build_trie<4>(mi_idx_trie0, mi_idx_movie_id);
        auto it2_trie0 = phmap::flat_hash_map<int, bool>(it2_offsets.size());
        build_trie(it2_trie0, it2_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<int> interm0_col3;
        vector<string> interm0_col4;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_kind_id[t_off];
            if (kt_trie0.contains(x0)) {
                auto &kt_trie1 = kt_trie0.at(x0);
                auto x1 = t_id[t_off];
                if (mi_idx_trie0.contains(x1)) {
                    auto &mi_idx_trie1 = mi_idx_trie0.at(x1);
                    for (int mi_idx_i = 0; mi_idx_i < mi_idx_trie1.size(); ++mi_idx_i) {
                        auto mi_idx_off = mi_idx_trie1[mi_idx_i];
                        auto x2 = mi_idx_info_type_id[mi_idx_off];
                        if (it2_trie0.contains(x2)) {
                            auto &it2_trie1 = it2_trie0.at(x2);
                            interm0_col0.push_back(t_id[t_off]);
                            interm0_col1.push_back(t_kind_id[t_off]);
                            interm0_col2.push_back(t_title[t_off]);
                            interm0_col3.push_back(mi_idx_info_type_id[mi_idx_off]);
                            interm0_col4.push_back(mi_idx_info[mi_idx_off]);
                            interm0_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto ct_trie0 = phmap::flat_hash_map<int, bool>(ct_offsets.size());
        build_trie(ct_trie0, ct_id);
        auto interm0_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(interm0_offsets.size());
        build_trie<4>(interm0_trie0, interm0_col0);
        auto cn_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(cn_offsets.size());
        build_trie<4>(cn_trie0, cn_id);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<int> interm1_col1;
        vector<int> interm1_col2;
        vector<string> interm1_col3;
        vector<string> interm1_col5;
        vector<string> interm1_col7;
        vector<int> interm1_offsets;
        cnt = 0;
        for (const auto &mc_off : mc_offsets) {
            auto x0 = mc_company_type_id[mc_off];
            if (ct_trie0.contains(x0)) {
                auto &ct_trie1 = ct_trie0.at(x0);
                auto x1 = mc_movie_id[mc_off];
                if (interm0_trie0.contains(x1)) {
                    auto &interm0_trie1 = interm0_trie0.at(x1);
                    auto x2 = mc_company_id[mc_off];
                    if (cn_trie0.contains(x2)) {
                        auto &cn_trie1 = cn_trie0.at(x2);
                        for (int cn_i = 0; cn_i < cn_trie1.size(); ++cn_i) {
                            auto cn_off = cn_trie1[cn_i];
                            for (int interm0_i = 0; interm0_i < interm0_trie1.size(); ++interm0_i) {
                                auto interm0_off = interm0_trie1[interm0_i];
                                interm1_col0.push_back(mc_company_id[mc_off]);
                                interm1_col1.push_back(mc_company_type_id[mc_off]);
                                interm1_col2.push_back(mc_movie_id[mc_off]);
                                interm1_col3.push_back(cn_name[cn_off]);
                                interm1_col5.push_back(interm0_col2[interm0_off]);
                                interm1_col7.push_back(interm0_col4[interm0_off]);
                                interm1_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        auto interm1_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(interm1_offsets.size());
        build_trie<4>(interm1_trie0, interm1_col2);
        timer.StoreElapsedTime(4);

        vector<int> interm2_col0;
        vector<int> interm2_col1;
        vector<string> interm2_col4;
        vector<string> interm2_col6;
        vector<string> interm2_col8;
        vector<int> interm2_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_keyword_id[mk_off];
            if (k_trie0.contains(x0)) {
                auto &k_trie1 = k_trie0.at(x0);
                auto x1 = mk_movie_id[mk_off];
                if (interm1_trie0.contains(x1)) {
                    auto &interm1_trie1 = interm1_trie0.at(x1);
                    for (int interm1_i = 0; interm1_i < interm1_trie1.size(); ++interm1_i) {
                        auto interm1_off = interm1_trie1[interm1_i];
                        interm2_col0.push_back(mk_keyword_id[mk_off]);
                        interm2_col1.push_back(mk_movie_id[mk_off]);
                        interm2_col4.push_back(interm1_col3[interm1_off]);
                        interm2_col6.push_back(interm1_col5[interm1_off]);
                        interm2_col8.push_back(interm1_col7[interm1_off]);
                        interm2_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(5);

        auto it1_trie0 = phmap::flat_hash_map<int, bool>(it1_offsets.size());
        build_trie(it1_trie0, it1_id);
        auto interm2_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(interm2_offsets.size());
        build_trie<4>(interm2_trie0, interm2_col1);
        timer.StoreElapsedTime(6);

        string mn_interm2_col4 = "zzzzzzzz";
        string mn_interm2_col6 = "zzzzzzzz";
        string mn_interm2_col8 = "zzzzzzzz";
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_info_type_id[mi_off];
            if (it1_trie0.contains(x0)) {
                auto &it1_trie1 = it1_trie0.at(x0);
                auto x1 = mi_movie_id[mi_off];
                if (interm2_trie0.contains(x1)) {
                    auto &interm2_trie1 = interm2_trie0.at(x1);
                    for (int interm2_i = 0; interm2_i < interm2_trie1.size(); ++interm2_i) {
                        auto interm2_off = interm2_trie1[interm2_i];
                        mn_interm2_col4 = min(mn_interm2_col4, interm2_col4[interm2_off]);
                        mn_interm2_col6 = min(mn_interm2_col6, interm2_col6[interm2_off]);
                        mn_interm2_col8 = min(mn_interm2_col8, interm2_col8[interm2_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(7);

        if (iter == 0)
            cout << mn_interm2_col4 << " | " << mn_interm2_col6 << " | " << mn_interm2_col8 << endl;
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
