#ifndef TRIE_TEST_
#define TRIE_TEST_
#include "StringTrie.h"
#include "StringChart.h"
#include "PhraseTableProcess.h"
#include "LanguageModel.h"

int trie_test(void)
{
	cout << "begin……" << endl;
	StringTrie string_trie;
	string_trie.insertPhrase("刘", "liu 1 2 3 4 5");
	string_trie.insertPhrase("刘强", "liuqiang 1 2 3 4 5");
	string_trie.insertPhrase("刘强东", "liuqiangdong 1 2 4 5 6");
	string_trie.insertPhrase("good boy", "好人啊 1 2 3 4 5");
	string_trie.insertPhrase("good boy", "好小伙 1 2 3 4 5");
	string_trie.insertPhrase("刘强东哥牛榜样啊", "liuqiangdongbangyang 1 2 3 4 5");

	if(string_trie.searchPhrase("good girls").second == true)
		cout << "have found the phrase: " << "good girl" << endl;
	else 
		cout << "can not find the phrase: " << "good girls" << endl;

	string_trie.deletePhrase(string("刘强"));
	string_trie.deletePhrase(string("刘"));
	string_trie.deletePhrase(string("good boys"));

	if(string_trie.searchPhrase("good boy").second == true)
	{
		cout << "have found the phrase: " << "good boy" << endl;
		list<Record>& record_list = string_trie.getRecordList("good boy");
		for(list<Record>::iterator iter = record_list.begin(); iter != record_list.end(); iter++)
		{
			cout << iter->getString() << endl;
			double* arry = iter->getFeatures();
			for(int i = 0; i< FEATURE_NUM; i++)
				cout << (double)arry[i] << endl;
		}
	}
	else 
		cout << "can not find the phrase: " << "good boy" << endl;
	return 0;
}
#endif