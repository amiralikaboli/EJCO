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

void naive_query_benchmark() {
	auto title = load("../data/JOB/title_compact.csv");
	auto movie_companies = load("../data/JOB/movie_companies_compact.csv");
	auto movie_info_idx = load("../data/JOB/movie_info_idx_compact.csv");

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t i = 0; i < iters; ++i) {
		trie_timer.Reset();
		auto R_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {a -> 1}}
		auto S_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {b -> 1}}
		auto T_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {c -> 1}}

		build_trie(movie_info_idx, R_trie);
		build_trie(title, S_trie);
		build_trie(movie_companies, T_trie);
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
	}
	cout << "Naive: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void opt_query_benchmark() {
	auto title = load("../data/JOB/title_compact.csv");
	auto movie_companies = load("../data/JOB/movie_companies_compact.csv");
	auto movie_info_idx = load("../data/JOB/movie_info_idx_compact.csv");

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t i = 0; i < iters; ++i) {
		trie_timer.Reset();
		auto R_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {a -> 1}}
		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {b -> 1}}
		auto T_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {c -> 1}}

		build_trie(movie_info_idx, R_trie);
		build_trie(title, S_trie);
		build_trie(movie_companies, T_trie);
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
	}
	cout << "Opt: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void opt2_query_benchmark() {
	auto title = load("../data/JOB/title_compact.csv");
	auto movie_companies = load("../data/JOB/movie_companies_compact.csv");
	auto movie_info_idx = load("../data/JOB/movie_info_idx_compact.csv");

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (size_t i = 0; i < iters; ++i) {
		trie_timer.Reset();
		vector<pair<long, vector<long>>> R_trie;;  // {x -> {a -> 1}}
		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {b -> 1}}
		auto T_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {c -> 1}}

		build_trie(movie_info_idx, R_trie);
		build_trie(title, S_trie);
		build_trie(movie_companies, T_trie);
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
	}
	cout << "Opt2: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

int main(int argc, char *argv[]) {
	iters = 10;

	naive_query_benchmark();
	opt_query_benchmark();
	opt2_query_benchmark();
}
