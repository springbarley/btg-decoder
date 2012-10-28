#include "Util.h"


/************************************************************************/
/* 读取nist文件                                                         */
/************************************************************************/
void read_nist_file(const string& src_file, vector<string>& v_nist_sents)
{
	ifstream is(src_file.c_str());
	if(!is) {
		cerr << "Error, fail to read the source file from \"" << src_file << "\"." << endl;
		exit(1);
	}

	string line;
	vector<string> v_sent;
	while (getline(is, line)) {		
		if (line.find("<seg id") != string::npos ) { 
			v_nist_sents.push_back(line);
		}
	}
	is.close();
}


/************************************************************************/
/* 切分nist文件                                                         */
/************************************************************************/
vector<string> split_nist_file(const vector<string> &v_sents, const int& thread_num, int &pos)
{
	int size = (int)v_sents.size();
	static int chunk_size = size % thread_num == 0 ? size / thread_num : size / thread_num + 1;
	vector<string> chunk;
	for (int i = 0, j = pos; i < chunk_size && j < size; i++, j++){
		chunk.push_back(v_sents[j]);
	}
	pos += chunk_size;

	return chunk;
};


/************************************************************************/
/* 统计词数                                                             */
/************************************************************************/
int calc_word_num( const string& str )
{
	int word_num = 0;
	string word;	
	istringstream istr(str.c_str());
	while (istr >> word) { word_num++; }

	return word_num;
}


/************************************************************************/
/* 计算分数                                                             */
/************************************************************************/
//double calc_score(const vector<double>& v_feat, const vector<double>& v_lambda, const int& feat_num)
//{	
//	if ((int)v_feat.size() < feat_num || (int)v_lambda.size() < feat_num) {
//		cerr << "Calc_score Error." << endl;
//		cerr << "The size of v_feat is: " << v_feat.size() << endl;
//		cerr << "The size of v_lambda is: " << v_lambda.size() << endl;
//		cerr << "The feat_num is: " << feat_num << endl;
//		exit(1);
//	}
//
//	double score = 0;
//	for (int i=0; i<feat_num; i++) {
//		score += v_feat[i] * v_lambda[i];
//	}
//
//	return score;
//}


/************************************************************************/
/* string -> vector<string>                                             */
/************************************************************************/
vector<string> get_all_words(const string& phr)
{
	string word;
	vector<string> all;	
	istringstream istr( phr.c_str() );
	while (istr >> word) { all.push_back( word ); }

	return all;
}


/************************************************************************/
/* 获取开始第一个词                                                     */
/************************************************************************/
string get_first_word( const string& phr )
{
	string word;
	vector<string> all;	
	istringstream istr( phr.c_str() );
	while (istr >> word) { all.push_back( word ); }

	if (all.size() > 1) { return all[0]; }
	else { return phr; }
}


/************************************************************************/
/* 获取左边n个词                                                        */
/************************************************************************/
string get_first_n_words(const string& phra, const int& n)
{
	string word;
	vector<string> v_word;	
	istringstream istr( phra.c_str() );
	while (istr >> word) { v_word.push_back(word); }

	int i = 0;
	string w ="";
	for( ; i < n && i < int(v_word.size()); i++) {		
		w += v_word[i];
		w += " ";
	}

	// erase the last space
	if (w.size() > 1) { w.erase( w.size()-1,1 ); }

	return w;
}


/************************************************************************/
/* 获取最后第一个词                                                     */
/************************************************************************/
string get_last_word(const string& phr)
{
	string word;
	vector<string> all;	
	istringstream istr( phr.c_str() );
	while( istr >> word )
	{
		all.push_back( word );
	}

	if( all.size() <= 1 )
	{
		return phr;
	}
	else
	{
		return all[all.size()-1];
	}	
}


/************************************************************************/
/* 获取最后n个词                                                        */
/************************************************************************/
string get_last_n_words(const string& phr, const int& n)
{
	string word;
	vector<string> all;	
	istringstream istr( phr.c_str() );
	while (istr >> word) { all.push_back( word ); }

	int s = int(all.size());
	if (s <= n) { return phr; }
	else {
		int i;
		string w;
		for (i = s - n; i < s; i++) {
			string wi = all[i];
			w += wi;
			w += " ";
		}

		// erase the last space
		if (w.size() > 1) { w.erase( w.size()-1, 1 ); }

		return w;
	}
}


/************************************************************************/
/* 根据分隔符input_delimit切分输入串input_str                           */
/************************************************************************/
vector<string> split_str(const string& input_str, const string& input_delimit)
{
	vector<string> v_str;
	int len_sep=(int)input_delimit.length();

	size_t pre_pos=0;
	size_t pos=input_str.find(input_delimit, pre_pos);

	while(pos!=string::npos)
	{		
		int temp_len=pos-pre_pos;
		if(temp_len!=0)
		{
			v_str.push_back(input_str.substr(pre_pos, temp_len));
		}

		pre_pos=pos+len_sep;
		pos=input_str.find(input_delimit, pre_pos);
	}

	if((int)input_str.length()>pre_pos)
	{
		v_str.push_back(input_str.substr(pre_pos,(int)input_str.length()));
	}

	return v_str;
}


/************************************************************************/
/* double -> str                                                        */
/************************************************************************/
string dou2str(const double& d){
	stringstream ss;
	ss<<d;
	return ss.str();
}


/************************************************************************/
/* int -> str                                                           */
/************************************************************************/
string num2str(const int& i){
	stringstream ss;
	ss<<i;
	return ss.str();
}


/************************************************************************/
/* 去除""或者[]                                                         */
/************************************************************************/
string remove_sides(const string& str)
{
	if (str.size()<=2) {
		cerr << "Remove_side error, fail to remove sides, the str is: \"" << str << "\"" << endl;
		exit(1);
	}

	return str.substr(1, (int)str.size()-2);
}
/************************************************************************/
/*fry                                            */
/************************************************************************/
/************************************************************************/
/*//统计空格的个数                                                     */
/************************************************************************/
int countSpace(const string& source)
{
	int num = 0;
	for(size_t i = 0; i < source.length(); i++)
		if(source.at(i) == ' ')
			num++;
	return num;//source_的右端有空格
}
/************************************************************************/
/*//去除出string左右两端的空格                                          */
/************************************************************************/
string strip(const string& source)
{
	size_t begin = 0, end = 0;
	char last_char = '\0';
	for(size_t i = 0; i < source.length(); i++)
	{
		if(last_char == '\0' && source[i] != ' ')
		{
			begin = i; //标示从'\0'开始的第一个非空格
		}
		else if(last_char != ' ' && source[i] == ' ')
		{
			end = i; //标志第一个空格
		}
		else;
		last_char = source[i];
	}
	return source.substr(begin, end);
}
/***************************************************************************************/
/*通过空格来截取source，注意两个单词之间的空格个数为1个，最后一个单词后面还有一个空格,跳过空格 */
/***************************************************************************************/
string subString(const string& source,int start_space, int end_space)
{
	size_t pos = 0;
	int begin_flag = 0;
	string temp("");
	do
	{
		if(source.at(pos) == ' ')
		{	
			pos++;//跳过这个' ',得到的短语里面没有空格
			begin_flag++;
		}
		if(begin_flag >= start_space && begin_flag < end_space)
			temp += source.at(pos);
		else if(begin_flag >= end_space)
			break;
		else //若是begin_flag加不了了，也就是读不到空格了，那么一直读到最后一个'\n'到temp中去
			NULL;
	}while(pos++ < source.length());
	return temp;
}
/***************************************************************************************/
/*通过空格来截取source，注意两个单词之间的空格个数为1个，最后一个单词后面还有一个空格,不跳过空格 */
/***************************************************************************************/
string subString_en(const string& source,int start_space, int end_space)
{
	size_t pos = 0;
	int begin_flag = 0;
	string temp("");
	do
	{
		if(source.at(pos) == ' ')
		{	
			begin_flag++;
		}
		if(begin_flag >= start_space && begin_flag < end_space)
			temp += source.at(pos);
		else if(begin_flag >= end_space)
			break;
		else //若是begin_flag加不了了，也就是读不到空格了，那么一直读到最后一个'\n'到temp中去
			NULL;
	}while(pos++ < source.length());
	return temp;
}

string lstrip(const string& source)
{
	size_t begin = 0;
	char last_char = '\0';
	for(size_t i = 0; i < source.length(); i++)
	{
		if(last_char == '\0' && source[i] != ' ')
		{
			begin = i; //标示从'\0'开始的第一个非空格
			break;
		}
		else;
		last_char = source[i];
	}
	return source.substr(begin, source.length());
}

string rstrip(const string& source)
{
	size_t end = 0;
	char last_char = '\0';
	for(size_t i = 0; i < source.length(); i++)
	{
		if(last_char != ' ' && source[i] == ' ')
		{
			end = i; //标志第一个空格
		}
		else;
		last_char = source[i];
	}
	if(end < source.length())
		return source.substr(0, end);
	else
		return source;
}