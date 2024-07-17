#include "load/3b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3b/t.csv");
    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3b/mi.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/3b/k.csv");
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
        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col2 = "zzzzzzzz";
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_movie_id[mi_off];
            auto interm0_range = interm0_trie0.equal_range(x0);
            if (interm0_range.first != interm0_range.second) {
                for (auto interm0_it = interm0_range.first; interm0_it != interm0_range.second; ++interm0_it) {
                    auto interm0_off = interm0_it->second;
                    auto x1 = interm0_col1[interm0_off];
                    if (k_trie0.contains(x1)) {
                        auto &k_trie1 = k_trie0.at(x1);
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_interm0_col2 << endl;
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
