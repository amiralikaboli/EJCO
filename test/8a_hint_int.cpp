#include "../generated/cpp/fj/load/8a.h"
#include "../include/build.h"
#include "../include/high_precision_timer.h"
#include "../include/small_vector.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
	HighPrecisionTimer timer;

	load_t("/Users/s2522996/Documents/free-join/data/imdb_csv/title.csv");
	load_an1("/Users/s2522996/Documents/free-join/data/imdb_csv/aka_name.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int iter = 0; iter < 1 + 10; ++iter) {
		timer.Reset();
		auto an1_trie0 = phmap::flat_hash_map<int, vector<int>>(an1_offsets.size());
		build_trie(an1_trie0, an1_person_id);
		timer.StoreElapsedTime(0);

		timer.Reset();
		auto t_trie0 = phmap::flat_hash_map<int, int>(t_offsets.size());
		build_trie(t_trie0, t_id);
		timer.StoreElapsedTime(1);

		cout << "*" << " " << flush;
	}
	cout << endl;

	auto tm0 = timer.GetMean(0);
	auto tm1 = timer.GetMean(1);
	cout << tm1 << " " << tm0 << endl;
}
