#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> an_person_id;
vector<int> an_offsets;
void load_an(const string path) {
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
		an_person_id.push_back(stoi(token));
		an_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> cc_movie_id;
vector<int> cc_subject_id;
vector<int> cc_status_id;
vector<int> cc_offsets;
void load_cc(const string path) {
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
		cc_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		cc_subject_id.push_back(stoi(token));
		getline(ss, token, '|');
		cc_status_id.push_back(stoi(token));
		cc_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> cct1_id;
vector<int> cct1_offsets;
void load_cct1(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cct1_id.push_back(stoi(token));
		cct1_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> cct2_id;
vector<int> cct2_offsets;
void load_cct2(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cct2_id.push_back(stoi(token));
		cct2_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> chn_id;
vector<string> chn_name;
vector<int> chn_offsets;
void load_chn(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		chn_id.push_back(stoi(token));
		getline(ss, token, '|');
		chn_name.push_back(token);
		chn_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> ci_person_id;
vector<int> ci_movie_id;
vector<int> ci_person_role_id;
vector<int> ci_role_id;
vector<int> ci_offsets;
void load_ci(const string path) {
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
		ci_person_id.push_back(stoi(token));
		getline(ss, token, '|');
		ci_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		ci_person_role_id.push_back(stoi(token));
		getline(ss, token, '|');
		getline(ss, token, '|');
		getline(ss, token, '|');
		ci_role_id.push_back(stoi(token));
		ci_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> cn_id;
vector<int> cn_offsets;
void load_cn(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cn_id.push_back(stoi(token));
		cn_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> it_id;
vector<int> it_offsets;
void load_it(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		it_id.push_back(stoi(token));
		it_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> it3_id;
vector<int> it3_offsets;
void load_it3(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		it3_id.push_back(stoi(token));
		it3_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> k_id;
vector<int> k_offsets;
void load_k(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		k_id.push_back(stoi(token));
		k_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> mc_movie_id;
vector<int> mc_company_id;
vector<int> mc_offsets;
void load_mc(const string path) {
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
		mc_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc_company_id.push_back(stoi(token));
		mc_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> mi_movie_id;
vector<int> mi_info_type_id;
vector<int> mi_offsets;
void load_mi(const string path) {
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
		mi_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_info_type_id.push_back(stoi(token));
		mi_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> mk_movie_id;
vector<int> mk_keyword_id;
vector<int> mk_offsets;
void load_mk(const string path) {
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
		mk_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mk_keyword_id.push_back(stoi(token));
		mk_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> n_id;
vector<string> n_name;
vector<int> n_offsets;
void load_n(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		n_id.push_back(stoi(token));
		getline(ss, token, '|');
		n_name.push_back(token);
		n_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> pi_person_id;
vector<int> pi_info_type_id;
vector<int> pi_offsets;
void load_pi(const string path) {
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
		pi_person_id.push_back(stoi(token));
		getline(ss, token, '|');
		pi_info_type_id.push_back(stoi(token));
		pi_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> rt_id;
vector<int> rt_offsets;
void load_rt(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		rt_id.push_back(stoi(token));
		rt_offsets.push_back(cnt++);
	}
	in.close();
}

vector<int> t_id;
vector<string> t_title;
vector<int> t_offsets;
void load_t(const string path) {
	ifstream in(path);
	if (!in)
		throw path;
	string line;
	string token;
	int cnt = 0;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		t_id.push_back(stoi(token));
		getline(ss, token, '|');
		t_title.push_back(token);
		t_offsets.push_back(cnt++);
	}
	in.close();
}
