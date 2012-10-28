#ifndef _STRING_TRIE_H_
#define _STRING_TRIE_H_
#include "header.h"
typedef unsigned char CellByte;

//RecordNode可以是一个链表的一个节点，存储的是对应的target source和相应的频率
class Record //phrase节点的数据存储区域
{
private:
	string target_string_;
	double feature_arr_[FEATURE_NUM];
public:
	//target_string包含一个target_string和FEATURE_NUM个string类型的feature
	Record():target_string_("")
	{
		for(int i = 0; i < FEATURE_NUM; i++)
			feature_arr_[i] = 0.0;
	}
	//这个构造函数接受一个string, 格式为：target feature1 feature2 feature3 feature4 ... featureMaxNum
	Record(string record):target_string_(record)
	{
		istringstream is(record);
		is >> target_string_;
		for(int i = 0; i < FEATURE_NUM; i++)
			is >> feature_arr_[i];
	}
	string& getString(){return target_string_;}
	void setString(const string& target_string){target_string_ = target_string;}
	double* getFeatures(){return feature_arr_;}
};
//Record是一个链表结果的表示，内部存储了头结点和尾部节点，以及链表的长度
class RecordList
{
private:
	Record* head_, *tail_;
	unsigned int length_;
public:
	RecordList():head_(NULL),tail_(NULL){}
	void addRecordNode(Record* a);
	unsigned int getLength();
	Record* getHeader(){return head_;}
	Record* getTail(){return tail_;}
};

class TrieNode
{
private:
	CellByte  key_; //trie节点关键字
	bool is_a_phrase_; //标志位判断是否是个phrase
	int frequency_; //当前节点的经过频率
	int phrase_num_; //若当前节点标志一个phrase，此区域是phrase的个数
	TrieNode* branch_[MAX_BRANCH_NUM]; //孩子节点的分支
	//RecordList record_list_;
	list<Record> record_list_;
public:
	TrieNode(CellByte key):key_(key),is_a_phrase_(0),frequency_(0),phrase_num_(0)
	{
		for(int i = 0; i < MAX_BRANCH_NUM; i++)
			branch_[i] = NULL;
	}
	TrieNode():key_(-1),is_a_phrase_(0),frequency_(0),phrase_num_(0)
	{
		for(int i = 0; i < MAX_BRANCH_NUM; i++)
			branch_[i] = NULL;
	}
	void addFrequency(){frequency_++;}
	void addPhraseNum(){phrase_num_++;}
	void subPhraseNum(){phrase_num_--;}
	void subFrequency(){frequency_--;}
	bool isPhrase(){return is_a_phrase_;}
	void setPhrase(bool flag){is_a_phrase_ = flag;}
	bool addRecord(const string& target);//当is_phrase_是true时添加,string& target是译文+5个特征，用空格分开,向recordlist中添加记录，记录包含目标译文，以及特征值
	bool addRecord(const Record& record);//普通的添加一个record对象
	list<Record>& getRecordList(){return record_list_;}
	friend bool deleteNode(TrieNode* ptr, const string& s, size_t char_pos);
	friend class StringTrie;
};
class StringTrie
{
private:
	TrieNode* root_, *current_;
public:
	StringTrie();
	pair<TrieNode*, bool> searchPhrase(const string& phrase)const;
	list<Record>& getRecordList(const string& phrase)const;//得到recordlist
	bool insertPhrase(const string& source, const string& record_string);
	bool insertPhrase(const string& source, const Record& record);
	bool deletePhrase(const string& phrase);
	StringTrie::~StringTrie(void);
};
#endif
