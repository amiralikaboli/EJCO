#include "load/6b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/6b/t.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/6b/k.csv");
    load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/6b/n.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto k_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(k_offsets.size());
        build_trie<4>(k_trie0, k_id);
        auto t_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(t_offsets.size());
        build_trie<4>(t_trie0, t_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<string> interm0_col3;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_keyword_id[mk_off];
            if (k_trie0.contains(x0)) {
                auto &k_trie1 = k_trie0.at(x0);
                auto x1 = mk_movie_id[mk_off];
                if (t_trie0.contains(x1)) {
                    auto &t_trie1 = t_trie0.at(x1);
                    for (int t_i = 0; t_i < t_trie1.size(); ++t_i) {
                        auto t_off = t_trie1[t_i];
                        for (int k_i = 0; k_i < k_trie1.size(); ++k_i) {
                            auto k_off = k_trie1[k_i];
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

        auto n_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(n_offsets.size());
        build_trie<4>(n_trie0, n_id);
        auto interm0_trie0 = phmap::flat_hash_map<int, smallvec<int, 4>>(interm0_offsets.size());
        build_trie<4>(interm0_trie0, interm0_col0);
        timer.StoreElapsedTime(2);

        string mn_n_name = "zzzzzzzz";
        string mn_interm0_col2 = "zzzzzzzz";
        string mn_interm0_col3 = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_person_id[ci_off];
            if (n_trie0.contains(x0)) {
                auto &n_trie1 = n_trie0.at(x0);
                auto x1 = ci_movie_id[ci_off];
                if (interm0_trie0.contains(x1)) {
                    auto &interm0_trie1 = interm0_trie0.at(x1);
                    for (int n_i = 0; n_i < n_trie1.size(); ++n_i) {
                        auto n_off = n_trie1[n_i];
                        mn_n_name = min(mn_n_name, n_name[n_off]);
                    }
                    for (int interm0_i = 0; interm0_i < interm0_trie1.size(); ++interm0_i) {
                        auto interm0_off = interm0_trie1[interm0_i];
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
