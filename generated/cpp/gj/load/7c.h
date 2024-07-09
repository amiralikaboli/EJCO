#include <fstream>
#include <iostream>
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

vector<int> ci_person_id;
vector<int> ci_movie_id;
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
        ci_offsets.push_back(cnt++);
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
        getline(ss, token, '|');
        ml_linked_movie_id.push_back(stoi(token));
        getline(ss, token, '|');
        ml_link_type_id.push_back(stoi(token));
        ml_offsets.push_back(cnt++);
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
vector<string> pi_info;
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
        getline(ss, token, '|');
        pi_info.push_back(token);
        pi_offsets.push_back(cnt++);
    }
    in.close();
}

vector<int> t_id;
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
        t_offsets.push_back(cnt++);
    }
    in.close();
}
