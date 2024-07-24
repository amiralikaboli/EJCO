#include <iostream>
#include "../include/lazy_ht.h"

using namespace std;

int main() {
	srand(time(nullptr));

	const int SZ = 300;
	vector<int> col0;
	vector<int> col1;
	for (int i = 0; i < SZ; ++i) {
		col0.push_back(rand() % 10 + 1);
		col1.push_back(rand() % 10 + 11);
	}
	cout << "col0: ";
	for (int i = 0; i < col0.size(); ++i)
		cout << col0[i] << " ";
	cout << endl;
	cout << "col1: ";
	for (int i = 0; i < col1.size(); ++i)
		cout << col1[i] << " ";
	cout << endl;

	cout << "offs: ";
	LazyHT<int> ht0(&col0);
	for (int i = 0; i < ht0.size(); ++i) {
		cout << ht0[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 100; ++i)
		cout << "#";
	cout << endl;

	auto svec0 = ht0.lookup(2);
	if (svec0) {
		cout << "Found key 2" << endl;
		LazyHT ht1(&col1, svec0);
		for (int i = 0; i < ht1.size(); ++i) {
			cout << ht1[i] << " ";
		}
		cout << endl;
		auto svec1 = ht1.lookup(111);
		if (svec1) {
			cout << "Found key 111" << endl;
			auto offs = *svec1;
			for (auto off: offs)
				cout << off << " ";
			cout << endl;
		} else {
			cout << "Key 111 not found" << endl;

		}
	}
	for (int i = 0; i < 100; ++i)
		cout << "#";
	cout << endl;

	svec0 = ht0.lookup(3);
	if (svec0) {
		cout << "Found key 3" << endl;
		LazyHT ht1(&col1, svec0);
		for (int i = 0; i < ht1.size(); ++i) {
			cout << ht1[i] << " ";
		}
		cout << endl;
		auto svec1 = ht1.lookup(17);
		if (svec1) {
			cout << "Found key 17" << endl;
			auto offs = *svec1;
			for (auto off: offs)
				cout << off << " ";
			cout << endl;
		} else {
			cout << "Key 17 not found" << endl;
		}
	}
}