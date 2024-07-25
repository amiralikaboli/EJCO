#include "load/4c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4c/t.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4c/mi_idx.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4c/k.csv");
    load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4c/it.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        for (int i = 0; i < k_offsets.size(); ++i)
            k_trie0[k_id[i]] += 1;
        auto mi_idx_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(mi_idx_offsets.size());
        for (int i = 0; i < mi_idx_offsets.size(); ++i)
            mi_idx_trie0[mi_idx_movie_id[i]][i] += 1;
        auto t_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(t_offsets.size());
        for (int i = 0; i < t_offsets.size(); ++i)
            t_trie0[t_id[i]][i] += 1;
        auto it_trie0 = phmap::flat_hash_map<int, bool>(it_offsets.size());
        for (int i = 0; i < it_offsets.size(); ++i)
            it_trie0[it_id[i]] += 1;
        timer.StoreElapsedTime(0);

        string mn_t_title = "zzzzzzzz";
        string mn_mi_idx_info = "zzzzzzzz";
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_keyword_id[mk_off];
            if (k_trie0.contains(x0)) {
                auto &k_trie1 = k_trie0.at(x0);
                auto x1 = mk_movie_id[mk_off];
                if (mi_idx_trie0.contains(x1) && t_trie0.contains(x1)) {
                    auto &mi_idx_trie1 = mi_idx_trie0.at(x1);
                    auto &t_trie1 = t_trie0.at(x1);
                    for (const auto &mi_idx_off : mi_idx_trie1) {
                        auto x2 = mi_idx_info_type_id[mi_idx_off];
                        if (it_trie0.contains(x2)) {
                            auto &it_trie1 = it_trie0.at(x2);
                            for (const auto &t_off : t_trie1) {
                                mn_t_title = min(mn_t_title, t_title[t_off]);
                            }
                            mn_mi_idx_info = min(mn_mi_idx_info, mi_idx_info[mi_idx_off]);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        if (iter == 0)
            cout << mn_t_title << " | " << mn_mi_idx_info << endl;
        cout << "*" << " " << flush;
    }
    cout << endl;

    vector<double> tm{0};
    for (int i = 0; i < 2 * 1; ++i)
        tm.push_back(timer.GetMean(i));
    for (int i = 0; i < 2 * 1; i += 2) {
        cout << tm[i + 1] - tm[i] << " + ";
        cout << tm[i + 2] - tm[i + 1] << " = ";
        cout << tm[i + 2] - tm[i] << " ms" << endl;
    }
    cout << tm[2 * 1] << " ms" << endl;
}
