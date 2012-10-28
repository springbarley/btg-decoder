#include "StringTrie.h"
#include "StringChart.h"
#include "PhraseTableProcess.h"
#include "LanguageModel.h"

int main(void)
{
	cout << "begin����" << endl;
	StringTrie string_trie;
	PhraseTableProcess ptp;
	ifstream in_file("phraseTable.txt", ios::in);
	if(!in_file.is_open())
	{
		cerr << "can't open file" << endl;
		return 0;
	}
	cout << "��ȡ�����Trie�ṹ..." << endl;
	string aLine;
	while(!in_file.eof())
	{
		getline(in_file, aLine);
		if(aLine.length() < 3)//��ȡ�����ַ���С��3ֹͣ
		{
			cout << "�ַ���С��3" << endl;
			break;
		}
		pair<string, Record> s_r = ptp.getTrieStructure(aLine);
		if(string_trie.insertPhrase(s_r.first.c_str(), s_r.second))
		{
			cout << "have insert: " << s_r.first << " successful" << endl;
		}
	}
	in_file.clear();
	in_file.close(); 
	cout << "������ȡ���..." << endl;
	LanguageModel* lm_model = new LanguageModel("giga.gz");
	FeatureScoreCal* feature_calculate_model = new FeatureScoreCal();
	feature_calculate_model->setLanguageModelHandle(lm_model);
	//feature_calculate_model->initialEnvironment();

	StringChart decoder(&string_trie);
	decoder.setFeatureHandel(feature_calculate_model);
	ifstream test_file("testFile.txt", ios::in);
	cout << test_file.failbit << endl;
	string test_line;
	while(!test_file.eof())
	{
		getline(test_file, test_line);
		decoder.setSourceString(test_line);
		clock_t start =clock();
		decoder.runCKYDecode();
		clock_t use_time = clock() - start;
		cout << "����: " << test_line << " ��ʱ��" << (double)use_time/CLOCKS_PER_SEC;
	}
	cout << "";
	return 0;
}