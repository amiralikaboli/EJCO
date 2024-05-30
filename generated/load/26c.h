#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> cc_movie_id;
vector<int> cc_subject_id;
vector<int> cc_status_id;

void load_cc(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		cc_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		cc_subject_id.push_back(stoi(token));
		getline(ss, token, '|');
		cc_status_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> cct1_id;

void load_cct1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cct1_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> cct2_id;

void load_cct2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cct2_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> chn_id;
vector<string> chn_name;

void load_chn(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		chn_id.push_back(stoi(token));
		getline(ss, token, '|');
		chn_name.push_back(token);
	}
	in.close();
}

vector<int> ci_person_id;
vector<int> ci_movie_id;
vector<int> ci_person_role_id;

void load_ci(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		ci_person_id.push_back(stoi(token));
		getline(ss, token, '|');
		ci_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		ci_person_role_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> it2_id;

void load_it2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		it2_id.push_back(stoi(token));
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

vector<int> kt_id;

void load_kt(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		kt_id.push_back(stoi(token));
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

vector<int> n_id;

void load_n(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		n_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> t_id;
vector<string> t_title;
vector<int> t_kind_id;

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
		getline(ss, token, '|');
		getline(ss, token, '|');
		t_kind_id.push_back(stoi(token));
	}
	in.close();
}
