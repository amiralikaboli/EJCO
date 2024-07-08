#include <iostream>
#include <vector>
#include "parallel_hashmap/phmap.h"

using namespace std;

void build_trie(vector<int> &off, vector<int> &attr0) {
	sort(off.begin(), off.end(), [&attr0](const auto &i, const auto &j) {
		if (attr0[i] < attr0[j]) return true;
		else return false;
	});
}

inline pair<int, int> find_range(vector<int> &off, vector<int> &attr0, const int &target, pair<int, int> range) {
	int first = -1;
	int last = -1;

	int left = range.first;
	int right = range.second;
	while (left <= right) {
		int mid = (left + right) >> 1;
		if (attr0[off[mid]] == target) {
			first = mid;
			right = mid - 1;
		} else if (attr0[off[mid]] < target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

	if (first == -1)
		return {-1, -1};

//	last = first - 1;
//	while (last + 1 <= range.second && attr0[off[last + 1]] == target) {
//		int pw = 1;
//		while (last + pw <= range.second && attr0[off[last + pw]] == target)
//			pw <<= 1;
//		last += pw >> 1;
//	}

	last = first;
	while (last <= range.second && attr0[off[last]] == target)
		++last;
	--last;

	return {first, last};
}