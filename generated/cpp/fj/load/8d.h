#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> an1_person_id;
vector<string> an1_name;
vector<int> an1_offsets;
void load_an1(const string path) {
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
        an1_person_id.push_back(stoi(token));
        getline(ss, token, '|');
        an1_name.push_back(token);
        an1_offsets.push_back(cnt++);
    }
    in.close();
}

vector<int> ci_person_id;
vector<int> ci_movie_id;
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

vector<int> n1_id;
vector<int> n1_offsets;
void load_n1(const string path) {
    ifstream in(path);
    if (!in)
        throw path;
    string line;
    string token;
    int cnt = 0;
    while (getline(in, line)) {
        stringstream ss(line);
        getline(ss, token, '|');
        n1_id.push_back(stoi(token));
        n1_offsets.push_back(cnt++);
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
