#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> it_id;

void load_it(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		it_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> k_id;

void load_k(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		k_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> mi_idx_movie_id;
vector<int> mi_idx_info_type_id;
vector<string> mi_idx_info;

void load_mi_idx(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mi_idx_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx_info.push_back(token);
	}
	in.close();
}

vector<int> mk_movie_id;
vector<int> mk_keyword_id;

void load_mk(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mk_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mk_keyword_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> t_id;
vector<string> t_title;

void load_t(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		t_id.push_back(stoi(token));
		getline(ss, token, '|');
		t_title.push_back(token);
	}
	in.close();
}
