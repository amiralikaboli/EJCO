#include <iostream>
#include "../include/lazy_ht.h"

using namespace std;

int main() {
	srand(time(nullptr));

	const int SZ = 100;
	vector<int> off;
	vector<int> col;
	for (int i = 0; i < SZ; ++i) {
		off.push_back(i);
		col.push_back(rand() % 5 + 1);
	}

	Trie *trie0 = new Trie(off);
	trie0->transform(col);
	auto trie1 = trie0->lookup(1);
	for (auto o = trie1->vec_begin(); o != trie1->vec_end(); ++o)
		cout << *o << " ";
}