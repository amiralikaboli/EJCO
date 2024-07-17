#include "load/16d.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16d/t.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16d/k.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16d/cn.csv");
    load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
    load_n("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
    load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
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

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<int> interm0_col3;
        vector<int> interm0_offsets;
        cnt = 0;
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
                                interm0_col0.push_back(mk_movie_id[mk_off]);
                                interm0_col1.push_back(mk_keyword_id[mk_off]);
                                interm0_col2.push_back(t_title[t_off]);
                                interm0_col3.push_back(mc_company_id[mc_off]);
                                interm0_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        unordered_multimap<int, int> interm0_trie0(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col0);
        unordered_multimap<int, int> an_trie0(an_offsets.size());
        build_trie(an_trie0, an_person_id);
        auto n_trie0 = phmap::flat_hash_map<int, bool>(n_offsets.size());
        build_trie(n_trie0, n_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col2 = "zzzzzzzz";
        string mn_an_name = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_movie_id[ci_off];
            auto interm0_range = interm0_trie0.equal_range(x0);
            if (interm0_range.first != interm0_range.second) {
                auto x1 = ci_person_id[ci_off];
                auto an_range = an_trie0.equal_range(x1);
                if (an_range.first != an_range.second && n_trie0.contains(x1)) {
                    auto &n_trie1 = n_trie0.at(x1);
                    for (auto interm0_it = interm0_range.first; interm0_it != interm0_range.second; ++interm0_it) {
                        auto interm0_off = interm0_it->second;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                    }
                    for (auto an_it = an_range.first; an_it != an_range.second; ++an_it) {
                        auto an_off = an_it->second;
                        mn_an_name = min(mn_an_name, an_name[an_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_interm0_col2 << " | " << mn_an_name << endl;
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
