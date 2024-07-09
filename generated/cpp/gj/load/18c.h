#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

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

vector<int> mi_movie_id;
vector<int> mi_info_type_id;
vector<string> mi_info;
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
        getline(ss, token, '|');
        mi_info.push_back(token);
        mi_offsets.push_back(cnt++);
    }
    in.close();
}

vector<int> mi_idx_movie_id;
vector<int> mi_idx_info_type_id;
vector<string> mi_idx_info;
vector<int> mi_idx_offsets;
void load_mi_idx(const string path) {
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
        mi_idx_movie_id.push_back(stoi(token));
        getline(ss, token, '|');
        mi_idx_info_type_id.push_back(stoi(token));
        getline(ss, token, '|');
        mi_idx_info.push_back(token);
        mi_idx_offsets.push_back(cnt++);
    }
    in.close();
}

vector<int> n_id;
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
        n_offsets.push_back(cnt++);
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
