#include <iostream>
#include <tuple>
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
	getline(in, line); // skip schema line
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
	getline(in, line); // skip schema line
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
		t_production_year.push_back(stoi(token));
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