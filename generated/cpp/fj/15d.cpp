#include "load/15d.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15d/t.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15d/mi.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_k("/Users/s2522996/Documents/free-join/data/imdb_csv/keyword.csv");
    load_it1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15d/it1.csv");
    load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/15d/cn.csv");
    load_at("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_title.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto t_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(t_offsets.size());
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

        auto mc_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(mc_offsets.size());
        build_trie<4>(mc_trie0, mc_movie_id);
        auto interm0_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(interm0_offsets.size());
        build_trie<4>(interm0_trie0, interm0_col0);
        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        auto it1_trie0 = phmap::flat_hash_map<int, bool>(it1_offsets.size());
        build_trie(it1_trie0, it1_id);
        auto ct_trie0 = phmap::flat_hash_map<int, bool>(ct_offsets.size());
        build_trie(ct_trie0, ct_id);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>(cn_offsets.size());
        build_trie(cn_trie0, cn_id);
        auto at_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(at_offsets.size());
        build_trie<4>(at_trie0, at_movie_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col2 = "zzzzzzzz";
        string mn_at_title = "zzzzzzzz";
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_movie_id[mi_off];
            if (mc_trie0.contains(x0) && interm0_trie0.contains(x0)) {
                auto &mc_trie1 = mc_trie0.at(x0);
                auto &interm0_trie1 = interm0_trie0.at(x0);
                for (int interm0_i = 0; interm0_i < interm0_trie1.size(); ++interm0_i) {
                    auto interm0_off = interm0_trie1[interm0_i];
                    auto x1 = interm0_col1[interm0_off];
                    if (k_trie0.contains(x1)) {
                        auto &k_trie1 = k_trie0.at(x1);
                        auto x2 = mi_info_type_id[mi_off];
                        if (it1_trie0.contains(x2)) {
                            auto &it1_trie1 = it1_trie0.at(x2);
                            for (int mc_i = 0; mc_i < mc_trie1.size(); ++mc_i) {
                                auto mc_off = mc_trie1[mc_i];
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_trie0.contains(x4)) {
                                        auto &cn_trie1 = cn_trie0.at(x4);
                                        if (at_trie0.contains(x0)) {
                                            auto &at_trie1 = at_trie0.at(x0);
                                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                                            for (int at_i = 0; at_i < at_trie1.size(); ++at_i) {
                                                auto at_off = at_trie1[at_i];
                                                mn_at_title = min(mn_at_title, at_title[at_off]);
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
            cout << mn_interm0_col2 << " | " << mn_at_title << endl;
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
