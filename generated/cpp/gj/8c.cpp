#include "load/8c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8c/cn.csv");
    load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
    load_n1("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
    load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/8c/rt.csv");
    load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
    load_a1("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int z = 0; z < 1 + 5; ++z) {
        int cnt;
        timer.Reset();

        auto mc_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(mc_trie0, mc_company_id);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cn_trie0, cn_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        for (const auto &[x0, mc_trie1] : mc_trie0) {
            if (cn_trie0.contains(x0)) {
                auto &cn_trie1 = cn_trie0.at(x0);
                for (const auto &mc_off : mc_trie1) {
                    interm0_col0.push_back(mc_company_id[mc_off]);
                    interm0_col1.push_back(mc_movie_id[mc_off]);
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto ci_trie0 = phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, bool>>>();
        build_trie(ci_trie0, ci_person_id, ci_movie_id, ci_role_id);
        auto n1_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(n1_trie0, n1_id);
        auto interm0_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(interm0_trie0, interm0_col1);
        auto rt_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(rt_trie0, rt_id);
        auto t_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(t_trie0, t_id);
        auto a1_trie0 = phmap::flat_hash_map<int, vector<int>>();
        build_trie(a1_trie0, a1_person_id);
        timer.StoreElapsedTime(2);

        string mn_t_title = "zzzzzzzz";
        string mn_a1_name = "zzzzzzzz";
        for (const auto &[x0, ci_trie1] : ci_trie0) {
            if (n1_trie0.contains(x0)) {
                auto &n1_trie1 = n1_trie0.at(x0);
                for (const auto &[x1, ci_trie2] : ci_trie1) {
                    if (interm0_trie0.contains(x1)) {
                        auto &interm0_trie1 = interm0_trie0.at(x1);
                        for (const auto &[x2, ci_trie3] : ci_trie2) {
                            if (rt_trie0.contains(x2)) {
                                auto &rt_trie1 = rt_trie0.at(x2);
                                if (t_trie0.contains(x1)) {
                                    auto &t_trie1 = t_trie0.at(x1);
                                    if (a1_trie0.contains(x0)) {
                                        auto &a1_trie1 = a1_trie0.at(x0);
                                        for (const auto &t_off : t_trie1) {
                                            mn_t_title = min(mn_t_title, t_title[t_off]);
                                        }
                                        for (const auto &a1_off : a1_trie1) {
                                            mn_a1_name = min(mn_a1_name, a1_name[a1_off]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (z == 0)
            cout << mn_t_title << " | " << mn_a1_name << endl;
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
