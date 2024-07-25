#include "load/1d.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1d/t.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_info_idx.csv");
    load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1d/mc.csv");
    load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1d/it.csv");
    load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/1d/ct.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto mi_idx_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(mi_idx_offsets.size());
        for (int i = 0; i < mi_idx_offsets.size(); ++i)
            mi_idx_trie0[mi_idx_movie_id[i]][i] += 1;
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<int> interm0_col3;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_id[t_off];
            if (mi_idx_trie0.contains(x0)) {
                auto &mi_idx_trie1 = mi_idx_trie0.at(x0);
                for (const auto &mi_idx_off : mi_idx_trie1) {
                    interm0_col0.push_back(t_id[t_off]);
                    interm0_col1.push_back(t_title[t_off]);
                    interm0_col2.push_back(t_production_year[t_off]);
                    interm0_col3.push_back(mi_idx_info_type_id[mi_idx_off]);
                    interm0_offsets.push_back(cnt++);
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto interm0_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(interm0_offsets.size());
        for (int i = 0; i < interm0_offsets.size(); ++i)
            interm0_trie0[interm0_col0[i]][i] += 1;
        auto it_trie0 = phmap::flat_hash_map<int, bool>(it_offsets.size());
        for (int i = 0; i < it_offsets.size(); ++i)
            it_trie0[it_id[i]] += 1;
        auto ct_trie0 = phmap::flat_hash_map<int, bool>(ct_offsets.size());
        for (int i = 0; i < ct_offsets.size(); ++i)
            ct_trie0[ct_id[i]] += 1;
        timer.StoreElapsedTime(2);

        string mn_mc_note = "zzzzzzzz";
        string mn_interm0_col1 = "zzzzzzzz";
        int mn_interm0_col2 = numeric_limits<int>::max();
        for (const auto &mc_off : mc_offsets) {
            auto x0 = mc_movie_id[mc_off];
            if (interm0_trie0.contains(x0)) {
                auto &interm0_trie1 = interm0_trie0.at(x0);
                for (const auto &interm0_off : interm0_trie1) {
                    auto x1 = interm0_col3[interm0_off];
                    if (it_trie0.contains(x1)) {
                        auto &it_trie1 = it_trie0.at(x1);
                        auto x2 = mc_company_type_id[mc_off];
                        if (ct_trie0.contains(x2)) {
                            auto &ct_trie1 = ct_trie0.at(x2);
                            mn_mc_note = min(mn_mc_note, mc_note[mc_off]);
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_mc_note << " | " << mn_interm0_col1 << " | " << mn_interm0_col2 << endl;
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
