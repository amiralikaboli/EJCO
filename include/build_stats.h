#include <iostream>
#include <unordered_set>
#include "parallel_hashmap/phmap.h"

using namespace std;

void calc_stats(vector<int> &attr0) {
	unordered_set<int> unq;
	for (int i = 0; i < attr0.size(); ++i) {
		unq.insert(attr0[i]);
	}

	long x0_cnt = 0;
	long x0_max = 0;
	x0_max = max(x0_max, long(unq.size()));
	x0_cnt += unq.size();

	cout << x0_cnt << " | ";
	cout << x0_max << endl;
}

void calc_stats(vector<int> &attr0, vector<int> &attr1) {
	phmap::flat_hash_map<int, unordered_set<int>> unq;
	for (int i = 0; i < attr0.size(); ++i) {
		unq[attr0[i]].insert(attr1[i]);
	}

	long x0_cnt = 0;
	long x1_cnt = 0;
	long x0_max = 0;
	long x1_max = 0;
	x0_max = max(x0_max, long(unq.size()));
	for (const auto &[x0, unq_x0]: unq) {
		++x0_cnt;
		x1_max = max(x1_max, long(unq_x0.size()));
		x1_cnt += unq_x0.size();
	}

	cout << x0_cnt << " " << ceil((x1_cnt + 0.0) / (x0_cnt + 0.0)) << " | ";
	cout << x0_max << " " << x1_max << endl;
}

void calc_stats(vector<int> &attr0, vector<int> &attr1, vector<int> &attr2) {
	phmap::flat_hash_map<int, phmap::flat_hash_map<int, unordered_set<int>>> unq;
	for (int i = 0; i < attr0.size(); ++i) {
		unq[attr0[i]][attr1[i]].insert(attr2[i]);
	}

	long x0_cnt = 0;
	long x1_cnt = 0;
	long x2_cnt = 0;
	long x0_max = 0;
	long x1_max = 0;
	long x2_max = 0;
	x0_max = max(x0_max, long(unq.size()));
	for (const auto &[x0, unq_x0]: unq) {
		++x0_cnt;
		x1_max = max(x1_max, long(unq_x0.size()));
		for (const auto &[x1, unq_x0_x1]: unq_x0) {
			++x1_cnt;
			x2_max = max(x2_max, long(unq_x0_x1.size()));
			x2_cnt += unq_x0_x1.size();
		}
	}

	cout << x0_cnt << " " << ceil((x1_cnt + 0.0) / (x0_cnt + 0.0)) << " " << ceil((x2_cnt + 0.0) / (x1_cnt + 0.0)) << " | ";
	cout << x0_max << " " << x1_max << " " << x2_max << endl;
}

void calc_stats(vector<int> &attr0, vector<int> &attr1, vector<int> &attr2, vector<int> &attr3) {
	phmap::flat_hash_map<int, phmap::flat_hash_map<int, phmap::flat_hash_map<int, unordered_set<int>>>> unq;
	for (int i = 0; i < attr0.size(); ++i) {
		unq[attr0[i]][attr1[i]][attr2[i]].insert(attr3[i]);
	}

	long x0_cnt = 0;
	long x1_cnt = 0;
	long x2_cnt = 0;
	long x3_cnt = 0;
	long x0_max = 0;
	long x1_max = 0;
	long x2_max = 0;
	long x3_max = 0;
	x0_max = max(x0_max, long(unq.size()));
	for (const auto &[x0, unq_x0]: unq) {
		++x0_cnt;
		x1_max = max(x1_max, long(unq_x0.size()));
		for (const auto &[x1, unq_x0_x1]: unq_x0) {
			++x1_cnt;
			x2_max = max(x2_max, long(unq_x0_x1.size()));
			for (const auto &[x2, unq_x0_x1_x2]: unq_x0_x1) {
				++x2_cnt;
				x3_max = max(x3_max, long(unq_x0_x1_x2.size()));
				x3_cnt += unq_x0_x1_x2.size();
			}
		}
	}

	cout << x0_cnt << " " << ceil((x1_cnt + 0.0) / (x0_cnt + 0.0)) << " " << ceil((x2_cnt + 0.0) / (x1_cnt + 0.0)) << " " << ceil((x3_cnt + 0.0) / (x2_cnt + 0.0)) << " | ";
	cout << x0_max << " " << x1_max << " " << x2_max << " " << x3_max << endl;
}