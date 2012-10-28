#ifndef _PHRASE_TABLE_PROCESS_
#define _PHRASE_TABLE_PROCESS_
#include "StringTrie.h"

class PhraseTableProcess
{
public:
	//�������һ�еĽṹ�ǣ�ǰ�� ||| 15 march ||| 0.0357143 4.48857e-11 0.333333 5.09856e-05 2.718 ||| ||| 28 3
	//��ɣ�pair<string = ǰ��, record = ����>
	//pair<string, string> getTrieSturcture(const string& aLine);
	pair<string, Record> getTrieStructure(const string& aLine);
	PhraseTableProcess(void);
	~PhraseTableProcess(void);
};
#endif
