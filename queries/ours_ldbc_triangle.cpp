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

void htht_benchmark(string SF) {
	auto post_hastag_tag = load("../data/LDBC/" + SF + "/post_hastag_tag.csv", true, true);
	auto comment_hastag_tag = load("../data/LDBC/" + SF + "/comment_hastag_tag.csv", true, true);
	auto comment_replyof_post = load("../data/LDBC/" + SF + "/comment_replyof_post.csv", true, true);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (int i = 0; i < iters; ++i) {
		trie_timer.Reset();
		auto R_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {y -> 1}}
		auto S_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {y -> {z -> 1}}
		auto T_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {z -> 1}}

		build_trie(post_hastag_tag, R_trie);
		build_trie(comment_replyof_post, S_trie);
		build_trie(comment_hastag_tag, T_trie);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		auto res = phmap::flat_hash_map<tuple<long, long, long>, bool>();
		for (auto &R_ent: R_trie) {
			auto a = R_ent.first;
			auto R_prime = R_ent.second;
			if (T_trie.contains(a)) {
				auto T_prime = T_trie.at(a);
				for (auto &r_ent: R_prime) {
					auto b = r_ent.first;
					if (S_trie.contains(b)) {
						auto S_prime = S_trie.at(b);
						for (auto &s_ent: S_prime) {
							auto c = s_ent.first;
							if (T_prime.contains(c))
								res[make_tuple(a, b, c)] = true;
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

void htvec_benchmark(string SF) {
	auto post_hastag_tag = load("../data/LDBC/" + SF + "/post_hastag_tag.csv", true, true);
	auto comment_replyof_post = load("../data/LDBC/" + SF + "/comment_replyof_post.csv", true, true);
	auto comment_hastag_tag = load("../data/LDBC/" + SF + "/comment_hastag_tag.csv", true, true);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (int i = 0; i < iters; ++i) {
		trie_timer.Reset();
		auto R_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {y -> 1}}
		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {y -> {z -> 1}}
		auto T_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {z -> 1}}

		build_trie(post_hastag_tag, R_trie);
		build_trie(comment_replyof_post, S_trie);
		build_trie(comment_hastag_tag, T_trie);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		vector<tuple<long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &a = R_ent.first;
			auto &R_prime = R_ent.second;
			if (T_trie.contains(a)) {
				auto &T_prime = T_trie.at(a);
				for (auto &b: R_prime)
					if (S_trie.contains(b)) {
						auto &S_prime = S_trie.at(b);
						for (auto &c: S_prime)
							if (T_prime.contains(c))
								res.push_back(make_tuple(a, b, c));
					}
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "HtVec: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void vecvec_benchmark(string SF) {
	auto post_hastag_tag = load("../data/LDBC/" + SF + "/post_hastag_tag.csv", true, true);
	auto comment_replyof_post = load("../data/LDBC/" + SF + "/comment_replyof_post.csv", true, true);
	auto comment_hastag_tag = load("../data/LDBC/" + SF + "/comment_hastag_tag.csv", true, true);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (int i = 0; i < iters; ++i) {
		trie_timer.Reset();
		vector<pair<long, vector<long>>> R_trie;  // {x -> {y -> 1}}
		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {y -> {z -> 1}}
		auto T_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {z -> 1}}

		build_trie(post_hastag_tag, R_trie);
		build_trie(comment_replyof_post, S_trie);
		build_trie(comment_hastag_tag, T_trie);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		vector<tuple<long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &a = R_ent.first;
			auto &R_prime = R_ent.second;
			if (T_trie.contains(a)) {
				auto &T_prime = T_trie.at(a);
				for (auto &b: R_prime)
					if (S_trie.contains(b)) {
						auto &S_prime = S_trie.at(b);
						for (auto &c: S_prime)
							if (T_prime.contains(c))
								res.push_back(make_tuple(a, b, c));
					}
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "VecVec: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void vec_benchmark(string SF) {
	auto post_hastag_tag = load("../data/LDBC/" + SF + "/post_hastag_tag.csv", true, true);
	auto comment_replyof_post = load("../data/LDBC/" + SF + "/comment_replyof_post.csv", true, true);
	auto comment_hastag_tag = load("../data/LDBC/" + SF + "/comment_hastag_tag.csv", true, true);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	for (int i = 0; i < iters; ++i) {
		trie_timer.Reset();
		vector<pair<long, long>> R_trie;  // {x -> {y -> 1}}
		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {y -> {z -> 1}}
		auto T_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {z -> 1}}

		build_trie(post_hastag_tag, R_trie);
		build_trie(comment_replyof_post, S_trie);
		build_trie(comment_hastag_tag, T_trie);
		trie_timer.StoreElapsedTime(0);

		query_timer.Reset();
		vector<tuple<long, long, long>> res;
		for (auto &R_ent: R_trie) {
			auto &a = R_ent.first;
			auto &b = R_ent.second;
			if (S_trie.contains(b) && T_trie.contains(a)) {
				auto &S_prime = S_trie.at(b);
				auto &T_prime = T_trie.at(a);
				for (auto &c: S_prime)
					if (T_prime.contains(c))
						res.push_back(make_tuple(a, b, c));
			}
		}
		query_timer.StoreElapsedTime(0);

		if (verbose)
			cerr << res.size() << endl;
	}
	cout << "Vec: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

int main(int argc, char *argv[]) {
	string SF = argv[1];

	iters = 10;
	verbose = false;

	htht_benchmark(SF);
	htvec_benchmark(SF);
	vecvec_benchmark(SF);
	vec_benchmark(SF);
}
