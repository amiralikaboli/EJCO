#include "../include/parallel_hashmap/phmap.h"
#include "../include/high_precision_timer.h"
#include "../include/build.h"
#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int iters;
bool verbose;

void ht_ht() {
	vector<pair<long, long>> movie_info_idx, title, movie_companies;
	load("../data/JOB/movie_info_idx_compact.csv", movie_info_idx);
	load("../data/JOB/title_compact.csv", title);
	load("../data/JOB/movie_companies_compact.csv", movie_companies);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t x = 0; x < iters; ++x) {
		auto R_tuples = movie_info_idx;
		auto S_tuples = title;
		auto T_tuples = movie_companies;

		trie_timer.Reset();
		auto R_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {a -> 1}}
		build_trie(R_tuples, R_trie);

		auto S_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie);

		auto T_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {c -> 1}}
		build_trie(T_tuples, T_trie);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		auto res = phmap::flat_hash_map<tuple<long, long, long, long>, bool>();
		for (auto &R_ent: R_trie) {
			auto x = R_ent.first;
			auto R_prime = R_ent.second;
			if (S_trie.contains(x) && T_trie.contains(x)) {
				auto S_prime = S_trie.at(x);
				auto T_prime = T_trie.at(x);
				for (auto &r_ent: R_prime) {
					auto a = r_ent.first;
					for (auto &s_ent: S_prime) {
						auto b = s_ent.first;
						for (auto &t_ent: T_prime) {
							auto c = t_ent.first;
							res[make_tuple(x, a, b, c)] = true;
						}
					}
				}
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "HtHt: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void ht_vec_hint() {
	vector<pair<long, long>> movie_info_idx, title, movie_companies;
	load("../data/JOB/movie_info_idx_compact.csv", movie_info_idx);
	load("../data/JOB/title_compact.csv", title);
	load("../data/JOB/movie_companies_compact.csv", movie_companies);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t x = 0; x < iters; ++x) {
		auto R_tuples = movie_info_idx;
		auto S_tuples = title;
		auto T_tuples = movie_companies;

		trie_timer.Reset();
		auto R_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {a -> 1}}
		build_trie(R_tuples, R_trie, 3);

		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie, 1);

		auto T_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {c -> 1}}
		build_trie(T_tuples, T_trie, 2);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		vector<tuple<long, long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &x = R_ent.first;
			auto &R_prime = R_ent.second;
			if (S_trie.contains(x) && T_trie.contains(x)) {
				auto &S_prime = S_trie.at(x);
				auto &T_prime = T_trie.at(x);
				for (auto &a: R_prime)
					for (auto &b: S_prime)
						for (auto &c: T_prime)
							res.push_back(make_tuple(x, a, b, c));
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "HtVecHint: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void ht_vec_idx() {
	pair<vector<long>, vector<long>> movie_info_idx, title, movie_companies;
	load("../data/JOB/movie_info_idx_compact.csv", movie_info_idx);
	load("../data/JOB/title_compact.csv", title);
	load("../data/JOB/movie_companies_compact.csv", movie_companies);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t x = 0; x < iters; ++x) {
		auto R_tuples = movie_info_idx;
		auto S_tuples = title;
		auto T_tuples = movie_companies;

		trie_timer.Reset();
		auto R_trie = phmap::flat_hash_map<long, pair<int, int>>();  // {x -> {a -> 1}}
		build_trie(R_tuples, R_trie);

		auto S_trie = phmap::flat_hash_map<long, pair<int, int>>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie);

		auto T_trie = phmap::flat_hash_map<long, pair<int, int>>();  // {x -> {c -> 1}}
		build_trie(T_tuples, T_trie);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		vector<tuple<long, long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &x = R_ent.first;
			auto &R_prime = R_ent.second;
			if (S_trie.contains(x) && T_trie.contains(x)) {
				auto &S_prime = S_trie.at(x);
				auto &T_prime = T_trie.at(x);
				for (int i = R_prime.first; i < R_prime.second; ++i) {
					auto &a = R_tuples.second[i];
					for (int j = S_prime.first; j < S_prime.second; ++j) {
						auto &b = S_tuples.second[j];
						for (int k = T_prime.first; k < T_prime.second; ++k) {
							auto &c = T_tuples.second[i];
							res.push_back(make_tuple(x, a, b, c));
						}
					}
				}
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "HtIdx: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void vec_vec_hint() {
	vector<pair<long, long>> movie_info_idx, title, movie_companies;
	load("../data/JOB/movie_info_idx_compact.csv", movie_info_idx);
	load("../data/JOB/title_compact.csv", title);
	load("../data/JOB/movie_companies_compact.csv", movie_companies);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t x = 0; x < iters; ++x) {
		auto R_tuples = movie_info_idx;
		auto S_tuples = title;
		auto T_tuples = movie_companies;

		trie_timer.Reset();
		vector<pair<long, vector<long>>> R_trie;  // {x -> {a -> 1}}
		build_trie(R_tuples, R_trie, 3);

		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie, 1);

		auto T_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {c -> 1}}
		build_trie(T_tuples, T_trie, 2);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		vector<tuple<long, long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &x = R_ent.first;
			auto &R_prime = R_ent.second;
			if (S_trie.contains(x) && T_trie.contains(x)) {
				auto &S_prime = S_trie.at(x);
				auto &T_prime = T_trie.at(x);
				for (auto &a: R_prime)
					for (auto &b: S_prime)
						for (auto &c: T_prime)
							res.push_back(make_tuple(x, a, b, c));
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "VecVecHint: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void vec_vec_idx() {
	pair<vector<long>, vector<long>> movie_info_idx, title, movie_companies;
	load("../data/JOB/movie_info_idx_compact.csv", movie_info_idx);
	load("../data/JOB/title_compact.csv", title);
	load("../data/JOB/movie_companies_compact.csv", movie_companies);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t x = 0; x < iters; ++x) {
		auto R_tuples = movie_info_idx;
		auto S_tuples = title;
		auto T_tuples = movie_companies;

		trie_timer.Reset();
		vector<tuple<long, int, int>> R_trie;  // {x -> {a -> 1}}
		build_trie(R_tuples, R_trie);

		auto S_trie = phmap::flat_hash_map<long, pair<int, int>>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie);

		auto T_trie = phmap::flat_hash_map<long, pair<int, int>>();  // {x -> {c -> 1}}
		build_trie(T_tuples, T_trie);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		vector<tuple<long, long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &x = get<0>(R_ent);
			auto &R_l = get<1>(R_ent);
			auto &R_r = get<2>(R_ent);
			if (S_trie.contains(x) && T_trie.contains(x)) {
				auto &S_prime = S_trie.at(x);
				auto &T_prime = T_trie.at(x);
				for (int i = R_l; i < R_r; ++i) {
					auto &a = R_tuples.second[i];
					for (int j = S_prime.first; j < S_prime.second; ++j) {
						auto &b = S_tuples.second[j];
						for (int k = T_prime.first; k < T_prime.second; ++k) {
							auto &c = T_tuples.second[k];
							res.push_back(make_tuple(x, a, b, c));
						}
					}
				}
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "VecVecIdx: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void vec_idx() {
	pair<vector<long>, vector<long>> movie_info_idx, title, movie_companies;
	load("../data/JOB/movie_info_idx_compact.csv", movie_info_idx);
	load("../data/JOB/title_compact.csv", title);
	load("../data/JOB/movie_companies_compact.csv", movie_companies);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t x = 0; x < iters; ++x) {
		auto R_tuples = movie_info_idx;
		auto S_tuples = title;
		auto T_tuples = movie_companies;

		trie_timer.Reset();
		vector<pair<long, long>> R_trie;  // {x -> {a -> 1}}
		build_trie(R_tuples, R_trie);

		auto S_trie = phmap::flat_hash_map<long, pair<int, int>>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie);

		auto T_trie = phmap::flat_hash_map<long, pair<int, int>>();  // {x -> {c -> 1}}
		build_trie(T_tuples, T_trie);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		vector<tuple<long, long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &x = R_ent.first;
			auto &a = R_ent.second;
			if (S_trie.contains(x) && T_trie.contains(x)) {
				auto &S_prime = S_trie.at(x);
				auto &T_prime = T_trie.at(x);
				for (int j = S_prime.first; j < S_prime.second; ++j) {
					auto &b = S_tuples.second[j];
					for (int k = T_prime.first; k < T_prime.second; ++k) {
						auto &c = T_tuples.second[k];
						res.push_back(make_tuple(x, a, b, c));
					}
				}
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "VecIdx: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void bs_vec_vec() {
	vector<pair<long, long>> movie_info_idx, title, movie_companies;
	load("../data/JOB/movie_info_idx_compact.csv", movie_info_idx);
	load("../data/JOB/title_compact.csv", title);
	load("../data/JOB/movie_companies_compact.csv", movie_companies);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t x = 0; x < iters; ++x) {
		auto R_tuples = movie_info_idx;
		auto S_tuples = title;
		auto T_tuples = movie_companies;

		trie_timer.Reset();
		vector<pair<long, vector<long>>> R_trie;  // {x -> {a -> 1}}
		build_trie(R_tuples, R_trie);

		auto S_trie = phmap::flat_hash_map<long, long>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie);

		sort(T_tuples.begin(), T_tuples.end(), cmp);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		int global_low = 0;
		vector<tuple<long, long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &x = R_ent.first;
			auto &R_prime = R_ent.second;
			if (S_trie.contains(x)) {
				auto &b = S_trie.at(x);
				auto [l_idx, r_idx] = binary_search(T_tuples, x, global_low, T_tuples.size() - 1, true);
				if (l_idx != -1) {
					global_low = l_idx;
					for (int k = l_idx; k <= r_idx; ++k) {
						auto &c = T_tuples[k].second;
						for (auto &a: R_prime)
							res.push_back(make_tuple(x, a, b, c));
					}
				}
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "BsVecVec: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void bs_vec_vec_idx() {
	pair<vector<long>, vector<long>> movie_info_idx;
	vector<pair<long, long>> title, movie_companies;
	load("../data/JOB/movie_info_idx_compact.csv", movie_info_idx);
	load("../data/JOB/title_compact.csv", title);
	load("../data/JOB/movie_companies_compact.csv", movie_companies);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t x = 0; x < iters; ++x) {
		auto R_tuples = movie_info_idx;
		auto S_tuples = title;
		auto T_tuples = movie_companies;

		trie_timer.Reset();
		vector<tuple<long, int, int>> R_trie;  // {x -> {a -> 1}}
		build_trie(R_tuples, R_trie);

		auto S_trie = phmap::flat_hash_map<long, long>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie);

		sort(T_tuples.begin(), T_tuples.end(), cmp);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		int global_low = 0;
		vector<tuple<long, long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &x = get<0>(R_ent);
			auto &R_l = get<1>(R_ent);
			auto &R_r = get<2>(R_ent);
			if (S_trie.contains(x)) {
				auto &b = S_trie.at(x);
				auto [l_idx, r_idx] = binary_search(T_tuples, x, global_low, T_tuples.size() - 1, true);
				if (l_idx != -1) {
					global_low = l_idx;
					for (int k = l_idx; k <= r_idx; ++k) {
						auto &c = T_tuples[k].second;
						for (int i = R_l; i < R_r; ++i) {
							auto &a = R_tuples.second[i];
							res.push_back(make_tuple(x, a, b, c));
						}
					}
				}
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "BsVecVecIdx: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void bs_vec() {
	vector<pair<long, long>> movie_info_idx, title, movie_companies;
	load("../data/JOB/movie_info_idx_compact.csv", movie_info_idx);
	load("../data/JOB/title_compact.csv", title);
	load("../data/JOB/movie_companies_compact.csv", movie_companies);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t x = 0; x < iters; ++x) {
		auto R_tuples = movie_info_idx;
		auto S_tuples = title;
		auto T_tuples = movie_companies;

		trie_timer.Reset();
		vector<pair<long, long>> R_trie;  // {x -> {a -> 1}}
		build_trie(R_tuples, R_trie);

		auto S_trie = phmap::flat_hash_map<long, long>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie);

		sort(T_tuples.begin(), T_tuples.end(), cmp);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		int global_low = 0;
		vector<tuple<long, long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &x = R_ent.first;
			auto &a = R_ent.second;
			if (S_trie.contains(x)) {
				auto &b = S_trie.at(x);
				auto [l_idx, r_idx] = binary_search(T_tuples, x, global_low, T_tuples.size() - 1, true);
				if (l_idx != -1) {
					global_low = l_idx;
					for (int k = l_idx; k <= r_idx; ++k) {
						auto &c = T_tuples[k].second;
						res.push_back(make_tuple(x, a, b, c));
					}
				}
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "BsVec: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

int main(int argc, char *argv[]) {
	iters = 10;
	verbose = false;


}
