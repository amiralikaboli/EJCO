#include "load/9d.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9d/cn.csv");
    load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9d/ci.csv");
    load_n("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9d/n.csv");
    load_rt("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/9d/rt.csv");
    load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
    load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
    load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto cn_trie0 = phmap::flat_hash_map<int, bool>(cn_offsets.size());
        for (int i = 0; i < cn_offsets.size(); ++i)
            cn_trie0[cn_id[i]] += 1;
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
        for (int i = 0; i < rt_offsets.size(); ++i)
            rt_trie0[rt_id[i]] += 1;
        auto an_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(an_offsets.size());
        for (int i = 0; i < an_offsets.size(); ++i)
            an_trie0[an_person_id[i]][i] += 1;
        auto n_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(n_offsets.size());
        for (int i = 0; i < n_offsets.size(); ++i)
            n_trie0[n_id[i]][i] += 1;
        auto interm0_trie0 = phmap::flat_hash_map<int, bool>(interm0_offsets.size());
        for (int i = 0; i < interm0_offsets.size(); ++i)
            interm0_trie0[interm0_col1[i]] += 1;
        auto t_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(t_offsets.size());
        for (int i = 0; i < t_offsets.size(); ++i)
            t_trie0[t_id[i]][i] += 1;
        auto chn_trie0 = phmap::flat_hash_map<int, smallvecdict<int, 4>>(chn_offsets.size());
        for (int i = 0; i < chn_offsets.size(); ++i)
            chn_trie0[chn_id[i]][i] += 1;
        timer.StoreElapsedTime(2);

        string mn_n_name = "zzzzzzzz";
        string mn_t_title = "zzzzzzzz";
        string mn_chn_name = "zzzzzzzz";
        string mn_an_name = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_role_id[ci_off];
            if (rt_trie0.contains(x0)) {
                auto &rt_trie1 = rt_trie0.at(x0);
                auto x1 = ci_person_id[ci_off];
                if (an_trie0.contains(x1) && n_trie0.contains(x1)) {
                    auto &an_trie1 = an_trie0.at(x1);
                    auto &n_trie1 = n_trie0.at(x1);
                    auto x2 = ci_movie_id[ci_off];
                    if (interm0_trie0.contains(x2) && t_trie0.contains(x2)) {
                        auto &interm0_trie1 = interm0_trie0.at(x2);
                        auto &t_trie1 = t_trie0.at(x2);
                        auto x3 = ci_person_role_id[ci_off];
                        if (chn_trie0.contains(x3)) {
                            auto &chn_trie1 = chn_trie0.at(x3);
                            for (const auto &n_off : n_trie1) {
                                mn_n_name = min(mn_n_name, n_name[n_off]);
                            }
                            for (const auto &t_off : t_trie1) {
                                mn_t_title = min(mn_t_title, t_title[t_off]);
                            }
                            for (const auto &chn_off : chn_trie1) {
                                mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                            }
                            for (const auto &an_off : an_trie1) {
                                mn_an_name = min(mn_an_name, an_name[an_off]);
                            }
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_n_name << " | " << mn_t_title << " | " << mn_chn_name << " | " << mn_an_name << endl;
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
