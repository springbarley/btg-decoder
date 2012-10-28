#ifndef UTIL_H
#define UTIL_H

#include "header.h"
//#include "Constdef.h"
using namespace std;

//Ҫ��string�ı�����ǰҲ�пո�
int countSpace(const string& source);

//ȥ����string�������˵Ŀո�
string strip(const string& source);
string lstrip(const string& source);
string rstrip(const string& source);

//ͨ���ո�����ȡsource��ע����������֮��Ŀո����Ϊ1�������һ�����ʺ��滹��һ���ո�,���ص��ַ���֮��û�пո�������ȡ����
string subString(const string& source,int start_space, int end_space);
//ͨ���ո�����ȡsource��ע����������֮��Ŀո����Ϊ1�������һ�����ʺ��滹��һ���ո�,���ص��ַ���֮���пո�������ȡӢ��
string subString_en(const string& source,int start_space, int end_space);
// ��ȡnist�ļ�
void read_nist_file(const string& src_file, vector<string>& v_nist_sents);

// �ļ��з�
vector<string> split_nist_file(const vector<string> &sents, const int& thread_num, int &pos);

// �ʸ���
int calc_word_num(const string& str);

// �������
inline double calc_score(const vector<double>& v_feat, const vector<double>& v_lambda, const int& feat_num = FEATURE_NUM)
{	
	if ((int)v_feat.size() < feat_num || (int)v_lambda.size() < feat_num) {
		cerr << "Calc_score Error." << endl;
		cerr << "The size of v_feat is: " << v_feat.size() << endl;
		cerr << "The size of v_lambda is: " << v_lambda.size() << endl;
		cerr << "The feat_num is: " << feat_num << endl;
		exit(1);
	}

	double score = 0;
	for (int i=0; i<feat_num; i++) {
		score += v_feat[i] * v_lambda[i];
	}

	return score;
};


// trans -> vector<string>
vector<string> get_all_words(const string& trans);

// �õ��״�
string get_first_word(const string& trans);

// �õ���n��
string get_first_n_words(const string& trans, const int& n);

// �õ�β��
string get_last_word(const string& trans); 

// �õ�βn��
string get_last_n_words(const string& trans, const int& n);

// ���ݷָ����ָ�
vector<string> split_str(const string& input_str, const string& input_sep);

// ���ݷָ�������
/************************************************************************/
/* ���ݷָ�������                                                       */
/************************************************************************/
inline string join_str(const vector<string>& input_v_word, const string& input_sep = " ")
{
	string str;
	for (size_t i = 0; i < input_v_word.size(); i++) {
		str += input_v_word[i];
		if (i != input_v_word.size() - 1) { 
			str += input_sep; 
		}
	}

	return str;
};


/************************************************************************/
/* ���ݷָ�������                                                       */
/************************************************************************/
inline string join_str(vector<string>::iterator begin_it, vector<string>::iterator end_it, const string& input_sep = " ")
{	
	string str;
	int word_num = end_it - begin_it;
	vector<string>::iterator it = begin_it;
	for (int i = 0; i < word_num; i++ ) {
		str += *it++;
		if (i != word_num - 1) { str += input_sep; }
	}

	return str;
};


/************************************************************************/
/* ȥ����ʼ�����հ׷�                                                   */
/************************************************************************/
inline string strip_str(const string& s, const string chs = " \t\n")
{
	if (s.empty()) {
		return s;
	}

	int i = 0;
	while (i < (int)s.size() && chs.find(s[i]) != string::npos) {
		++i;
	}

	int j = (int)s.size() - 1;
	while (j >= 0 && chs.find(s[j]) != string::npos) {
		--j;
	}

	++j;

	return i >= j ? "" : s.substr(i, j - i);
};


// ת��Ϊstring
string dou2str(const double& d);
//string dou2str(const double& d){
//	stringstream ss;
//	ss<<d;
//	return ss.str();
//};

string num2str(const int& i);

// ȥ��""����[]
string remove_sides(const string& str);


#endif
