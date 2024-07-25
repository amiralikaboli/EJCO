#include "load/11a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/t.csv");
    load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/mc.csv");
    load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/lt.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/k.csv");
    load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/ct.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/11a/cn.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto ml_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(ml_offsets.size());
        for (int i = 0; i < ml_offsets.size(); ++i)
            ml_trie0[ml_movie_id[i]][i] += 1;
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_id[t_off];
            if (ml_trie0.contains(x0)) {
                auto &ml_trie1 = ml_trie0.at(x0);
                for (const auto &ml_off : ml_trie1) {
                    interm0_col0.push_back(t_id[t_off]);
                    interm0_col1.push_back(t_title[t_off]);
                    interm0_col2.push_back(ml_link_type_id[ml_off]);
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
        auto lt_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(lt_offsets.size());
        for (int i = 0; i < lt_offsets.size(); ++i)
            lt_trie0[lt_id[i]][i] += 1;
        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        for (int i = 0; i < k_offsets.size(); ++i)
            k_trie0[k_id[i]] += 1;
        auto ct_trie0 = phmap::flat_hash_map<int, bool>(ct_offsets.size());
        for (int i = 0; i < ct_offsets.size(); ++i)
            ct_trie0[ct_id[i]] += 1;
        auto cn_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(cn_offsets.size());
        for (int i = 0; i < cn_offsets.size(); ++i)
            cn_trie0[cn_id[i]][i] += 1;
        timer.StoreElapsedTime(2);

        string mn_interm0_col1 = "zzzzzzzz";
        string mn_lt_link = "zzzzzzzz";
        string mn_cn_name = "zzzzzzzz";
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_movie_id[mk_off];
            if (interm0_trie0.contains(x0) && mc_trie0.contains(x0)) {
                auto &interm0_trie1 = interm0_trie0.at(x0);
                auto &mc_trie1 = mc_trie0.at(x0);
                for (const auto &interm0_off : interm0_trie1) {
                    auto x1 = interm0_col2[interm0_off];
                    if (lt_trie0.contains(x1)) {
                        auto &lt_trie1 = lt_trie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            for (const auto &mc_off : mc_trie1) {
                                auto x3 = mc_company_type_id[mc_off];
                                if (ct_trie0.contains(x3)) {
                                    auto &ct_trie1 = ct_trie0.at(x3);
                                    auto x4 = mc_company_id[mc_off];
                                    if (cn_trie0.contains(x4)) {
                                        auto &cn_trie1 = cn_trie0.at(x4);
                                        mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                        for (const auto &lt_off : lt_trie1) {
                                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                        }
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
            cout << mn_interm0_col1 << " | " << mn_lt_link << " | " << mn_cn_name << endl;
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
