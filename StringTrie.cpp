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
	ptr->setPhrase(true);//������һ�����ӵı�ʶ
	ptr->addRecord(record_string);//����Ŀ���¼��
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
	ptr->setPhrase(true);//������һ�����ӵı�ʶ
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
	//���ҵ�ʱ�����Ƿ��ֵ�����ڵ�ı�־λ��һ�����ӣ��ͷ����ҵ���
	if(ptr->isPhrase())
	{
		return pair<TrieNode*, bool>(ptr, true);
	}
	//����־λ����true
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
	if(char_pos != s.length() - 1)//��û��ɾ�������stringһ���ڵ�
	{
		if(deleteNode(ptr->branch_[(unsigned char)s[char_pos]], s, char_pos + 1))
		{
		}
	}
	//ע�⵱�͹��string�����һ���ڵ��ǣ�ptrָ�������һ���ַ��ڵ����һ���ڵ��TrieNode
	cout << "now delete: " << s[char_pos] << " char" << endl;
	bool unnull_flag = false; 
	TrieNode* current_node_ptr = ptr->branch_[(unsigned char)s[char_pos]];//�˴�һ��Ҫת����unsigned char�ͣ�Ҫ��Ȼ���Ǹ�����
	for(size_t i = 0; i < MAX_BRANCH_NUM; i++)
	{
		if(current_node_ptr->branch_[i] != NULL)
			unnull_flag = true;
	}
	if(unnull_flag)//��ǰ�ڵ����滹���ӽڵ㣬��ôphrase_num_-1��frequency_ - 1���ǵû�Ҫ��isPhrase��Ϊ0
	{
		current_node_ptr->subFrequency();
		current_node_ptr->subPhraseNum();
		//�˴��ñ�־λΪfalseʱ��Ҫ��֤�����һ���ڵ���false����Ϊ���ܵݹ鷵��ʱ���ϲ�Ľڵ�Ҳ��false��
		if(current_node_ptr->isPhrase() && char_pos == s.length() - 1)
			current_node_ptr->setPhrase(false);
	}
	else//��ǰ�ڵ�һ���ڵ�����û�ӽڵ㣬��ôֱ��ɾ����ǰ�ڵ�,���Ұѱ�ɾ���ڵ�ĸ��ڵ�Ķ�Ӧָ������Ϊ0,���ҰѸ��ڵ���ļ�����һ���ǵû�Ҫ��isPhrase��Ϊ0��
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
