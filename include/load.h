#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> at_id;
vector<int> at_movie_id;
vector<string> at_title;
vector<string> at_imdb_index;
vector<int> at_kind_id;
vector<int> at_production_year;
vector<string> at_phonetic_code;
vector<int> at_episode_of_id;
vector<int> at_season_nr;
vector<int> at_episode_nr;
vector<string> at_note;
vector<string> at_md5sum;

void load_at(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		at_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		at_title.push_back(token);
	}
	in.close();
}

vector<int> cn_id;
vector<string> cn_name;
vector<string> cn_country_code;
vector<string> cn_imdb_id;
vector<string> cn_name_pcode_nf;
vector<string> cn_name_pcode_sf;
vector<string> cn_md5sum;

void load_cn(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cn_id.push_back(stoi(token));
		getline(ss, token, '|');
		cn_name.push_back(token);
	}
	in.close();
}

vector<int> ct_id;
vector<string> ct_kind;

void load_ct(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		ct_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> it_id;
vector<string> it_info;

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

vector<int> it1_id;
vector<string> it1_info;

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
vector<string> it2_info;

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

vector<int> k_id;
vector<string> k_keyword;
vector<string> k_phonetic_code;

void load_k(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		k_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> kt_id;
vector<string> kt_kind;

void load_kt(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		kt_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> lt_id;
vector<string> lt_link;

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
		getline(ss, token, '|');
		lt_link.push_back(token);
	}
	in.close();
}

vector<int> mc_id;
vector<int> mc_movie_id;
vector<int> mc_company_id;
vector<int> mc_company_type_id;
vector<string> mc_note;

void load_mc(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mc_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc_company_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc_company_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc_note.push_back(token);
	}
	in.close();
}

vector<int> mi_id;
vector<int> mi_movie_id;
vector<int> mi_info_type_id;
vector<string> mi_info;
vector<string> mi_note;

void load_mi(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mi_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_info.push_back(token);
	}
	in.close();
}

vector<int> mi_idx_id;
vector<int> mi_idx_movie_id;
vector<int> mi_idx_info_type_id;
vector<string> mi_idx_info;
vector<string> mi_idx_note;

void load_mi_idx(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mi_idx_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx_info.push_back(token);
	}
	in.close();
}

vector<int> miidx_id;
vector<int> miidx_movie_id;
vector<int> miidx_info_type_id;
vector<string> miidx_info;
vector<string> miidx_note;

void load_miidx(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		miidx_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		miidx_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		miidx_info.push_back(token);
	}
	in.close();
}

vector<int> mk_id;
vector<int> mk_movie_id;
vector<int> mk_keyword_id;

void load_mk(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mk_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mk_keyword_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> ml_id;
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

vector<int> t_id;
vector<string> t_title;
vector<string> t_imdb_index;
vector<int> t_kind_id;
vector<int> t_production_year;
vector<string> t_imdb_id;
vector<string> t_phonetic_code;
vector<int> t_episode_of_id;
vector<int> t_season_nr;
vector<int> t_episode_nr;
vector<string> t_series_years;
vector<string> t_md5sum;

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
		getline(ss, token, '|');
		t_title.push_back(token);
		getline(ss, token, '|');
		getline(ss, token, '|');
		t_kind_id.push_back(stoi(token));
		getline(ss, token, '|');
		try { t_production_year.push_back(stoi(token)); } catch (...) { t_production_year.push_back(-1); }
	}
	in.close();
}

vector<int> t1_id;
vector<string> t1_title;
vector<string> t1_imdb_index;
vector<int> t1_kind_id;
vector<int> t1_production_year;
vector<string> t1_imdb_id;
vector<string> t1_phonetic_code;
vector<int> t1_episode_of_id;
vector<int> t1_season_nr;
vector<int> t1_episode_nr;
vector<string> t1_series_years;
vector<string> t1_md5sum;

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
	}
	in.close();
}

vector<int> t2_id;
vector<string> t2_title;
vector<string> t2_imdb_index;
vector<int> t2_kind_id;
vector<int> t2_production_year;
vector<string> t2_imdb_id;
vector<string> t2_phonetic_code;
vector<int> t2_episode_of_id;
vector<int> t2_season_nr;
vector<int> t2_episode_nr;
vector<string> t2_series_years;
vector<string> t2_md5sum;

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
	}
	in.close();
}
