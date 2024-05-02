#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> cn1_id;
vector<string> cn1_name;

void load_cn1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cn1_id.push_back(stoi(token));
		getline(ss, token, '|');
		cn1_name.push_back(token);
	}
	in.close();
}

vector<int> cn2_id;
vector<string> cn2_name;

void load_cn2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cn2_id.push_back(stoi(token));
		getline(ss, token, '|');
		cn2_name.push_back(token);
	}
	in.close();
}

vector<int> it1_id;

void load_it1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		it1_id.push_back(stoi(token));
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

vector<int> kt1_id;

void load_kt1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		kt1_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> kt2_id;

void load_kt2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		kt2_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> lt_id;

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
	}
	in.close();
}

vector<int> mc1_movie_id;
vector<int> mc1_company_id;

void load_mc1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mc1_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc1_company_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> mc2_movie_id;
vector<int> mc2_company_id;

void load_mc2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mc2_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc2_company_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> mi_idx1_movie_id;
vector<int> mi_idx1_info_type_id;
vector<string> mi_idx1_info;

void load_mi_idx1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mi_idx1_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx1_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx1_info.push_back(token);
	}
	in.close();
}

vector<int> mi_idx2_movie_id;
vector<int> mi_idx2_info_type_id;
vector<string> mi_idx2_info;

void load_mi_idx2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mi_idx2_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx2_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx2_info.push_back(token);
	}
	in.close();
}

vector<int> ml_movie_id;
vector<int> ml_linked_movie_id;
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
		ml_linked_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		ml_link_type_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> t1_id;
vector<string> t1_title;
vector<int> t1_kind_id;

void load_t1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		t1_id.push_back(stoi(token));
		getline(ss, token, '|');
		t1_title.push_back(token);
		getline(ss, token, '|');
		getline(ss, token, '|');
		t1_kind_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> t2_id;
vector<string> t2_title;
vector<int> t2_kind_id;

void load_t2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		t2_id.push_back(stoi(token));
		getline(ss, token, '|');
		t2_title.push_back(token);
		getline(ss, token, '|');
		getline(ss, token, '|');
		t2_kind_id.push_back(stoi(token));
	}
	in.close();
}
