#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

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

vector<int> lt_id;
vector<string> lt_link;
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
        getline(ss, token, '|');
        lt_link.push_back(token);
        lt_offsets.push_back(cnt++);
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
        t1_offsets.push_back(cnt++);
    }
    in.close();
}

vector<int> t2_id;
vector<string> t2_title;
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
        t2_offsets.push_back(cnt++);
    }
    in.close();
}
