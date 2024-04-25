#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> an_id;
vector<int> an_person_id;
vector<string> an_name;
vector<string> an_imdb_index;
vector<string> an_name_pcode_cf;
vector<string> an_name_pcode_nf;
vector<string> an_surname_pcode;
vector<string> an_md5sum;

void load_an(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		try { an_id.push_back(stoi(token)); } catch (...) { an_id.push_back(-1); }
		getline(ss, token, '|');
		try { an_person_id.push_back(stoi(token)); } catch (...) { an_person_id.push_back(-1); }
		getline(ss, token, '|');
		an_name.push_back(token);
		getline(ss, token, '|');
		an_imdb_index.push_back(token);
		getline(ss, token, '|');
		an_name_pcode_cf.push_back(token);
		getline(ss, token, '|');
		an_name_pcode_nf.push_back(token);
		getline(ss, token, '|');
		an_surname_pcode.push_back(token);
		getline(ss, token, '|');
		an_md5sum.push_back(token);
	}
	in.close();
}

vector<int> ci_id;
vector<int> ci_person_id;
vector<int> ci_movie_id;
vector<int> ci_person_role_id;
vector<string> ci_note;
vector<int> ci_nr_order;
vector<int> ci_role_id;

void load_ci(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		try { ci_id.push_back(stoi(token)); } catch (...) { ci_id.push_back(-1); }
		getline(ss, token, '|');
		try { ci_person_id.push_back(stoi(token)); } catch (...) { ci_person_id.push_back(-1); }
		getline(ss, token, '|');
		try { ci_movie_id.push_back(stoi(token)); } catch (...) { ci_movie_id.push_back(-1); }
		getline(ss, token, '|');
		try { ci_person_role_id.push_back(stoi(token)); } catch (...) { ci_person_role_id.push_back(-1); }
		getline(ss, token, '|');
		ci_note.push_back(token);
		getline(ss, token, '|');
		try { ci_nr_order.push_back(stoi(token)); } catch (...) { ci_nr_order.push_back(-1); }
		getline(ss, token, '|');
		try { ci_role_id.push_back(stoi(token)); } catch (...) { ci_role_id.push_back(-1); }
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
		try { cn_id.push_back(stoi(token)); } catch (...) { cn_id.push_back(-1); }
		getline(ss, token, '|');
		cn_name.push_back(token);
		getline(ss, token, '|');
		cn_country_code.push_back(token);
		getline(ss, token, '|');
		cn_imdb_id.push_back(token);
		getline(ss, token, '|');
		cn_name_pcode_nf.push_back(token);
		getline(ss, token, '|');
		cn_name_pcode_sf.push_back(token);
		getline(ss, token, '|');
		cn_md5sum.push_back(token);
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
		try { ct_id.push_back(stoi(token)); } catch (...) { ct_id.push_back(-1); }
		getline(ss, token, '|');
		ct_kind.push_back(token);
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
		try { it_id.push_back(stoi(token)); } catch (...) { it_id.push_back(-1); }
		getline(ss, token, '|');
		it_info.push_back(token);
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
		try { k_id.push_back(stoi(token)); } catch (...) { k_id.push_back(-1); }
		getline(ss, token, '|');
		k_keyword.push_back(token);
		getline(ss, token, '|');
		k_phonetic_code.push_back(token);
	}
	in.close();
}

vector<int> lt_id;
vector<string> lt_name;

void load_lt(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		try { lt_id.push_back(stoi(token)); } catch (...) { lt_id.push_back(-1); }
		getline(ss, token, '|');
		lt_name.push_back(token);
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
		try { mc_id.push_back(stoi(token)); } catch (...) { mc_id.push_back(-1); }
		getline(ss, token, '|');
		try { mc_movie_id.push_back(stoi(token)); } catch (...) { mc_movie_id.push_back(-1); }
		getline(ss, token, '|');
		try { mc_company_id.push_back(stoi(token)); } catch (...) { mc_company_id.push_back(-1); }
		getline(ss, token, '|');
		try { mc_company_type_id.push_back(stoi(token)); } catch (...) { mc_company_type_id.push_back(-1); }
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
		try { mi_id.push_back(stoi(token)); } catch (...) { mi_id.push_back(-1); }
		getline(ss, token, '|');
		try { mi_movie_id.push_back(stoi(token)); } catch (...) { mi_movie_id.push_back(-1); }
		getline(ss, token, '|');
		try { mi_info_type_id.push_back(stoi(token)); } catch (...) { mi_info_type_id.push_back(-1); }
		getline(ss, token, '|');
		mi_info.push_back(token);
		getline(ss, token, '|');
		mi_note.push_back(token);
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
		try { mi_idx_id.push_back(stoi(token)); } catch (...) { mi_idx_id.push_back(-1); }
		getline(ss, token, '|');
		try { mi_idx_movie_id.push_back(stoi(token)); } catch (...) { mi_idx_movie_id.push_back(-1); }
		getline(ss, token, '|');
		try { mi_idx_info_type_id.push_back(stoi(token)); } catch (...) { mi_idx_info_type_id.push_back(-1); }
		getline(ss, token, '|');
		mi_idx_info.push_back(token);
		getline(ss, token, '|');
		mi_idx_note.push_back(token);
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
		try { mk_id.push_back(stoi(token)); } catch (...) { mk_id.push_back(-1); }
		getline(ss, token, '|');
		try { mk_movie_id.push_back(stoi(token)); } catch (...) { mk_movie_id.push_back(-1); }
		getline(ss, token, '|');
		try { mk_keyword_id.push_back(stoi(token)); } catch (...) { mk_keyword_id.push_back(-1); }
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
		try { ml_id.push_back(stoi(token)); } catch (...) { ml_id.push_back(-1); }
		getline(ss, token, '|');
		try { ml_movie_id.push_back(stoi(token)); } catch (...) { ml_movie_id.push_back(-1); }
		getline(ss, token, '|');
		try { ml_linked_movie_id.push_back(stoi(token)); } catch (...) { ml_linked_movie_id.push_back(-1); }
		getline(ss, token, '|');
		try { ml_link_type_id.push_back(stoi(token)); } catch (...) { ml_link_type_id.push_back(-1); }
	}
	in.close();
}

vector<int> n_id;
vector<string> n_name;
vector<string> n_imdb_index;
vector<string> n_imdb_id;
vector<string> n_gender;
vector<string> n_name_pcode_cf;
vector<string> n_name_pcode_nf;
vector<string> n_surname_pcode;
vector<string> n_md5sum;

void load_n(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		try { n_id.push_back(stoi(token)); } catch (...) { n_id.push_back(-1); }
		getline(ss, token, '|');
		n_name.push_back(token);
		getline(ss, token, '|');
		n_imdb_index.push_back(token);
		getline(ss, token, '|');
		n_imdb_id.push_back(token);
		getline(ss, token, '|');
		n_gender.push_back(token);
		getline(ss, token, '|');
		n_name_pcode_cf.push_back(token);
		getline(ss, token, '|');
		n_name_pcode_nf.push_back(token);
		getline(ss, token, '|');
		n_surname_pcode.push_back(token);
		getline(ss, token, '|');
		n_md5sum.push_back(token);
	}
	in.close();
}

vector<int> pi_id;
vector<int> pi_person_id;
vector<int> pi_info_type_id;
vector<string> pi_info;
vector<string> pi_note;

void load_pi(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		try { pi_id.push_back(stoi(token)); } catch (...) { pi_id.push_back(-1); }
		getline(ss, token, '|');
		try { pi_person_id.push_back(stoi(token)); } catch (...) { pi_person_id.push_back(-1); }
		getline(ss, token, '|');
		try { pi_info_type_id.push_back(stoi(token)); } catch (...) { pi_info_type_id.push_back(-1); }
		getline(ss, token, '|');
		pi_info.push_back(token);
		getline(ss, token, '|');
		pi_note.push_back(token);
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
		try { t_id.push_back(stoi(token)); } catch (...) { t_id.push_back(-1); }
		getline(ss, token, '|');
		t_title.push_back(token);
		getline(ss, token, '|');
		t_imdb_index.push_back(token);
		getline(ss, token, '|');
		try { t_kind_id.push_back(stoi(token)); } catch (...) { t_kind_id.push_back(-1); }
		getline(ss, token, '|');
		try { t_production_year.push_back(stoi(token)); } catch (...) { t_production_year.push_back(-1); }
		getline(ss, token, '|');
		t_imdb_id.push_back(token);
		getline(ss, token, '|');
		t_phonetic_code.push_back(token);
		getline(ss, token, '|');
		try { t_episode_of_id.push_back(stoi(token)); } catch (...) { t_episode_of_id.push_back(-1); }
		getline(ss, token, '|');
		try { t_season_nr.push_back(stoi(token)); } catch (...) { t_season_nr.push_back(-1); }
		getline(ss, token, '|');
		try { t_episode_nr.push_back(stoi(token)); } catch (...) { t_episode_nr.push_back(-1); }
		getline(ss, token, '|');
		t_series_years.push_back(token);
		getline(ss, token, '|');
		t_md5sum.push_back(token);
	}
	in.close();
}
