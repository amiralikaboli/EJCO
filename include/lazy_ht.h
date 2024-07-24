#pragma once

#include <iostream>
#include "parallel_hashmap/phmap.h"
#include "small_vector2.h"

using namespace std;

// Assumed the value type is always smallvec<int, N>
template<typename KEY_TYPE, size_t N = 4>
class LazyHT {
	phmap::flat_hash_map<KEY_TYPE, smallvec<int, N>> *ht_{nullptr};
	smallvec<int, N> *offs_{nullptr};
	vector<KEY_TYPE> *keys_{nullptr};
	bool transformed_{false};

public:
	LazyHT() { throw "Keys (and offs) not found"; }

	LazyHT(vector<KEY_TYPE> *keys) : keys_(keys) {}

	LazyHT(vector<KEY_TYPE> *keys, smallvec<int, N> *partial_offs) : keys_(keys), offs_(partial_offs) {}

	~LazyHT() { delete ht_; }

	size_t size() {
		if (!offs_)
			return keys_->size();
		return offs_->size();
	}

	void transform() {
		ht_ = new phmap::flat_hash_map<KEY_TYPE, smallvec<int, N>>(size());
		if (!offs_)
			for (int i = 0; i < keys_->size(); ++i)
				(*ht_)[(*keys_)[i]].push_back(i);
		else
			for (int i = 0; i < offs_->size(); ++i) {
				auto &off = (*offs_)[i];
				(*ht_)[(*keys_)[off]].push_back(off);
			}
		transformed_ = true;
	}

	// return type is pointer because of returning nullptr in case of not found
	smallvec<int, N> *lookup(KEY_TYPE key) {
		if (!transformed_)
			transform();
		if (ht_->contains(key))
			return &(ht_->at(key));
		return nullptr;
	}

	int operator[](int idx) {
		if (!offs_)
			return idx;
		return (*offs_)[idx];
	}
};
