#include "load/32b.h"
#include "../../../include/build.h"
#include "../../../include/high_precision_timer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    HighPrecisionTimer timer;

    load_t1("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
    load_ml("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_link.csv");
    load_t2("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
    load_mk("/Users/s2522996/Documents/free-join/data/imdb_csv/movie_keyword.csv");
    load_lt("/Users/s2522996/Documents/free-join/data/imdb_csv/link_type.csv");
    load_k("/Users/s2522996/Documents/free-join/queries/preprocessed/join-order-benchmark/data/32b/k.csv");
    cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

    for (int z = 0; z < 1 + 5; ++z) {
        int cnt;
        timer.Reset();

        auto ml_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto ml_itrie0 = phmap::flat_hash_map<int, int>();
        auto ml_isunq = build_trie(ml_vtrie0, ml_itrie0, ml_offsets, ml_movie_id);
        auto t2_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto t2_itrie0 = phmap::flat_hash_map<int, int>();
        auto t2_isunq = build_trie(t2_vtrie0, t2_itrie0, t2_offsets, t2_id);
        timer.StoreElapsedTime(0);

        vector<int> interm0_col0;
        vector<string> interm0_col1;
        vector<int> interm0_col2;
        vector<int> interm0_col3;
        vector<string> interm0_col4;
        vector<int> interm0_offsets;
        cnt = 0;
        if (ml_isunq == 0 && t2_isunq == 0) {
            for (const auto &t1_off : t1_offsets) {
                auto x0 = t1_id[t1_off];
                if (ml_vtrie0.contains(x0)) {
                    auto &ml_vtrie1 = ml_vtrie0.at(x0);
                    for (const auto &ml_off : ml_vtrie1) {
                        auto x1 = ml_linked_movie_id[ml_off];
                        if (t2_vtrie0.contains(x1)) {
                            auto &t2_vtrie1 = t2_vtrie0.at(x1);
                            for (const auto &t2_off : t2_vtrie1) {
                                interm0_col0.push_back(t1_id[t1_off]);
                                interm0_col1.push_back(t1_title[t1_off]);
                                interm0_col2.push_back(ml_linked_movie_id[ml_off]);
                                interm0_col3.push_back(ml_link_type_id[ml_off]);
                                interm0_col4.push_back(t2_title[t2_off]);
                                interm0_offsets.push_back(cnt++);
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 0 && t2_isunq == 1) {
            for (const auto &t1_off : t1_offsets) {
                auto x0 = t1_id[t1_off];
                if (ml_vtrie0.contains(x0)) {
                    auto &ml_vtrie1 = ml_vtrie0.at(x0);
                    for (const auto &ml_off : ml_vtrie1) {
                        auto x1 = ml_linked_movie_id[ml_off];
                        if (t2_itrie0.contains(x1)) {
                            auto &t2_itrie1 = t2_itrie0.at(x1);
                            auto &t2_off = t2_itrie1;
                            interm0_col0.push_back(t1_id[t1_off]);
                            interm0_col1.push_back(t1_title[t1_off]);
                            interm0_col2.push_back(ml_linked_movie_id[ml_off]);
                            interm0_col3.push_back(ml_link_type_id[ml_off]);
                            interm0_col4.push_back(t2_title[t2_off]);
                            interm0_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else if (ml_isunq == 1 && t2_isunq == 0) {
            for (const auto &t1_off : t1_offsets) {
                auto x0 = t1_id[t1_off];
                if (ml_itrie0.contains(x0)) {
                    auto &ml_itrie1 = ml_itrie0.at(x0);
                    auto &ml_off = ml_itrie1;
                    auto x1 = ml_linked_movie_id[ml_off];
                    if (t2_vtrie0.contains(x1)) {
                        auto &t2_vtrie1 = t2_vtrie0.at(x1);
                        for (const auto &t2_off : t2_vtrie1) {
                            interm0_col0.push_back(t1_id[t1_off]);
                            interm0_col1.push_back(t1_title[t1_off]);
                            interm0_col2.push_back(ml_linked_movie_id[ml_off]);
                            interm0_col3.push_back(ml_link_type_id[ml_off]);
                            interm0_col4.push_back(t2_title[t2_off]);
                            interm0_offsets.push_back(cnt++);
                        }
                    }
                }
            }
        } else {
            for (const auto &t1_off : t1_offsets) {
                auto x0 = t1_id[t1_off];
                if (ml_itrie0.contains(x0)) {
                    auto &ml_itrie1 = ml_itrie0.at(x0);
                    auto &ml_off = ml_itrie1;
                    auto x1 = ml_linked_movie_id[ml_off];
                    if (t2_itrie0.contains(x1)) {
                        auto &t2_itrie1 = t2_itrie0.at(x1);
                        auto &t2_off = t2_itrie1;
                        interm0_col0.push_back(t1_id[t1_off]);
                        interm0_col1.push_back(t1_title[t1_off]);
                        interm0_col2.push_back(ml_linked_movie_id[ml_off]);
                        interm0_col3.push_back(ml_link_type_id[ml_off]);
                        interm0_col4.push_back(t2_title[t2_off]);
                        interm0_offsets.push_back(cnt++);
                    }
                }
            }
        }
        timer.StoreElapsedTime(1);

        auto interm0_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto interm0_itrie0 = phmap::flat_hash_map<int, int>();
        auto interm0_isunq = build_trie(interm0_vtrie0, interm0_itrie0, interm0_offsets, interm0_col0);
        auto lt_vtrie0 = phmap::flat_hash_map<int, vector<int>>();
        auto lt_itrie0 = phmap::flat_hash_map<int, int>();
        auto lt_isunq = build_trie(lt_vtrie0, lt_itrie0, lt_offsets, lt_id);
        auto k_trie0 = phmap::flat_hash_map<int, bool>();
        build_trie(k_trie0, k_offsets, k_id);
        timer.StoreElapsedTime(2);

        string mn_interm0_col1 = "zzzzzzzz";
        string mn_interm0_col4 = "zzzzzzzz";
        string mn_lt_link = "zzzzzzzz";
        if (ml_isunq == 0 && t2_isunq == 0 && interm0_isunq == 0 && lt_isunq == 0) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col3[interm0_off];
                        if (lt_vtrie0.contains(x1)) {
                            auto &lt_vtrie1 = lt_vtrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                                for (const auto &lt_off : lt_vtrie1) {
                                    mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                }
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 0 && t2_isunq == 0 && interm0_isunq == 0 && lt_isunq == 1) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col3[interm0_off];
                        if (lt_itrie0.contains(x1)) {
                            auto &lt_itrie1 = lt_itrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                                auto &lt_off = lt_itrie1;
                                mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 0 && t2_isunq == 0 && interm0_isunq == 1 && lt_isunq == 0) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col3[interm0_off];
                    if (lt_vtrie0.contains(x1)) {
                        auto &lt_vtrie1 = lt_vtrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                            for (const auto &lt_off : lt_vtrie1) {
                                mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 0 && t2_isunq == 0 && interm0_isunq == 1 && lt_isunq == 1) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col3[interm0_off];
                    if (lt_itrie0.contains(x1)) {
                        auto &lt_itrie1 = lt_itrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                            auto &lt_off = lt_itrie1;
                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                        }
                    }
                }
            }
        } else if (ml_isunq == 0 && t2_isunq == 1 && interm0_isunq == 0 && lt_isunq == 0) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col3[interm0_off];
                        if (lt_vtrie0.contains(x1)) {
                            auto &lt_vtrie1 = lt_vtrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                                for (const auto &lt_off : lt_vtrie1) {
                                    mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                }
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 0 && t2_isunq == 1 && interm0_isunq == 0 && lt_isunq == 1) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col3[interm0_off];
                        if (lt_itrie0.contains(x1)) {
                            auto &lt_itrie1 = lt_itrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                                auto &lt_off = lt_itrie1;
                                mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 0 && t2_isunq == 1 && interm0_isunq == 1 && lt_isunq == 0) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col3[interm0_off];
                    if (lt_vtrie0.contains(x1)) {
                        auto &lt_vtrie1 = lt_vtrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                            for (const auto &lt_off : lt_vtrie1) {
                                mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 0 && t2_isunq == 1 && interm0_isunq == 1 && lt_isunq == 1) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col3[interm0_off];
                    if (lt_itrie0.contains(x1)) {
                        auto &lt_itrie1 = lt_itrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                            auto &lt_off = lt_itrie1;
                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                        }
                    }
                }
            }
        } else if (ml_isunq == 1 && t2_isunq == 0 && interm0_isunq == 0 && lt_isunq == 0) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col3[interm0_off];
                        if (lt_vtrie0.contains(x1)) {
                            auto &lt_vtrie1 = lt_vtrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                                for (const auto &lt_off : lt_vtrie1) {
                                    mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                }
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 1 && t2_isunq == 0 && interm0_isunq == 0 && lt_isunq == 1) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col3[interm0_off];
                        if (lt_itrie0.contains(x1)) {
                            auto &lt_itrie1 = lt_itrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                                auto &lt_off = lt_itrie1;
                                mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 1 && t2_isunq == 0 && interm0_isunq == 1 && lt_isunq == 0) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col3[interm0_off];
                    if (lt_vtrie0.contains(x1)) {
                        auto &lt_vtrie1 = lt_vtrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                            for (const auto &lt_off : lt_vtrie1) {
                                mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 1 && t2_isunq == 0 && interm0_isunq == 1 && lt_isunq == 1) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col3[interm0_off];
                    if (lt_itrie0.contains(x1)) {
                        auto &lt_itrie1 = lt_itrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                            auto &lt_off = lt_itrie1;
                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                        }
                    }
                }
            }
        } else if (ml_isunq == 1 && t2_isunq == 1 && interm0_isunq == 0 && lt_isunq == 0) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col3[interm0_off];
                        if (lt_vtrie0.contains(x1)) {
                            auto &lt_vtrie1 = lt_vtrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                                for (const auto &lt_off : lt_vtrie1) {
                                    mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                                }
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 1 && t2_isunq == 1 && interm0_isunq == 0 && lt_isunq == 1) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_vtrie0.contains(x0)) {
                    auto &interm0_vtrie1 = interm0_vtrie0.at(x0);
                    for (const auto &interm0_off : interm0_vtrie1) {
                        auto x1 = interm0_col3[interm0_off];
                        if (lt_itrie0.contains(x1)) {
                            auto &lt_itrie1 = lt_itrie0.at(x1);
                            auto x2 = mk_keyword_id[mk_off];
                            if (k_trie0.contains(x2)) {
                                auto &k_trie1 = k_trie0.at(x2);
                                mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                                mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                                auto &lt_off = lt_itrie1;
                                mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                            }
                        }
                    }
                }
            }
        } else if (ml_isunq == 1 && t2_isunq == 1 && interm0_isunq == 1 && lt_isunq == 0) {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col3[interm0_off];
                    if (lt_vtrie0.contains(x1)) {
                        auto &lt_vtrie1 = lt_vtrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                            for (const auto &lt_off : lt_vtrie1) {
                                mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                            }
                        }
                    }
                }
            }
        } else {
            for (const auto &mk_off : mk_offsets) {
                auto x0 = mk_movie_id[mk_off];
                if (interm0_itrie0.contains(x0)) {
                    auto &interm0_itrie1 = interm0_itrie0.at(x0);
                    auto &interm0_off = interm0_itrie1;
                    auto x1 = interm0_col3[interm0_off];
                    if (lt_itrie0.contains(x1)) {
                        auto &lt_itrie1 = lt_itrie0.at(x1);
                        auto x2 = mk_keyword_id[mk_off];
                        if (k_trie0.contains(x2)) {
                            auto &k_trie1 = k_trie0.at(x2);
                            mn_interm0_col1 = min(mn_interm0_col1, interm0_col1[interm0_off]);
                            mn_interm0_col4 = min(mn_interm0_col4, interm0_col4[interm0_off]);
                            auto &lt_off = lt_itrie1;
                            mn_lt_link = min(mn_lt_link, lt_link[lt_off]);
                        }
                    }
                }
            }
        }
        timer.StoreElapsedTime(3);

        if (z == 0)
            cout << mn_interm0_col1 << " | " << mn_interm0_col4 << " | " << mn_lt_link << endl;
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
