#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

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
