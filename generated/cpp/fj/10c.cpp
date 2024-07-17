#include "load/10c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/10c/t.csv");
    load_ct("/Users/s2522996/Documents/free-join/data/imdb_csv/company_type.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/10c/cn.csv");
    load_ci("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/10c/ci.csv");
    load_rt("/Users/s2522996/Documents/free-join/data/imdb_csv/role_type.csv");
    load_chn("/Users/s2522996/Documents/free-join/data/imdb_csv/char_name.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int iter = 0; iter < 1 + 5; ++iter) {
        int cnt;
        timer.Reset();

        auto ct_trie0 = phmap::flat_hash_map<int, bool>(ct_offsets.size());
        build_trie(ct_trie0, ct_id);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>(cn_offsets.size());
        build_trie(cn_trie0, cn_id);
        unordered_multimap<int, int> t_trie0(t_offsets.size());
        build_trie(t_trie0, t_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<int> interm0_col2;
        vector<string> interm0_col3;
        vector<int> interm0_offsets;
        cnt = 0;
        for (const auto &mc_off : mc_offsets) {
            auto x0 = mc_company_type_id[mc_off];
            if (ct_trie0.contains(x0)) {
                auto &ct_trie1 = ct_trie0.at(x0);
                auto x1 = mc_company_id[mc_off];
                if (cn_trie0.contains(x1)) {
                    auto &cn_trie1 = cn_trie0.at(x1);
                    auto x2 = mc_movie_id[mc_off];
                    auto t_range = t_trie0.equal_range(x2);
                    if (t_range.first != t_range.second) {
                        for (auto t_it = t_range.first; t_it != t_range.second; ++t_it) {
                            auto t_off = t_it->second;
                            interm0_col0.push_back(mc_movie_id[mc_off]);
                            interm0_col1.push_back(mc_company_type_id[mc_off]);
                            interm0_col2.push_back(mc_company_id[mc_off]);
                            interm0_col3.push_back(t_title[t_off]);
                            interm0_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto rt_trie0 = phmap::flat_hash_map<int, bool>(rt_offsets.size());
        build_trie(rt_trie0, rt_id);
        unordered_multimap<int, int> interm0_trie0(interm0_offsets.size());
        build_trie(interm0_trie0, interm0_col0);
        unordered_multimap<int, int> chn_trie0(chn_offsets.size());
        build_trie(chn_trie0, chn_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col3 = "zzzzzzzz";
        string mn_chn_name = "zzzzzzzz";
        for (const auto &ci_off : ci_offsets) {
            auto x0 = ci_role_id[ci_off];
            if (rt_trie0.contains(x0)) {
                auto &rt_trie1 = rt_trie0.at(x0);
                auto x1 = ci_movie_id[ci_off];
                auto interm0_range = interm0_trie0.equal_range(x1);
                if (interm0_range.first != interm0_range.second) {
                    auto x2 = ci_person_role_id[ci_off];
                    auto chn_range = chn_trie0.equal_range(x2);
                    if (chn_range.first != chn_range.second) {
                        for (auto interm0_it = interm0_range.first; interm0_it != interm0_range.second; ++interm0_it) {
                            auto interm0_off = interm0_it->second;
                            mn_interm0_col3 = min(mn_interm0_col3, interm0_col3[interm0_off]);
                        }
                        for (auto chn_it = chn_range.first; chn_it != chn_range.second; ++chn_it) {
                            auto chn_off = chn_it->second;
                            mn_chn_name = min(mn_chn_name, chn_name[chn_off]);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (iter == 0)
            cout << mn_interm0_col3 << " | " << mn_chn_name << endl;
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
