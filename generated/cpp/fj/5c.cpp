#include "load/5c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mi("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/mi.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/t.csv");
    load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/mc.csv");
    load_it("/Users/s2522996/Documents/free-join/data/imdb_csv/info_type.csv");
    load_ct("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/5c/ct.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto it_trie0 = phmap::flat_hash_map<int, bool>(it_offsets.size());
        build_trie(it_trie0, it_id);
        unordered_multimap<int, int> mc_trie0(mc_offsets.size());
        build_trie(mc_trie0, mc_movie_id);
        unordered_multimap<int, int> t_trie0(t_offsets.size());
        build_trie(t_trie0, t_id);
        auto ct_trie0 = phmap::flat_hash_map<int, bool>(ct_offsets.size());
        build_trie(ct_trie0, ct_id);
        timer.StoreElapsedTime(0);

        string mn_t_title = "zzzzzzzz";
        for (const auto &mi_off : mi_offsets) {
            auto x0 = mi_info_type_id[mi_off];
            if (it_trie0.contains(x0)) {
                auto &it_trie1 = it_trie0.at(x0);
                auto x1 = mi_movie_id[mi_off];
                auto mc_range = mc_trie0.equal_range(x1);
                auto t_range = t_trie0.equal_range(x1);
                if (mc_range.first != mc_range.second && t_range.first != t_range.second) {
                    for (auto mc_it = mc_range.first; mc_it != mc_range.second; ++mc_it) {
                        auto mc_off = mc_it->second;
                        auto x2 = mc_company_type_id[mc_off];
                        if (ct_trie0.contains(x2)) {
                            auto &ct_trie1 = ct_trie0.at(x2);
                            for (auto t_it = t_range.first; t_it != t_range.second; ++t_it) {
                                auto t_off = t_it->second;
                                mn_t_title = min(mn_t_title, t_title[t_off]);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        if (iter == 0)
            cout << mn_t_title << endl;
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
