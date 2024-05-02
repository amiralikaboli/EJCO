#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> an_person_id;

void load_an(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		an_person_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> ci_person_id;
vector<int> ci_movie_id;

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
	}
	in.close();
}

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
		getline(ss, token, '|');
		ml_linked_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		ml_link_type_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> n_id;
vector<string> n_name;

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
		getline(ss, token, '|');
		n_name.push_back(token);
	}
	in.close();
}

vector<int> pi_person_id;
vector<int> pi_info_type_id;
vector<string> pi_info;

void load_pi(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		pi_person_id.push_back(stoi(token));
		getline(ss, token, '|');
		pi_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		pi_info.push_back(token);
	}
	in.close();
}

vector<int> t_id;

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
	}
	in.close();
}
