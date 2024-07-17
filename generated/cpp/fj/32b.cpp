#include "load/32b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t1("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
    load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
    load_t2("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_lt("/Users/s2522996/Documents/free-join/data/imdb_csv/link_type.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/32b/k.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        unordered_multimap<int, int> ml_trie0(ml_offsets.size());
        build_trie(ml_trie0, ml_movie_id);
        unordered_multimap<int, int> t2_trie0(t2_offsets.size());
        build_trie(t2_trie0, t2_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<int> interm0_col3;
        vector<string> interm0_col4;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &t1_off : t1_offsets) {
            auto x0 = t1_id[t1_off];
            auto ml_range = ml_trie0.equal_range(x0);
            if (ml_range.first != ml_range.second) {
                for (auto ml_it = ml_range.first; ml_it != ml_range.second; ++ml_it) {
                    auto ml_off = ml_it->second;
                    auto x1 = ml_linked_movie_id[ml_off];
                    auto t2_range = t2_trie0.equal_range(x1);
                    if (t2_range.first != t2_range.second) {
                        for (auto t2_it = t2_range.first; t2_it != t2_range.second; ++t2_it) {
                            auto t2_off = t2_it->second;
                            interm0_col0.push_back(t1_id[t1_off]);
                            interm0_col1.push_back(t1_title[t1_off]);
                            interm0_col2.push_back(ml_linked_movie_id[ml_off]);
                            interm0_col3.push_back(ml_link_type_id[ml_off]);
                            interm0_col4.push_back(t2_title[t2_off]);
                            interm0_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        unordered_multimap<int, int> interm0_trie0(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col0);
        unordered_multimap<int, int> lt_trie0(lt_offsets.size());
        build_trie(lt_trie0, lt_id);
        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col1 = "zzzzzzzz";
        string mn_interm0_col4 = "zzzzzzzz";
        string mn_lt_link = "zzzzzzzz";
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_movie_id[mk_off];
            auto interm0_range = interm0_trie0.equal_range(x0);
            if (interm0_range.first != interm0_range.second) {
                for (auto interm0_it = interm0_range.first; interm0_it != interm0_range.second; ++interm0_it) {
                    auto interm0_off = interm0_it->second;
                    auto x1 = interm0_col3[interm0_off];
                    auto lt_range = lt_trie0.equal_range(x1);
                    if (lt_range.first != lt_range.second) {
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                            for (auto lt_it = lt_range.first; lt_it != lt_range.second; ++lt_it) {
                                auto lt_off = lt_it->second;
                                mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_interm0_col1 << " | " << mn_interm0_col4 << " | " << mn_lt_link << endl;
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
