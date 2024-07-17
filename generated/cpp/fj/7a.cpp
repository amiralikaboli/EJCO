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

        unordered_multimap<int, int> pi_trie0(pi_offsets.size());
        build_trie(pi_trie0, pi_person_id);
        auto it_trie0 = phmap::flat_hash_map<int, bool>(it_offsets.size());
        build_trie(it_trie0, it_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &n_off : n_offsets) {
            auto x0 = n_id[n_off];
            auto pi_range = pi_trie0.equal_range(x0);
            if (pi_range.first != pi_range.second) {
                for (auto pi_it = pi_range.first; pi_it != pi_range.second; ++pi_it) {
                    auto pi_off = pi_it->second;
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

        unordered_multimap<int, int> ml_trie0(ml_offsets.size());
        build_trie(ml_trie0, ml_linked_movie_id);
        auto lt_trie0 = phmap::flat_hash_map<int, bool>(lt_offsets.size());
        build_trie(lt_trie0, lt_id);
        timer.StoreElapsedTime(2);

        vector<int> interm1_col0;
        vector<string> interm1_col1;
        vector<int> interm1_col2;
        vector<int> interm1_offsets;
        cnt = 0;
        for (const auto &t_off : t_offsets) {
            auto x0 = t_id[t_off];
            auto ml_range = ml_trie0.equal_range(x0);
            if (ml_range.first != ml_range.second) {
                for (auto ml_it = ml_range.first; ml_it != ml_range.second; ++ml_it) {
                    auto ml_off = ml_it->second;
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

        unordered_multimap<int, int> interm0_trie0(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col0);
        unordered_multimap<int, int> interm1_trie0(interm1_offsets.size());
        build_trie(interm1_trie0, interm1_col0);
        auto an_trie0 = phmap::flat_hash_map<int, bool>(an_offsets.size());
        build_trie(an_trie0, an_person_id);
        timer.StoreElapsedTime(4);

        string mn_interm1_col1 = "zzzzzzzz";
        string mn_interm0_col1 = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_person_id[ci_off];
            auto interm0_range = interm0_trie0.equal_range(x0);
            if (interm0_range.first != interm0_range.second) {
                auto x1 = ci_movie_id[ci_off];
                auto interm1_range = interm1_trie0.equal_range(x1);
                if (interm1_range.first != interm1_range.second) {
                    if (an_trie0.contains(x0)) {
                        auto &an_trie1 = an_trie0.at(x0);
                        for (auto interm1_it = interm1_range.first; interm1_it != interm1_range.second; ++interm1_it) {
                            auto interm1_off = interm1_it->second;
                            mn_interm1_col1 = min(mn_interm1_col1, interm1_col1[interm1_off]);
                        }
                        for (auto interm0_it = interm0_range.first; interm0_it != interm0_range.second; ++interm0_it) {
                            auto interm0_off = interm0_it->second;
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
