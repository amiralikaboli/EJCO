#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> mk_id;
vector<int> mk_movie_id;
vector<int> mk_keyword_id;

void load_mk(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		mk_id.push_back(stoi(token));
		getline(ss, token, '|');
		mk_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mk_keyword_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> t_id;
vector <string> t_title;
vector <string> t_imdb_index;
vector<int> t_kind_id;
vector<int> t_production_year;
//vector<int> t_imdb_id;
vector <string> t_phonetic_code;
vector<int> t_episode_of_id;
vector<int> t_season_nr;
vector<int> t_episode_nr;
vector <string> t_series_years;
vector <string> t_md5sum;

void load_t(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		t_id.push_back(stoi(token));
		getline(ss, token, '|');
		t_title.push_back(token);
		getline(ss, token, '|');
		t_imdb_index.push_back(token);
		getline(ss, token, '|');
		t_kind_id.push_back(stoi(token));
		getline(ss, token, '|');
		try { t_production_year.push_back(stoi(token)); } catch (invalid_argument &e) { t_production_year.push_back(-1); }
		getline(ss, token, '|');
//		t_imdb_id.push_back(stoi(token));
		getline(ss, token, '|');
		t_phonetic_code.push_back(token);
		getline(ss, token, '|');
		try { t_episode_of_id.push_back(stoi(token)); } catch (invalid_argument &e) { t_episode_of_id.push_back(-1); }
		getline(ss, token, '|');
		try { t_season_nr.push_back(stoi(token)); } catch (invalid_argument &e) { t_season_nr.push_back(-1); }
		getline(ss, token, '|');
		try { t_episode_nr.push_back(stoi(token)); } catch (invalid_argument &e) { t_episode_nr.push_back(-1); }
		getline(ss, token, '|');
		t_series_years.push_back(token);
		getline(ss, token, '|');
		t_md5sum.push_back(token);
	}
	in.close();
}

vector<int> mi_id;
vector<int> mi_movie_id;
vector<int> mi_info_type_id;
vector <string> mi_info;
vector <string> mi_note;

void load_mi(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		mi_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_info.push_back(token);
		getline(ss, token, '|');
		mi_note.push_back(token);
	}
	in.close();
}

vector<int> k_id;
vector <string> k_keyword;
vector <string> k_phonetic_code;

void load_k(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		k_id.push_back(stoi(token));
		getline(ss, token, '|');
		k_keyword.push_back(token);
		getline(ss, token, '|');
		k_phonetic_code.push_back(token);
	}
	in.close();
}

vector<int> mc_id;
vector<int> mc_movie_id;
vector<int> mc_company_id;
vector<int> mc_company_type_id;
vector <string> mc_note;

void load_mc(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		mc_id.push_back(stoi(token));
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

vector<int> mi_idx_id;
vector<int> mi_idx_movie_id;
vector<int> mi_idx_info_type_id;
vector <string> mi_idx_info;
vector <string> mi_idx_note;

void load_mi_idx(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		mi_idx_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		mi_idx_info.push_back(token);
		getline(ss, token, '|');
		mi_idx_note.push_back(token);
	}
	in.close();
}

vector<int> it_id;
vector <string> it_info;

void load_it(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		it_id.push_back(stoi(token));
		getline(ss, token, '|');
		it_info.push_back(token);
	}
	in.close();
}

vector<int> ct_id;
vector <string> ct_kind;

void load_ct(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		ct_id.push_back(stoi(token));
		getline(ss, token, '|');
		ct_kind.push_back(token);
	}
	in.close();
}

vector<int> cn_id;
vector <string> cn_name;
vector <string> cn_country_code;
vector<int> cn_imdb_id;
vector <string> cn_namepcode_nf;
vector <string> cn_namepcode_sf;
vector <string> cn_md5sum;

void load_cn(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		cn_id.push_back(stoi(token));
		getline(ss, token, '|');
		cn_name.push_back(token);
		getline(ss, token, '|');
		cn_country_code.push_back(token);
		getline(ss, token, '|');
		try { cn_imdb_id.push_back(stoi(token)); } catch (invalid_argument &e) { cn_imdb_id.push_back(-1); }
		getline(ss, token, '|');
		cn_namepcode_nf.push_back(token);
		getline(ss, token, '|');
		cn_namepcode_sf.push_back(token);
		getline(ss, token, '|');
		cn_md5sum.push_back(token);
	}
	in.close();
}

vector<int> ci_id;
vector<int> ci_person_id;
vector<int> ci_movie_id;
vector<int> ci_person_role_id;
vector <string> ci_note;
vector<int> ci_nr_order;
vector<int> ci_role_id;

void load_ci(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		ci_id.push_back(stoi(token));
		getline(ss, token, '|');
		ci_person_id.push_back(stoi(token));
		getline(ss, token, '|');
		ci_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		try { ci_person_role_id.push_back(stoi(token)); } catch (invalid_argument &e) {
			ci_person_role_id.push_back(-1);
		}
		getline(ss, token, '|');
		ci_note.push_back(token);
		getline(ss, token, '|');
		try { ci_nr_order.push_back(stoi(token)); } catch (invalid_argument &e) { ci_nr_order.push_back(-1); }
		getline(ss, token, '|');
		ci_role_id.push_back(stoi(token));
	}
	in.close();
}

vector<int> n_id;
vector <string> n_name;
vector <string> n_imdb_index;
vector<int> n_imdb_id;
vector <string> n_gender;
vector <string> n_pcode_cf;
vector <string> n_pcode_nf;
vector <string> n_surname_pcode;
vector <string> n_md5sum;

void load_n(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		n_id.push_back(stoi(token));
		getline(ss, token, '|');
		n_name.push_back(token);
		getline(ss, token, '|');
		n_imdb_index.push_back(token);
		getline(ss, token, '|');
		try { n_imdb_id.push_back(stoi(token)); } catch (invalid_argument &e) { n_imdb_id.push_back(-1); }
		getline(ss, token, '|');
		n_gender.push_back(token);
		getline(ss, token, '|');
		n_pcode_cf.push_back(token);
		getline(ss, token, '|');
		n_pcode_nf.push_back(token);
		getline(ss, token, '|');
		n_surname_pcode.push_back(token);
		getline(ss, token, '|');
		n_md5sum.push_back(token);
	}
}

vector<int> an_id;
vector<int> an_person_id;
vector <string> an_name;
vector <string> an_imdb_index;
vector <string> an_name_pcode_cf;
vector <string> an_name_pcode_nf;
vector <string> an_surname_pcode;
vector <string> an_md5sum;

void load_an(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		an_id.push_back(stoi(token));
		getline(ss, token, '|');
		an_person_id.push_back(stoi(token));
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
}

vector<int> lt_id;
vector <string> lt_link;

void load_lt(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		lt_id.push_back(stoi(token));
		getline(ss, token, '|');
		lt_link.push_back(token);
	}
}

vector<int> ml_id;
vector<int> ml_movie_id;
vector<int> ml_linked_movie_id;
vector<int> ml_link_type_id;

void load_ml(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		ml_id.push_back(stoi(token));
		getline(ss, token, '|');
		ml_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		ml_linked_movie_id.push_back(stoi(token));
		getline(ss, token, '|');
		ml_link_type_id.push_back(stoi(token));
	}
}

vector<int> pi_id;
vector<int> pi_person_id;
vector<int> pi_info_type_id;
vector <string> pi_info;
vector <string> pi_note;

void load_pi(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		pi_id.push_back(stoi(token));
		getline(ss, token, '|');
		pi_person_id.push_back(stoi(token));
		getline(ss, token, '|');
		pi_info_type_id.push_back(stoi(token));
		getline(ss, token, '|');
		pi_info.push_back(token);
		getline(ss, token, '|');
		pi_note.push_back(token);
	}
}

vector<int> rt_id;
vector <string> rt_role;

void load_rt(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		rt_id.push_back(stoi(token));
		getline(ss, token, '|');
		rt_role.push_back(token);
	}
}

vector<int> chn_id;
vector <string> chn_name;
vector <string> chn_imdb_index;
vector<int> chn_imdb_id;
vector <string> chn_name_pcode_nf;
vector <string> chn_surname_pcode;
vector <string> chn_md5sum;

void load_chn(string path) {
	ifstream in(path);
	if (!in)
		cerr << "Cannot open the File : " << path << endl;
	string line;
	string token;
	while (getline(in, line)) {
		stringstream ss(line);
		getline(ss, token, '|');
		chn_id.push_back(stoi(token));
		getline(ss, token, '|');
		chn_name.push_back(token);
		getline(ss, token, '|');
		chn_imdb_index.push_back(token);
		getline(ss, token, '|');
		try { chn_imdb_id.push_back(stoi(token)); } catch (invalid_argument &e) { chn_imdb_id.push_back(-1); }
		getline(ss, token, '|');
		chn_name_pcode_nf.push_back(token);
		getline(ss, token, '|');
		chn_surname_pcode.push_back(token);
		getline(ss, token, '|');
		chn_md5sum.push_back(token);
	}
}
