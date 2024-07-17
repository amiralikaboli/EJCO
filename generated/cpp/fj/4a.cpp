#include "load/4a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4a/t.csv");
    load_mi_idx("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4a/mi_idx.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4a/k.csv");
    load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/4a/it.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        unordered_multimap<int, int> mi_idx_trie0(mi_idx_offsets.size());
        build_trie(mi_idx_trie0, mi_idx_movie_id);
        unordered_multimap<int, int> t_trie0(t_offsets.size());
        build_trie(t_trie0, t_id);
        auto it_trie0 = phmap::flat_hash_map<int, bool>(it_offsets.size());
        build_trie(it_trie0, it_id);
        timer.StoreElapsedTime(0);

        string mn_t_title = "zzzzzzzz";
        string mn_mi_idx_info = "zzzzzzzz";
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_keyword_id[mk_off];
            if (k_trie0.contains(x0)) {
                auto &k_trie1 = k_trie0.at(x0);
                auto x1 = mk_movie_id[mk_off];
                auto mi_idx_range = mi_idx_trie0.equal_range(x1);
                auto t_range = t_trie0.equal_range(x1);
                if (mi_idx_range.first != mi_idx_range.second && t_range.first != t_range.second) {
                    for (auto mi_idx_it = mi_idx_range.first; mi_idx_it != mi_idx_range.second; ++mi_idx_it) {
                        auto mi_idx_off = mi_idx_it->second;
                        auto x2 = mi_idx_info_type_id[mi_idx_off];
                        if (it_trie0.contains(x2)) {
                            auto &it_trie1 = it_trie0.at(x2);
                            for (auto t_it = t_range.first; t_it != t_range.second; ++t_it) {
                                auto t_off = t_it->second;
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
