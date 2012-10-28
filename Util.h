#ifndef UTIL_H
#define UTIL_H

#include "header.h"
//#include "Constdef.h"
using namespace std;

//要求string的标点符号前也有空格
int countSpace(const string& source);

//去除出string左右两端的空格
string strip(const string& source);
string lstrip(const string& source);
string rstrip(const string& source);

//通过空格来截取source，注意两个单词之间的空格个数为1个，最后一个单词后面还有一个空格,返回的字符串之间没有空格，用于提取中文
string subString(const string& source,int start_space, int end_space);
//通过空格来截取source，注意两个单词之间的空格个数为1个，最后一个单词后面还有一个空格,返回的字符串之间有空格，用于提取英文
string subString_en(const string& source,int start_space, int end_space);
// 读取nist文件
void read_nist_file(const string& src_file, vector<string>& v_nist_sents);

// 文件切分
vector<string> split_nist_file(const vector<string> &sents, const int& thread_num, int &pos);

// 词个数
int calc_word_num(const string& str);

// 计算分数
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

// 得到首词
string get_first_word(const string& trans);

// 得到首n词
string get_first_n_words(const string& trans, const int& n);

// 得到尾词
string get_last_word(const string& trans); 

// 得到尾n词
string get_last_n_words(const string& trans, const int& n);

// 根据分隔符分割
vector<string> split_str(const string& input_str, const string& input_sep);

// 根据分隔符连接
/************************************************************************/
/* 根据分隔符连接                                                       */
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
/* 根据分隔符连接                                                       */
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
/* 去除开始结束空白符                                                   */
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


// 转化为string
string dou2str(const double& d);
//string dou2str(const double& d){
//	stringstream ss;
//	ss<<d;
//	return ss.str();
//};

string num2str(const int& i);

// 去除""或者[]
string remove_sides(const string& str);


#endif
