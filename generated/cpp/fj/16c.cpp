#include "load/16c.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_t("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16c/t.csv");
    load_mc("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_companies.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16c/k.csv");
    load_cn("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/16c/cn.csv");
    load_ci("/Users/s2522996/Documents/free-join/data/imdb_csv/cast_info.csv");
    load_n("/Users/s2522996/Documents/free-join/data/imdb_csv/name.csv");
    load_an("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int z = 0; z < 1 + 5; ++z) {
        int cnt;
        timer.Reset();

        auto k_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(k_trie0, k_offsets, k_id);
        auto t_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto t_itrie0 = phmap::flat_hash_map<int, int>();
        auto t_isunq = build_trie(t_vtrie0, t_itrie0, t_offsets, t_id);
        auto mc_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto mc_itrie0 = phmap::flat_hash_map<int, int>();
        auto mc_isunq = build_trie(mc_vtrie0, mc_itrie0, mc_offsets, mc_movie_id);
        auto cn_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(cn_trie0, cn_offsets, cn_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<int> interm0_col1;
        vector<string> interm0_col2;
        vector<int> interm0_col3;
        vector<int> interm0_offsets;
        cnt = 0;
        if (t_isunq == 0 && mc_isunq == 0) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_vtrie0.contains(x1) && mc_vtrie0.contains(x1)) {
                        auto &t_vtrie1 = t_vtrie0.at(x1);
                        auto &mc_vtrie1 = mc_vtrie0.at(x1);
                        for (const auto &mc_off : mc_vtrie1) {
                            auto x2 = mc_company_id[mc_off];
                            if (cn_trie0.contains(x2)) {
                                auto &cn_trie1 = cn_trie0.at(x2);
                                for (const auto &t_off : t_vtrie1) {
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
        } else if (t_isunq == 0 && mc_isunq == 1) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_vtrie0.contains(x1) && mc_itrie0.contains(x1)) {
                        auto &t_vtrie1 = t_vtrie0.at(x1);
                        auto &mc_itrie1 = mc_itrie0.at(x1);
                        auto &mc_off = mc_itrie1;
                        auto x2 = mc_company_id[mc_off];
                        if (cn_trie0.contains(x2)) {
                            auto &cn_trie1 = cn_trie0.at(x2);
                            for (const auto &t_off : t_vtrie1) {
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
        } else if (t_isunq == 1 && mc_isunq == 0) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_itrie0.contains(x1) && mc_vtrie0.contains(x1)) {
                        auto &t_itrie1 = t_itrie0.at(x1);
                        auto &mc_vtrie1 = mc_vtrie0.at(x1);
                        for (const auto &mc_off : mc_vtrie1) {
                            auto x2 = mc_company_id[mc_off];
                            if (cn_trie0.contains(x2)) {
                                auto &cn_trie1 = cn_trie0.at(x2);
                                auto &t_off = t_itrie1;
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
        } else {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_keyword_id[mk_off];
                if (k_trie0.contains(x0)) {
                    auto &k_trie1 = k_trie0.at(x0);
                    auto x1 = mk_movie_id[mk_off];
                    if (t_itrie0.contains(x1) && mc_itrie0.contains(x1)) {
                        auto &t_itrie1 = t_itrie0.at(x1);
                        auto &mc_itrie1 = mc_itrie0.at(x1);
                        auto &mc_off = mc_itrie1;
                        auto x2 = mc_company_id[mc_off];
                        if (cn_trie0.contains(x2)) {
                            auto &cn_trie1 = cn_trie0.at(x2);
                            auto &t_off = t_itrie1;
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
        timer.StoreElapsedTime(1);

        auto interm0_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm0_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm0_isunq = build_trie(interm0_vtrie0, interm0_itrie0, interm0_offsets, interm0_col0);
        auto an_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto an_itrie0 = phmap::flat_hash_map<int, int>();
        auto an_isunq = build_trie(an_vtrie0, an_itrie0, an_offsets, an_person_id);
        auto n_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(n_trie0, n_offsets, n_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col2 = "zzzzzzzz";
        string mn_an_name = "zzzzzzzz";
        if (t_isunq == 0 && mc_isunq == 0 && interm0_isunq == 0 && an_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_vtrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_vtrie1 = an_vtrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        }
                        for (const auto &an_off : an_vtrie1) {
                            mn_an_name = min(mn_an_name, an_name[an_off]);
                        }
                    }
                }
            }
        } else if (t_isunq == 0 && mc_isunq == 0 && interm0_isunq == 0 && an_isunq == 1) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_itrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_itrie1 = an_itrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        }
                        auto &an_off = an_itrie1;
                        mn_an_name = min(mn_an_name, an_name[an_off]);
                    }
                }
            }
        } else if (t_isunq == 0 && mc_isunq == 0 && interm0_isunq == 1 && an_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_vtrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_vtrie1 = an_vtrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        for (const auto &an_off : an_vtrie1) {
                            mn_an_name = min(mn_an_name, an_name[an_off]);
                        }
                    }
                }
            }
        } else if (t_isunq == 0 && mc_isunq == 0 && interm0_isunq == 1 && an_isunq == 1) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_itrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_itrie1 = an_itrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        auto &an_off = an_itrie1;
                        mn_an_name = min(mn_an_name, an_name[an_off]);
                    }
                }
            }
        } else if (t_isunq == 0 && mc_isunq == 1 && interm0_isunq == 0 && an_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_vtrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_vtrie1 = an_vtrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        }
                        for (const auto &an_off : an_vtrie1) {
                            mn_an_name = min(mn_an_name, an_name[an_off]);
                        }
                    }
                }
            }
        } else if (t_isunq == 0 && mc_isunq == 1 && interm0_isunq == 0 && an_isunq == 1) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_itrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_itrie1 = an_itrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        }
                        auto &an_off = an_itrie1;
                        mn_an_name = min(mn_an_name, an_name[an_off]);
                    }
                }
            }
        } else if (t_isunq == 0 && mc_isunq == 1 && interm0_isunq == 1 && an_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_vtrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_vtrie1 = an_vtrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        for (const auto &an_off : an_vtrie1) {
                            mn_an_name = min(mn_an_name, an_name[an_off]);
                        }
                    }
                }
            }
        } else if (t_isunq == 0 && mc_isunq == 1 && interm0_isunq == 1 && an_isunq == 1) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_itrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_itrie1 = an_itrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        auto &an_off = an_itrie1;
                        mn_an_name = min(mn_an_name, an_name[an_off]);
                    }
                }
            }
        } else if (t_isunq == 1 && mc_isunq == 0 && interm0_isunq == 0 && an_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_vtrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_vtrie1 = an_vtrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        }
                        for (const auto &an_off : an_vtrie1) {
                            mn_an_name = min(mn_an_name, an_name[an_off]);
                        }
                    }
                }
            }
        } else if (t_isunq == 1 && mc_isunq == 0 && interm0_isunq == 0 && an_isunq == 1) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_itrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_itrie1 = an_itrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        }
                        auto &an_off = an_itrie1;
                        mn_an_name = min(mn_an_name, an_name[an_off]);
                    }
                }
            }
        } else if (t_isunq == 1 && mc_isunq == 0 && interm0_isunq == 1 && an_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_vtrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_vtrie1 = an_vtrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        for (const auto &an_off : an_vtrie1) {
                            mn_an_name = min(mn_an_name, an_name[an_off]);
                        }
                    }
                }
            }
        } else if (t_isunq == 1 && mc_isunq == 0 && interm0_isunq == 1 && an_isunq == 1) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_itrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_itrie1 = an_itrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        auto &an_off = an_itrie1;
                        mn_an_name = min(mn_an_name, an_name[an_off]);
                    }
                }
            }
        } else if (t_isunq == 1 && mc_isunq == 1 && interm0_isunq == 0 && an_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_vtrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_vtrie1 = an_vtrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        }
                        for (const auto &an_off : an_vtrie1) {
                            mn_an_name = min(mn_an_name, an_name[an_off]);
                        }
                    }
                }
            }
        } else if (t_isunq == 1 && mc_isunq == 1 && interm0_isunq == 0 && an_isunq == 1) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_itrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_itrie1 = an_itrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        for (const auto &interm0_off : interm0_vtrie1) {
                            mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        }
                        auto &an_off = an_itrie1;
                        mn_an_name = min(mn_an_name, an_name[an_off]);
                    }
                }
            }
        } else if (t_isunq == 1 && mc_isunq == 1 && interm0_isunq == 1 && an_isunq == 0) {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_vtrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_vtrie1 = an_vtrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        for (const auto &an_off : an_vtrie1) {
                            mn_an_name = min(mn_an_name, an_name[an_off]);
                        }
                    }
                }
            }
        } else {
            for (const auto &ci_off : ci_offsets) {
                auto x0 = ci_movie_id[ci_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto x1 = ci_person_id[ci_off];
                    if (an_itrie0.contains(x1) && n_trie0.contains(x1)) {
                        auto &an_itrie1 = an_itrie0.at(x1);
                        auto &n_trie1 = n_trie0.at(x1);
                        auto &interm0_off = interm0_itrie1;
                        mn_interm0_col2 = min(mn_interm0_col2, interm0_col2[interm0_off]);
                        auto &an_off = an_itrie1;
                        mn_an_name = min(mn_an_name, an_name[an_off]);
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (z == 0)
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
