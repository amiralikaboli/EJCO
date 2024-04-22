#include "../include/parallel_hashmap/phmap.h"
#include "../include/high_precision_timer.h"
#include "build.h"
#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int iters;
bool verbose;

void ht_vec() {
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
		build_trie(R_tuples, R_trie);

		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie);

		auto T_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {c -> 1}}
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
	cout << "HtVec: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void ht_vec_idx() {
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
					auto &a = R_tuples[i].second;
					for (int j = S_prime.first; j < S_prime.second; ++j) {
						auto &b = S_tuples[j].second;
						for (int k = T_prime.first; k < T_prime.second; ++k) {
							auto &c = T_tuples[k].second;
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
	cout << "HtVecIdx: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void vec_vec() {
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

		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie);

		auto T_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {c -> 1}}
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
	cout << "VecVec: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void vec_vec_idx() {
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
					auto &a = R_tuples[i].second;
					for (int j = S_prime.first; j < S_prime.second; ++j) {
						auto &b = S_tuples[j].second;
						for (int k = T_prime.first; k < T_prime.second; ++k) {
							auto &c = T_tuples[k].second;
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

void vec() {
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

		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {b -> 1}}
		build_trie(S_tuples, S_trie);

		auto T_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {c -> 1}}
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
				for (auto &b: S_prime)
					for (auto &c: T_prime)
						res.push_back(make_tuple(x, a, b, c));
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "Vec: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void vec_idx() {
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
					auto &b = S_tuples[j].second;
					for (int k = T_prime.first; k < T_prime.second; ++k) {
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
	cout << "VecIdx: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void pk() {
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

		auto T_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {c -> 1}}
		build_trie(T_tuples, T_trie);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		vector<tuple<long, long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &x = R_ent.first;
			auto &a = R_ent.second;
			if (S_trie.contains(x) && T_trie.contains(x)) {
				auto &b = S_trie.at(x);
				auto &T_prime = T_trie.at(x);
				for (auto &c: T_prime)
					res.push_back(make_tuple(x, a, b, c));
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "Pk: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void pk_idx() {
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

		auto T_trie = phmap::flat_hash_map<long, pair<int, int>>();  // {x -> {c -> 1}}
		build_trie(T_tuples, T_trie);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		vector<tuple<long, long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &x = R_ent.first;
			auto &a = R_ent.second;
			if (S_trie.contains(x) && T_trie.contains(x)) {
				auto &b = S_trie.at(x);
				auto &T_prime = T_trie.at(x);
				for (int k = T_prime.first; k < T_prime.second; ++k) {
					auto &c = T_tuples[k].second;
					res.push_back(make_tuple(x, a, b, c));
				}
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "PkIdx: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

int main(int argc, char *argv[]) {
	iters = 10;
	verbose = false;

	ht_vec();
	ht_vec_idx();
	vec_vec();
	vec_vec_idx();
	vec();
	vec_idx();
	pk();
	pk_idx();
}
