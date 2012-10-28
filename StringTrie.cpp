#include "StringTrie.h"

StringTrie::StringTrie()
{
	root_ = new TrieNode();
	this->current_ = root_;
}
bool StringTrie::insertPhrase(const string& s, const string& record_string)
{
	TrieNode* ptr = this->root_;
	size_t length = s.length();
	for(size_t pos = 0; pos < length; pos++)
	{
		unsigned char next_byte = (unsigned char)s[pos];
		if(ptr->branch_[next_byte] == NULL)
		{
			TrieNode* temp = new TrieNode(next_byte);
			ptr->branch_[next_byte] = temp;
		}
		ptr = ptr->branch_[next_byte];
		ptr->addFrequency();
	}
	ptr->addPhraseNum();
	ptr->setPhrase(true);//增加是一个句子的标识
	ptr->addRecord(record_string);//增加目标记录域
	return true;
}
bool StringTrie::insertPhrase(const string& s, const Record& record)
{
	TrieNode* ptr = this->root_;
	size_t length = s.length();
	for(size_t pos = 0; pos < length; pos++)
	{
		unsigned char next_byte = (unsigned char)s[pos];
		if(ptr->branch_[next_byte] == NULL)
		{
			TrieNode* temp = new TrieNode(next_byte);
			ptr->branch_[next_byte] = temp;
		}
		ptr = ptr->branch_[next_byte];
		ptr->addFrequency();
	}
	ptr->addPhraseNum();
	ptr->setPhrase(true);//增加是一个句子的标识
	ptr->addRecord(record);
	return true;
}
pair<TrieNode*, bool> StringTrie::searchPhrase(const string& s)const
{
	TrieNode* ptr = this->root_;
	size_t length = s.length();
	for(size_t pos = 0; pos < length; pos++)
	{
		unsigned char next_byte = (unsigned char)s[pos];
		if(ptr->branch_[next_byte] == NULL)
		{
			cout << "can't find string: " << s << endl;
			return pair<TrieNode*, bool>((TrieNode*)NULL, false);
		}
		else
		{
			ptr = ptr->branch_[next_byte];
		}
	}
	//查找的时候，若是发现到这个节点的标志位是一个句子，就返回找到了
	if(ptr->isPhrase())
	{
		return pair<TrieNode*, bool>(ptr, true);
	}
	//若标志位不是true
	else
	{
		return pair<TrieNode*, bool>((TrieNode*)NULL, false);
	}
}

list<Record>& StringTrie::getRecordList(const string& source)const
{
	pair<TrieNode*, bool> pair = searchPhrase(source);
	if(pair.second == true)
		return pair.first->getRecordList();
	else
	{
		cerr << "can't find the phrase: " << source << "in stringtire" << endl;
		return (list<Record>)NULL;
	}
}
bool deleteNode(TrieNode* ptr, const string& s, size_t char_pos)
{
	if(char_pos != s.length() - 1)//还没有删除到最后string一个节点
	{
		if(deleteNode(ptr->branch_[(unsigned char)s[char_pos]], s, char_pos + 1))
		{
		}
	}
	//注意当低轨道string的最后一个节点是，ptr指的是最后一个字符节点的上一个节点的TrieNode
	cout << "now delete: " << s[char_pos] << " char" << endl;
	bool unnull_flag = false; 
	TrieNode* current_node_ptr = ptr->branch_[(unsigned char)s[char_pos]];//此处一定要转换成unsigned char型，要不然就是负数了
	for(size_t i = 0; i < MAX_BRANCH_NUM; i++)
	{
		if(current_node_ptr->branch_[i] != NULL)
			unnull_flag = true;
	}
	if(unnull_flag)//当前节点下面还有子节点，那么phrase_num_-1，frequency_ - 1，记得还要把isPhrase置为0
	{
		current_node_ptr->subFrequency();
		current_node_ptr->subPhraseNum();
		//此处置标志位为false时，要保证是最后一个节点置false，因为可能递归返回时把上层的节点也置false了
		if(current_node_ptr->isPhrase() && char_pos == s.length() - 1)
			current_node_ptr->setPhrase(false);
	}
	else//当前节点一个节点下面没子节点，那么直接删除当前节点,并且把被删除节点的父节点的对应指针设置为0,并且把父节点域的记数减一，记得还要把isPhrase置为0。
	{
		delete(current_node_ptr);
		ptr->branch_[(unsigned char)s[char_pos]] = NULL;
		ptr->subFrequency();
		ptr->subPhraseNum();
	}
	return true;
}
bool StringTrie::deletePhrase(const string& s)
{
	if(searchPhrase(s).second == false)
	{
		cout << "haven't find the string: " << s << "can't delete it!" << endl;
		return false;
	}
	TrieNode* current_root = this->root_;
	if(deleteNode(current_root, s, 0))
		return true;
	else
	{
		cerr << "delete string: " << s << endl;
		return false;
	}
}

bool TrieNode::addRecord(const string& record)
{
	//assert(this->is_a_phrase_ == true);
	if(this->is_a_phrase_ != true)
	{
		cerr << "the trienode is not an leaf node" << endl;
		return false;
	}
	this->record_list_.push_back(record);
	return true;
}
bool TrieNode::addRecord(const Record& record)
{
	if(this->is_a_phrase_ != true)
	{
		cerr << "in insert record: the trie node is not an leaf node" << endl;
		return false;
	}
	this->record_list_.push_back(record);
	return true;
}
StringTrie::~StringTrie(void)
{
}
