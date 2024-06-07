#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> cn1_id;
vector<string> cn1_name;
vector<int> cn1_offsets;
void load_cn1(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cn1_id.push_back(stoi(token));
		getline(ss, token, '|');
		cn1_name.push_back(token);
		cn1_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> cn2_id;
vector<string> cn2_name;
vector<int> cn2_offsets;
void load_cn2(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cn2_id.push_back(stoi(token));
		getline(ss, token, '|');
		cn2_name.push_back(token);
		cn2_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> it1_id;
vector<int> it1_offsets;
void load_it1(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		it1_id.push_back(stoi(token));
		it1_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> it2_id;
vector<int> it2_offsets;
void load_it2(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		it2_id.push_back(stoi(token));
		it2_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> kt1_id;
vector<int> kt1_offsets;
void load_kt1(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		kt1_id.push_back(stoi(token));
		kt1_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> kt2_id;
vector<int> kt2_offsets;
void load_kt2(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		kt2_id.push_back(stoi(token));
		kt2_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> lt_id;
vector<int> lt_offsets;
void load_lt(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		lt_id.push_back(stoi(token));
		lt_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> mc1_movie_id;
vector<int> mc1_company_id;
vector<int> mc1_offsets;
void load_mc1(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mc1_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc1_company_id.push_back(stoi(token));
		mc1_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> mc2_movie_id;
vector<int> mc2_company_id;
vector<int> mc2_offsets;
void load_mc2(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mc2_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc2_company_id.push_back(stoi(token));
		mc2_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> mi_idx1_movie_id;
vector<int> mi_idx1_info_type_id;
vector<string> mi_idx1_info;
vector<int> mi_idx1_offsets;
void load_mi_idx1(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mi_idx1_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx1_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx1_info.push_back(token);
		mi_idx1_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> mi_idx2_movie_id;
vector<int> mi_idx2_info_type_id;
vector<string> mi_idx2_info;
vector<int> mi_idx2_offsets;
void load_mi_idx2(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mi_idx2_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx2_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx2_info.push_back(token);
		mi_idx2_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> ml_movie_id;
vector<int> ml_linked_movie_id;
vector<int> ml_link_type_id;
vector<int> ml_offsets;
void load_ml(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		ml_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		ml_linked_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		ml_link_type_id.push_back(stoi(token));
		ml_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> t1_id;
vector<string> t1_title;
vector<int> t1_kind_id;
vector<int> t1_offsets;
void load_t1(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		t1_id.push_back(stoi(token));
		getline(ss, token, '|');
		t1_title.push_back(token);
		getline(ss, token, '|');
		getline(ss, token, '|');
		t1_kind_id.push_back(stoi(token));
		t1_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> t2_id;
vector<string> t2_title;
vector<int> t2_kind_id;
vector<int> t2_offsets;
void load_t2(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		t2_id.push_back(stoi(token));
		getline(ss, token, '|');
		t2_title.push_back(token);
		getline(ss, token, '|');
		getline(ss, token, '|');
		t2_kind_id.push_back(stoi(token));
		t2_offsets.push_back(cnt++);
	}
	in.close();
}
