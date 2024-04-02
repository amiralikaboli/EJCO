#include "../include/parallel_hashmap/phmap.h"
#include "../include/high_precision_timer.h"
#include "../include/build.h"
#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void naive_query_benchmark(string SF) {
	auto comment_replyof_post = load("../data/LDBC/" + SF + "/comment_replyof_post.csv", true);
	auto post_hastag_tag = load("../data/LDBC/" + SF + "/post_hastag_tag.csv", true);
	auto comment_hastag_tag = load("../data/LDBC/" + SF + "/comment_hastag_tag.csv", true);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	auto iters = 10;
	for (int i = 0; i < iters; ++i) {
		trie_timer.Reset();
		auto R_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {y -> 1}}
		auto S_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {y -> {z -> 1}}
		auto T_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {z -> 1}}

		build_trie(comment_replyof_post, R_trie);
		build_trie(post_hastag_tag, S_trie);
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
	}
	cout << "Naive: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void opt_query_benchmark(string SF) {
	auto comment_replyof_post = load("../data/LDBC/" + SF + "/comment_replyof_post.csv", true);
	auto post_hastag_tag = load("../data/LDBC/" + SF + "/post_hastag_tag.csv", true);
	auto comment_hastag_tag = load("../data/LDBC/" + SF + "/comment_hastag_tag.csv", true);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	auto iters = 10;
	for (int i = 0; i < iters; ++i) {
		trie_timer.Reset();
		auto R_trie = phmap::flat_hash_map<long, vector<long>>();  // {x -> {y -> 1}}
		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {y -> {z -> 1}}
		auto T_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {z -> 1}}

		build_trie(comment_replyof_post, R_trie);
		build_trie(post_hastag_tag, S_trie);
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
	}
	cout << "Opt: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

void opt2_query_benchmark(string SF) {
	auto comment_replyof_post = load("../data/LDBC/" + SF + "/comment_replyof_post.csv", true);
	auto post_hastag_tag = load("../data/LDBC/" + SF + "/post_hastag_tag.csv", true);
	auto comment_hastag_tag = load("../data/LDBC/" + SF + "/comment_hastag_tag.csv", true);

	auto trie_timer = HighPrecisionTimer();
	auto query_timer = HighPrecisionTimer();

	auto iters = 10;
	for (int i = 0; i < iters; ++i) {
		trie_timer.Reset();
		vector<pair<long, vector<long>>> R_trie;  // {x -> {y -> 1}}
		auto S_trie = phmap::flat_hash_map<long, vector<long>>();  // {y -> {z -> 1}}
		auto T_trie = phmap::flat_hash_map<long, phmap::flat_hash_map<long, bool>>();  // {x -> {z -> 1}}

		build_trie(comment_replyof_post, R_trie);
		build_trie(post_hastag_tag, S_trie);
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
	}
	cout << "Opt2: " << round(trie_timer.GetMean(0)) << " / " << round(query_timer.GetMean(0)) << " ms" << endl;
}

int main(int argc, char *argv[]) {
	string SF = argv[1];

	naive_query_benchmark(SF);
	opt_query_benchmark(SF);
	opt2_query_benchmark(SF);
}
