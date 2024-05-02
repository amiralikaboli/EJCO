#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> a1_person_id;
vector<string> a1_name;

void load_a1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		a1_person_id.push_back(stoi(token));
		getline(ss, token, '|');
		a1_name.push_back(token);
	}
	in.close();
}

vector<int> an_person_id;
vector<string> an_name;

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
		getline(ss, token, '|');
		an_name.push_back(token);
	}
	in.close();
}

vector<int> an1_person_id;
vector<string> an1_name;

void load_an1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		an1_person_id.push_back(stoi(token));
		getline(ss, token, '|');
		an1_name.push_back(token);
	}
	in.close();
}

vector<int> at_movie_id;
vector<string> at_title;

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

vector<int> cc_movie_id;
vector<int> cc_subject_id;
vector<int> cc_status_id;

void load_cc(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		try { cc_movie_id.push_back(stoi(token)); } catch (...) { cc_movie_id.push_back(-1); }
		getline(ss, token, '|');
		cc_subject_id.push_back(stoi(token));
		getline(ss, token, '|');
		cc_status_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> cct1_id;

void load_cct1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cct1_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> cct2_id;

void load_cct2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cct2_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> chn_id;
vector<string> chn_name;

void load_chn(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		chn_id.push_back(stoi(token));
		getline(ss, token, '|');
		chn_name.push_back(token);
	}
	in.close();
}

vector<int> ci_person_id;
vector<int> ci_movie_id;
vector<int> ci_person_role_id;
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
		getline(ss, token, '|');
		ci_person_id.push_back(stoi(token));
		getline(ss, token, '|');
		ci_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		try { ci_person_role_id.push_back(stoi(token)); } catch (...) { ci_person_role_id.push_back(-1); }
		getline(ss, token, '|');
		getline(ss, token, '|');
		getline(ss, token, '|');
		ci_role_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> cn_id;
vector<string> cn_name;

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

vector<int> cn1_id;
vector<string> cn1_name;

void load_cn1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cn1_id.push_back(stoi(token));
		getline(ss, token, '|');
		cn1_name.push_back(token);
	}
	in.close();
}

vector<int> cn2_id;
vector<string> cn2_name;

void load_cn2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cn2_id.push_back(stoi(token));
		getline(ss, token, '|');
		cn2_name.push_back(token);
	}
	in.close();
}

vector<int> ct_id;

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

vector<int> it3_id;

void load_it3(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		it3_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> k_id;
vector<string> k_keyword;

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
		getline(ss, token, '|');
		k_keyword.push_back(token);
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
		getline(ss, token, '|');
		kt_kind.push_back(token);
	}
	in.close();
}

vector<int> kt1_id;

void load_kt1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		kt1_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> kt2_id;

void load_kt2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		kt2_id.push_back(stoi(token));
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

vector<int> mc1_movie_id;
vector<int> mc1_company_id;

void load_mc1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mc1_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc1_company_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> mc2_movie_id;
vector<int> mc2_company_id;

void load_mc2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mc2_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mc2_company_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> mi_movie_id;
vector<int> mi_info_type_id;
vector<string> mi_info;

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

vector<int> mi_idx_movie_id;
vector<int> mi_idx_info_type_id;
vector<string> mi_idx_info;

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

vector<int> mi_idx1_movie_id;
vector<int> mi_idx1_info_type_id;
vector<string> mi_idx1_info;

void load_mi_idx1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mi_idx1_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx1_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx1_info.push_back(token);
	}
	in.close();
}

vector<int> mi_idx2_movie_id;
vector<int> mi_idx2_info_type_id;
vector<string> mi_idx2_info;

void load_mi_idx2(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		getline(ss, token, '|');
		mi_idx2_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx2_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx2_info.push_back(token);
	}
	in.close();
}

vector<int> miidx_movie_id;
vector<int> miidx_info_type_id;
vector<string> miidx_info;

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

vector<int> n1_id;

void load_n1(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		n1_id.push_back(stoi(token));
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

vector<int> rt_id;

void load_rt(const string path) {
	ifstream in(path);
	if (!in)
		 throw path;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		rt_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> t_id;
vector<string> t_title;
vector<int> t_kind_id;
vector<int> t_production_year;

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
vector<int> t1_kind_id;

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
		getline(ss, token, '|');
		getline(ss, token, '|');
		t1_kind_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> t2_id;
vector<string> t2_title;
vector<int> t2_kind_id;

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
		getline(ss, token, '|');
		getline(ss, token, '|');
		t2_kind_id.push_back(stoi(token));
	}
	in.close();
}
