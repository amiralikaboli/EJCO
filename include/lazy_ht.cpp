#include <iostream>
#include "parallel_hashmap/phmap.h"

using namespace std;

struct Node {
	vector<int> offsets;
	phmap::flat_hash_map<int, Node> ht;
	bool transformed;

	Node() : transformed(false) {}

	Node(vector<int> other) : offsets(other), transformed(false) {}

	void transform(vector<int> column) {
		for (const auto &off: offsets)
			ht[column[off]].offsets.push_back(off);
		transformed = true;
	}

	Node *lookup(int key, vector<int> column) {
		if (!transformed)
			transform(column);
		if (ht.contains(key))
			return &(ht.at(key));
		return nullptr;
	}

	vector<int>::iterator begin() { return offsets.begin(); }

	vector<int>::iterator end() { return offsets.end(); }
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

	Node* trie0 = new Node(off);
	auto trie1 = trie0->lookup(1, col);
	cout << trie1->offsets.size() << endl;
}