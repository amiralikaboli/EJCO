#include "load/8a.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mc("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8a/mc.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8a/cn.csv");
    load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8a/ci.csv");
    load_n1("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8a/n1.csv");
    load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8a/rt.csv");
    load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
    load_an1("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto cn_trie0 = phmap::flat_hash_map<int, bool>(cn_offsets.size());
        build_trie(cn_trie0, cn_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &mc_off : mc_offsets) {
            auto x0 = mc_company_id[mc_off];
            if (cn_trie0.contains(x0)) {
                auto &cn_trie1 = cn_trie0.at(x0);
                interm0_col0.push_back(mc_company_id[mc_off]);
                interm0_col1.push_back(mc_movie_id[mc_off]);
                interm0_offsets.push_back(cnt++);
            }
        }
        timer.StoreElapsedTime(1);

        auto rt_trie0 = phmap::flat_hash_map<int, bool>(rt_offsets.size());
        build_trie(rt_trie0, rt_id);
        auto n1_trie0 = phmap::flat_hash_map<int, bool>(n1_offsets.size());
        build_trie(n1_trie0, n1_id);
        auto interm0_trie0 = phmap::flat_hash_map<int, bool>(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col1);
        unordered_multimap<int, int> an1_trie0(an1_offsets.size());
        build_trie(an1_trie0, an1_person_id);
        unordered_multimap<int, int> t_trie0(t_offsets.size());
        build_trie(t_trie0, t_id);
        timer.StoreElapsedTime(2);

        string mn_t_title = "zzzzzzzz";
        string mn_an1_name = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_role_id[ci_off];
            if (rt_trie0.contains(x0)) {
                auto &rt_trie1 = rt_trie0.at(x0);
                auto x1 = ci_person_id[ci_off];
                if (n1_trie0.contains(x1)) {
                    auto &n1_trie1 = n1_trie0.at(x1);
                    auto x2 = ci_movie_id[ci_off];
                    if (interm0_trie0.contains(x2)) {
                        auto &interm0_trie1 = interm0_trie0.at(x2);
                        auto an1_range = an1_trie0.equal_range(x1);
                        if (an1_range.first != an1_range.second) {
                            auto t_range = t_trie0.equal_range(x2);
                            if (t_range.first != t_range.second) {
                                for (auto t_it = t_range.first; t_it != t_range.second; ++t_it) {
                                    auto t_off = t_it->second;
                                    mn_t_title = min(mn_t_title, t_title[t_off]);
                                }
                                for (auto an1_it = an1_range.first; an1_it != an1_range.second; ++an1_it) {
                                    auto an1_off = an1_it->second;
                                    mn_an1_name = min(mn_an1_name, an1_name[an1_off]);
                                }
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_t_title << " | " << mn_an1_name << endl;
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
