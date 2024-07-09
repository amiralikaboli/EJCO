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

    for (int z = 0; z < 1 + 5; ++z) {
        int cnt;
        timer.Reset();

        auto mk_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(mk_trie0, mk_movie_id);
        auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(t_trie0, t_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        for (const auto &[x0, mk_trie1] : mk_trie0) {
            if (t_trie0.contains(x0)) {
                auto &t_trie1 = t_trie0.at(x0);
                for (const auto &mk_off : mk_trie1) {
                    for (const auto &t_off : t_trie1) {
                        interm0_col0.push_back(mk_movie_id[mk_off]);
                        interm0_col1.push_back(mk_keyword_id[mk_off]);
                        interm0_col2.push_back(t_title[t_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto mi_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>();
        build_trie(mi_trie0, mi_movie_id, mi_info_type_id);
        auto interm0_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, vector<int>>>();
        build_trie(interm0_trie0, interm0_col0, interm0_col1);
        auto mc_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
        build_trie(mc_trie0, mc_movie_id, mc_company_type_id, mc_company_id);
        auto k_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(k_trie0, k_id);
        auto it1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(it1_trie0, it1_id);
        auto ct_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(ct_trie0, ct_id);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cn_trie0, cn_id);
        auto at_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(at_trie0, at_movie_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col2 = "zzzzzzzz";
        string mn_at_title = "zzzzzzzz";
        for (const auto &[x0, mi_trie1] : mi_trie0) {
            if (interm0_trie0.contains(x0) && mc_trie0.contains(x0)) {
                auto &interm0_trie1 = interm0_trie0.at(x0);
                auto &mc_trie1 = mc_trie0.at(x0);
                for (const auto &[x1, interm0_trie2] : interm0_trie1) {
                    if (k_trie0.contains(x1)) {
                        auto &k_trie1 = k_trie0.at(x1);
                        for (const auto &[x2, mi_trie2] : mi_trie1) {
                            if (it1_trie0.contains(x2)) {
                                auto &it1_trie1 = it1_trie0.at(x2);
                                for (const auto &[x3, mc_trie2] : mc_trie1) {
                                    if (ct_trie0.contains(x3)) {
                                        auto &ct_trie1 = ct_trie0.at(x3);
                                        for (const auto &[x4, mc_trie3] : mc_trie2) {
                                            if (cn_trie0.contains(x4)) {
                                                auto &cn_trie1 = cn_trie0.at(x4);
                                                if (at_trie0.contains(x0)) {
                                                    auto &at_trie1 = at_trie0.at(x0);
                                                    for (const auto &interm0_off : interm0_trie2) {
                                                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                                                    }
                                                    for (const auto &at_off : at_trie1) {
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
            }
        }
        timer.StoreElapsedTime(3);

        if (z == 0)
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
