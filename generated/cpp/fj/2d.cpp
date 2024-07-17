#include "load/2d.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/2d/k.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/2d/cn.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto k_trie0 = phmap::flat_hash_map<int, bool>(k_offsets.size());
        build_trie(k_trie0, k_id);
        unordered_multimap<int, int> t_trie0(t_offsets.size());
        build_trie(t_trie0, t_id);
        unordered_multimap<int, int> mc_trie0(mc_offsets.size());
        build_trie(mc_trie0, mc_movie_id);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>(cn_offsets.size());
        build_trie(cn_trie0, cn_id);
        timer.StoreElapsedTime(0);

        string mn_t_title = "zzzzzzzz";
        for (const auto &mk_off : mk_offsets) {
            auto x0 = mk_keyword_id[mk_off];
            if (k_trie0.contains(x0)) {
                auto &k_trie1 = k_trie0.at(x0);
                auto x1 = mk_movie_id[mk_off];
                auto t_range = t_trie0.equal_range(x1);
                auto mc_range = mc_trie0.equal_range(x1);
                if (t_range.first != t_range.second && mc_range.first != mc_range.second) {
                    for (auto mc_it = mc_range.first; mc_it != mc_range.second; ++mc_it) {
                        auto mc_off = mc_it->second;
                        auto x2 = mc_company_id[mc_off];
                        if (cn_trie0.contains(x2)) {
                            auto &cn_trie1 = cn_trie0.at(x2);
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
