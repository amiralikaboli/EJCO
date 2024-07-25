#include "load/7a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/n.csv");
    load_pi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/pi.csv");
    load_it("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/it.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/t.csv");
    load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
    load_lt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/lt.csv");
    load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
    load_an("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/7a/an.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto pi_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(pi_offsets.size());
        for (int i = 0; i < pi_offsets.size(); ++i)
            pi_trie0[pi_person_id[i]][i] += 1;
        auto it_trie0 = phmap::flat_hash_map<int, bool>(it_offsets.size());
        for (int i = 0; i < it_offsets.size(); ++i)
            it_trie0[it_id[i]] += 1;
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &n_off : n_offsets) {
            auto x0 = n_id[n_off];
            if (pi_trie0.contains(x0)) {
                auto &pi_trie1 = pi_trie0.at(x0);
                for (const auto &pi_off : pi_trie1) {
                    auto x1 = pi_info_type_id[pi_off];
                    if (it_trie0.contains(x1)) {
                        auto &it_trie1 = it_trie0.at(x1);
                        interm0_col0.push_back(n_id[n_off]);
                        interm0_col1.push_back(n_name[n_off]);
                        interm0_col2.push_back(pi_info_type_id[pi_off]);
                        interm0_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto ml_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(ml_offsets.size());
        for (int i = 0; i < ml_offsets.size(); ++i)
            ml_trie0[ml_linked_movie_id[i]][i] += 1;
        auto lt_trie0 = phmap::flat_hash_map<int, bool>(lt_offsets.size());
        for (int i = 0; i < lt_offsets.size(); ++i)
            lt_trie0[lt_id[i]] += 1;
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<string> interm1_col1;
        vector<int> interm1_col2;
        vector<int> interm1_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_id[t_off];
            if (ml_trie0.contains(x0)) {
                auto &ml_trie1 = ml_trie0.at(x0);
                for (const auto &ml_off : ml_trie1) {
                    auto x1 = ml_link_type_id[ml_off];
                    if (lt_trie0.contains(x1)) {
                        auto &lt_trie1 = lt_trie0.at(x1);
                        interm1_col0.push_back(t_id[t_off]);
                        interm1_col1.push_back(t_title[t_off]);
                        interm1_col2.push_back(ml_link_type_id[ml_off]);
                        interm1_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        auto interm0_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(interm0_offsets.size());
        for (int i = 0; i < interm0_offsets.size(); ++i)
            interm0_trie0[interm0_col0[i]][i] += 1;
        auto interm1_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(interm1_offsets.size());
        for (int i = 0; i < interm1_offsets.size(); ++i)
            interm1_trie0[interm1_col0[i]][i] += 1;
        auto an_trie0 = phmap::flat_hash_map<int, bool>(an_offsets.size());
        for (int i = 0; i < an_offsets.size(); ++i)
            an_trie0[an_person_id[i]] += 1;
        timer.StoreElapsedTime(4);

        string mn_interm1_col1 = "zzzzzzzz";
        string mn_interm0_col1 = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_person_id[ci_off];
            if (interm0_trie0.contains(x0)) {
                auto &interm0_trie1 = interm0_trie0.at(x0);
                auto x1 = ci_movie_id[ci_off];
                if (interm1_trie0.contains(x1)) {
                    auto &interm1_trie1 = interm1_trie0.at(x1);
                    if (an_trie0.contains(x0)) {
                        auto &an_trie1 = an_trie0.at(x0);
                        for (const auto &interm1_off : interm1_trie1) {
                            mn_interm1_col1 = min(mn_interm1_col1, interm1_col1[interm1_off]);
                        }
                        for (const auto &interm0_off : interm0_trie1) {
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(5);

        if (iter == 0)
            cout << mn_interm1_col1 << " | " << mn_interm0_col1 << endl;
        cout << "*" << " " << flush;
    }
    cout << endl;

    vector<double> tm{0};
    for (int i = 0; i < 2 * 3; ++i)
        tm.push_back(timer.GetMean(i));
    for (int i = 0; i < 2 * 3; i += 2) {
        cout << tm[i + 1] - tm[i] << " + ";
        cout << tm[i + 2] - tm[i + 1] << " = ";
        cout << tm[i + 2] - tm[i] << " ms" << endl;
    }
    cout << tm[2 * 3] << " ms" << endl;
}
