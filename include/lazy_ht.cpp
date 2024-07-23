#include <iostream>
#include "parallel_hashmap/phmap.h"

using namespace std;

struct Node {
	vector<int> *offsets{nullptr};
	phmap::flat_hash_map<int, Node *> *ht{nullptr};
	bool transformed{false};

	Node() : offsets(new vector<int>()) {}

	Node(vector<int> &other) : offsets(new vector<int>(other.begin(), other.end())) {}

	~Node() {
		delete offsets;
		delete ht;
	}

	void emplace(int key, int off) {
		if (!ht->contains(key))
			ht->emplace(key, new Node());
		ht->at(key)->offsets->push_back(off);
	}

	void transform(vector<int> column) {
		ht = new phmap::flat_hash_map<int, Node *>(column.size());
		for (const auto &off: *offsets)
			this->emplace(column[off], off);
		transformed = true;
	}

	Node *lookup(int key, vector<int> column) {
		if (!transformed)
			this->transform(column);
		if (ht->contains(key))
			return ht->at(key);
		return nullptr;
	}

	int vec_size() { return offsets->size(); }

	int ht_size() { return ht->size(); }

	vector<int>::iterator vec_begin() { return offsets->begin(); }

	vector<int>::iterator vec_end() { return offsets->end(); }

	phmap::flat_hash_map<int, Node *>::iterator ht_begin() { return ht->begin(); }

	phmap::flat_hash_map<int, Node *>::iterator ht_end() { return ht->end(); }
};

int main() {
	srand(time(nullptr));

	const int SZ = 100;
	vector<int> off;
	vector<int> col;
	for (int i = 0; i < SZ; ++i) {
		off.push_back(i);
		col.push_back(rand() % 5 + 1);
	}

	Node *trie0 = new Node(off);
	auto trie1 = trie0->lookup(1, col);
	for (auto o = trie1->vec_begin(); o != trie1->vec_end(); ++o)
		cout << *o << " ";
}