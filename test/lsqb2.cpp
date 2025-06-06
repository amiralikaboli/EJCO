#include "../include/build.h"
#include "../include/high_precision_timer.h"
#include "../include/small_vector2.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

vector<long> pkp_person1_id;
vector<long> pkp_person2_id;
vector<long> pkp_offsets;

void load_pkp(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	getline(in, line);
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		auto p1id = stol(token);
		getline(ss, token, '|');
		auto p2id = stol(token);
		pkp_person1_id.push_back(p1id);
		pkp_person2_id.push_back(p2id);
		pkp_person1_id.push_back(p2id);
		pkp_person2_id.push_back(p1id);
		pkp_offsets.push_back(cnt++);
		pkp_offsets.push_back(cnt++);
	}
	in.close();
}

vector<long> pst_id;
vector<long> pst_hascreator_person;
vector<long> pst_offsets;

void load_pst(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	getline(in, line);
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		pst_id.push_back(stol(token));
		getline(ss, token, '|');
		pst_hascreator_person.push_back(stol(token));
		pst_offsets.push_back(cnt++);
	}
	in.close();
}

vector<long> cmnt_hascreator_person;
vector<long> cmnt_replyof_post;
vector<long> cmnt_offsets;

void load_cmnt(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	getline(in, line);
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		cmnt_hascreator_person.push_back(stol(token));
		getline(ss, token, '|');
		getline(ss, token, '|');
		if (token == "")
			cmnt_replyof_post.push_back(-1);
		else
			cmnt_replyof_post.push_back(stol(token));
		cmnt_offsets.push_back(cnt++);
	}
	in.close();
}

int main() {
	HighPrecisionTimer timer;

	load_cmnt("/Users/s2522996/Documents/gj-vs-binary/data/lsqb1/Comment.csv");
	load_pst("/Users/s2522996/Documents/gj-vs-binary/data/lsqb1/Post.csv");
	load_pkp("/Users/s2522996/Documents/gj-vs-binary/data/lsqb1/Person_knows_Person.csv");
	cout << timer.GetElapsedTime() / 1000.0 << " s" << endl;

	for (int iter = 0; iter < 1 + 5; ++iter) {
		int cnt;
		timer.Reset();

		auto pst_trie0 = phmap::flat_hash_map<long, smallvecdict<int, 4>>(pst_offsets.size());
		for (int i = 0; i < pst_hascreator_person.size(); ++i)
			pst_trie0[pst_id[i]][i] += 1;
		auto pkp_trie0 = phmap::flat_hash_map<long, phmap::flat_hash_map<long, smallvecdict<int, 4>>>(pkp_offsets.size());
		for (int i = 0; i < pkp_person1_id.size(); ++i)
			pkp_trie0[pkp_person2_id[i]][pkp_person1_id[i]][i] += 1;
		timer.StoreElapsedTime(0);

		int ans = 0;
		for (const auto &cmnt_off: cmnt_offsets) {
			auto x0 = cmnt_replyof_post[cmnt_off];
			if (pst_trie0.contains(x0)) {
				auto &pst_trie1 = pst_trie0.at(x0);
				for (auto &pst_off: pst_trie1) {
					auto x1 = pst_hascreator_person[pst_off];
					if (pkp_trie0.contains(x1)) {
						auto &pkp_trie1 = pkp_trie0.at(x1);
						auto x2 = cmnt_hascreator_person[cmnt_off];
						if (pkp_trie1.contains(x2)) {
							auto &pkp_trie2 = pkp_trie1.at(x2);
							ans += pkp_trie2.size();
						}
					}
				}
			}
		}
		timer.StoreElapsedTime(1);

		if (iter == 0)
			cout << ans << endl;
		cout << "*" << " " << flush;
	}
	cout << endl;

	vector<double> tm{0};
	for (int i = 0; i < 2 * 1; ++i)
		tm.push_back(timer.GetMean(i));
	for (int i = 0; i < 2 * 1; i += 2) {
		cout << tm[i + 1] - tm[i] << " + ";
		cout << tm[i + 2] - tm[i + 1] << " = ";
		cout << tm[i + 2] - tm[i] << " ms" << endl;
	}
	cout << tm[2 * 1] << " ms" << endl;
}
