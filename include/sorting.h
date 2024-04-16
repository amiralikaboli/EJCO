#include "parallel_hashmap/phmap.h"
#include <iostream>
#include <tuple>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int partition(pair<vector<long>, vector<long>> &tuples, int low, int high) {
	int pivot_idx = (high + low) >> 1;
	long pivot = tuples.first[pivot_idx];
	swap(tuples.first[pivot_idx], tuples.first[high]);
	swap(tuples.second[pivot_idx], tuples.second[high]);
	int i = low - 1;

	for (int j = low; j <= high - 1; ++j) {
		if (tuples.first[j] < pivot) {
			++i;
			swap(tuples.first[i], tuples.first[j]);
			swap(tuples.second[i], tuples.second[j]);
		}
	}
	swap(tuples.first[i + 1], tuples.first[high]);
	swap(tuples.second[i + 1], tuples.second[high]);
	return i + 1;
}

void insertion_sort(std::pair<std::vector<long>, std::vector<long>>& tuples, int low, int high) {
	for (int i = low + 1; i <= high; i++) {
		long key1 = tuples.first[i];
		long key2 = tuples.second[i];
		int j = i - 1;
		while (j >= low && tuples.first[j] > key1) {
			tuples.first[j + 1] = tuples.first[j];
			tuples.second[j + 1] = tuples.second[j];
			j--;
		}
		tuples.first[j + 1] = key1;
		tuples.second[j + 1] = key2;
	}
}

void sort(pair<vector<long>, vector<long>> &tuples, int low, int high) {
	if (high - low < 50) {
		insertion_sort(tuples, low, high);
	} else {
		int pi = partition(tuples, low, high);
		sort(tuples, low, pi - 1);
		sort(tuples, pi + 1, high);
	}
}

int left_equal_binary_search(vector<pair<long, long>> &vec, const long key, int low, int high) {
	while (low < high) {
		int mid = (high + low) >> 1;
		if (mid == low) {
			if (vec[low].first == key)
				return low;
			else
				return high;
		}
		const long &vec_mid = vec[mid].first;
		if (key == vec_mid)
			high = mid;
		else
			low = mid;
	}
	return low;
}

int left_equal_binary_search(vector<long> &vec, const long key, int low, int high) {
	while (low < high) {
		int mid = (high + low) >> 1;
		if (mid == low) {
			if (vec[low] == key)
				return low;
			else
				return high;
		}
		const long &vec_mid = vec[mid];
		if (key == vec_mid)
			high = mid;
		else
			low = mid;
	}
	return low;
}

int right_equal_binary_search(vector<pair<long, long>> &vec, const long key, int low, int high) {
	while (low < high) {
		int mid = (high + low) >> 1;
		if (mid == low) {
			if (vec[high].first == key)
				return high;
			else
				return low;
		}
		const long &vec_mid = vec[mid].first;
		if (key == vec_mid)
			low = mid;
		else
			high = mid;
	}
	return low;
}

int right_equal_binary_search(vector<long> &vec, const long key, int low, int high) {
	while (low < high) {
		int mid = (high + low) >> 1;
		if (mid == low) {
			if (vec[high] == key)
				return high;
			else
				return low;
		}
		const long &vec_mid = vec[mid];
		if (key == vec_mid)
			low = mid;
		else
			high = mid;
	}
	return low;
}

pair<int, int> binary_search(vector<pair<long, long>> &vec, const long key, int low, int high, bool equal_mode = false) {  // -1 -> first & 1 -> last
	while (low <= high) {
		int mid = (high + low) >> 1;
		const long &vec_mid = vec[mid].first;
		if (vec_mid == key){
			if (equal_mode)
				return {left_equal_binary_search(vec, key, low, mid), right_equal_binary_search(vec, key, mid, high)};
			return {mid, mid};
		}
		else if (vec_mid > key)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return make_pair(-1, -1);
}

pair<int, int> binary_search(vector<long> &vec, const long key, int low, int high, bool equal_mode = false) {  // -1 -> first & 1 -> last
	while (low <= high) {
		int mid = (high + low) >> 1;
		const long &vec_mid = vec[mid];
		if (vec_mid == key){
			if (equal_mode)
				return {left_equal_binary_search(vec, key, low, mid), right_equal_binary_search(vec, key, mid, high)};
			return {mid, mid};
		}
		else if (vec_mid > key)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return make_pair(-1, -1);
}

bool cmp(const pair<long, long> &a, const pair<long, long> &b) {
	return a.first < b.first;
}
