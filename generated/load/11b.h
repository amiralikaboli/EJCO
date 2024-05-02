#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> cn_id;
vector<string> cn_name;

void load_cn(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cn_id.push_back(stoi(token));
		getline(ss, token, '|');
		cn_name.push_back(token);
	}
	in.close();
}

vector<int> ct_id;

void load_ct(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		ct_id.push_back(stoi(token));
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

vector<int> lt_id;
vector<string> lt_link;

void load_lt(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		lt_id.push_back(stoi(token));
		getline(ss, token, '|');
		lt_link.push_back(token);
	}
	in.close();
}

vector<int> mc_movie_id;
vector<int> mc_company_id;
vector<int> mc_company_type_id;

void load_mc(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mc_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc_company_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc_company_type_id.push_back(stoi(token));
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

vector<int> ml_movie_id;
vector<int> ml_link_type_id;

void load_ml(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		ml_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		getline(ss, token, '|');
		ml_link_type_id.push_back(stoi(token));
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
