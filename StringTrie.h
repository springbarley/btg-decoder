#ifndef _STRING_TRIE_H_
#define _STRING_TRIE_H_
#include "header.h"
typedef unsigned char CellByte;

//RecordNode������һ�������һ���ڵ㣬�洢���Ƕ�Ӧ��target source����Ӧ��Ƶ��
class Record //phrase�ڵ�����ݴ洢����
{
private:
	string target_string_;
	double feature_arr_[FEATURE_NUM];
public:
	//target_string����һ��target_string��FEATURE_NUM��string���͵�feature
	Record():target_string_("")
	{
		for(int i = 0; i < FEATURE_NUM; i++)
			feature_arr_[i] = 0.0;
	}
	//������캯������һ��string, ��ʽΪ��target feature1 feature2 feature3 feature4 ... featureMaxNum
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
//Record��һ���������ı�ʾ���ڲ��洢��ͷ����β���ڵ㣬�Լ�����ĳ���
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
	CellByte  key_; //trie�ڵ�ؼ���
	bool is_a_phrase_; //��־λ�ж��Ƿ��Ǹ�phrase
	int frequency_; //��ǰ�ڵ�ľ���Ƶ��
	int phrase_num_; //����ǰ�ڵ��־һ��phrase����������phrase�ĸ���
	TrieNode* branch_[MAX_BRANCH_NUM]; //���ӽڵ�ķ�֧
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
	bool addRecord(const string& target);//��is_phrase_��trueʱ���,string& target������+5���������ÿո�ֿ�,��recordlist����Ӽ�¼����¼����Ŀ�����ģ��Լ�����ֵ
	bool addRecord(const Record& record);//��ͨ�����һ��record����
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
	list<Record>& getRecordList(const string& phrase)const;//�õ�recordlist
	bool insertPhrase(const string& source, const string& record_string);
	bool insertPhrase(const string& source, const Record& record);
	bool deletePhrase(const string& phrase);
	StringTrie::~StringTrie(void);
};
#endif
