#pragma once

#include <iostream>
#include "parallel_hashmap/phmap.h"

using namespace std;

struct Trie {
	vector<int> *offsets{nullptr};
	phmap::flat_hash_map<int, Trie *> *ht{nullptr};
	bool transformed{false};

	Trie() : offsets(new vector<int>()) {}

	Trie(vector<int> &other) : offsets(new vector<int>(other.begin(), other.end())) {}

	~Trie() {
		delete offsets;
		delete ht;
	}

	void emplace(int key, int off) {
		if (!ht->contains(key))
			ht->emplace(key, new Trie());
		ht->at(key)->offsets->push_back(off);
	}

	void transform(vector<int> column, int hint_size = 0) {
		if (hint_size)
			ht = new phmap::flat_hash_map<int, Trie *>(hint_size);
		else
			ht = new phmap::flat_hash_map<int, Trie *>();
		for (const auto &off: *offsets)
			this->emplace(column[off], off);
		transformed = true;
	}

	Trie *lookup(int key) {
		if (!transformed)
			throw "Trie not transformed";
		if (ht->contains(key))
			return ht->at(key);
		return nullptr;
	}

	int vec_size() { return offsets->size(); }

	int ht_size() { return ht->size(); }

	vector<int>::iterator vec_begin() { return offsets->begin(); }

	vector<int>::iterator vec_end() { return offsets->end(); }

	phmap::flat_hash_map<int, Trie *>::iterator ht_begin() { return ht->begin(); }

	phmap::flat_hash_map<int, Trie *>::iterator ht_end() { return ht->end(); }
};
