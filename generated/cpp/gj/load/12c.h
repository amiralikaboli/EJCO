#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> cn_id;
vector<string> cn_name;
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
        getline(ss, token, '|');
        cn_name.push_back(token);
        cn_offsets.push_back(cnt++);
    }
    in.close();
}

vector<int> ct_id;
vector<int> ct_offsets;
void load_ct(const string path) {
    ifstream in(path);
    if (!in)
        throw path;
    string line;
    string token;
    int cnt = 0;
    while (getline(in, line)) {
        stringstream ss(line);
        getline(ss, token, '|');
        ct_id.push_back(stoi(token));
        ct_offsets.push_back(cnt++);
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

vector<int> mc_movie_id;
vector<int> mc_company_id;
vector<int> mc_company_type_id;
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
        getline(ss, token, '|');
        mc_company_type_id.push_back(stoi(token));
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
