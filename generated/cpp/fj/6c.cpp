#include "load/6c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/6c/t.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/6c/k.csv");
    load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/6c/n.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        unordered_multimap<int, int> k_trie0(k_offsets.size());
        build_trie(k_trie0, k_id);
        unordered_multimap<int, int> t_trie0(t_offsets.size());
        build_trie(t_trie0, t_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<string> interm0_col3;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_keyword_id[mk_off];
            auto k_range = k_trie0.equal_range(x0);
            if (k_range.first != k_range.second) {
                auto x1 = mk_movie_id[mk_off];
                auto t_range = t_trie0.equal_range(x1);
                if (t_range.first != t_range.second) {
                    for (auto t_it = t_range.first; t_it != t_range.second; ++t_it) {
                        auto t_off = t_it->second;
                        for (auto k_it = k_range.first; k_it != k_range.second; ++k_it) {
                            auto k_off = k_it->second;
                            interm0_col0.push_back(mk_movie_id[mk_off]);
                            interm0_col1.push_back(mk_keyword_id[mk_off]);
                            interm0_col2.push_back(t_title[t_off]);
                            interm0_col3.push_back(k_keyword[k_off]);
                            interm0_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        unordered_multimap<int, int> n_trie0(n_offsets.size());
        build_trie(n_trie0, n_id);
        unordered_multimap<int, int> interm0_trie0(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col0);
        timer.StoreElapsedTime(2);

        string mn_n_name = "zzzzzzzz";
        string mn_interm0_col2 = "zzzzzzzz";
        string mn_interm0_col3 = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_person_id[ci_off];
            auto n_range = n_trie0.equal_range(x0);
            if (n_range.first != n_range.second) {
                auto x1 = ci_movie_id[ci_off];
                auto interm0_range = interm0_trie0.equal_range(x1);
                if (interm0_range.first != interm0_range.second) {
                    for (auto n_it = n_range.first; n_it != n_range.second; ++n_it) {
                        auto n_off = n_it->second;
                        mn_n_name = min(mn_n_name, n_name[n_off]);
                    }
                    for (auto interm0_it = interm0_range.first; interm0_it != interm0_range.second; ++interm0_it) {
                        auto interm0_off = interm0_it->second;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_n_name << " | " << mn_interm0_col2 << " | " << mn_interm0_col3 << endl;
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
