#include "StringChart.h"

void StringChart::initializeChart()
{
	size_t span;

	for(span = 1; span <= word_num_; span++)
		for(size_t i = 0; i < word_num_ - span + 1; i++)
		{
			int j = i + span;
			string temp = subString(source_, i, j);
			//temp += " "; //��trie���в���Ķ�����涼��һ��" "
			pair<TrieNode*, bool> chart_pair = trie_->searchPhrase(temp);
			if(chart_pair.second != false)//�ҵ���һ�����ܵĶ���
			{
				//��trieNode*ָ���list<record>���������ӽ���MaxHeap
				MaxHeap recordHeap;
				list<Record>::iterator iter;
				list<Record>& record = chart_pair.first->getRecordList();
				for(iter = record.begin(); iter != record.end(); iter++)
				{
					Drivation* dri_ptr = new Drivation(iter->getString(), feature_calculator_->getInitialFeatureScore(*iter));//ͨ��һ��TrieNode��������TrieNode�������һ���Ƶ�
					chart[i][j].addDrivation(dri_ptr);
				}
			}
		}
}
//�ֲڵĴ��룬��Ҫ����
void StringChart::runCKYDecode()
{
	initializeChart();
	size_t span = 2;
	for(; span <= word_num_ - 1; span++)
	{
		for(size_t begin = 0; begin < word_num_ - span + 1; begin++)
		{
			size_t end = begin + span;
			complete(begin, end);
		}
	}
	if(chart[0][word_num_ - 1].size() != 0)
	{
		cout << "���ŵĽ�������:" << endl;
		cout << chart[0][word_num_ - 1].getMax()->getTargetSeq() << endl;
		/*
		cout << "���ŵ�n-best�����(n=6): " << endl;
		for(int i = 0; i <= 6; i++)
		{
			//cout << i << ": " << chart[0][word_num_ - 1].getMax()->getTargetSeq() << endl;
		}*/
	}
	else
	{
		cout << "cky������ִ���!" << endl;
	}
}
//�ֲڵĴ���,���Ӷ�̫����,��Ҫ�Ż�
void StringChart::complete(int begin, int end)
{
	for(int split = begin + 1; split < end; split++)
	{
		if(chart[begin][split].size() == 0 || chart[split][end].size() == 0)
		{
			cout << "one of the separated chart has zero data" << endl;
		}
		else
		{
			//���������������ӵ�chart[begin][end]��
			int heap_size_left = chart[begin][split].size();
			int heap_size_right = chart[split][end].size();
			for(int left_p = 1; left_p <= heap_size_left; left_p++)
				for(int right_p = 1; right_p <= heap_size_right; right_p++)
				{
					Drivation* positive = feature_calculator_->getPositiveDrivation(chart[begin][split][left_p], chart[split][end][right_p]);
					Drivation* reverse = feature_calculator_->getReverseDrivation(chart[begin][split][left_p], chart[split][end][right_p]);
					chart[begin][end].addDrivation(positive);
					chart[begin][end].addDrivation(reverse);
				}
		}
	}
}
void StringChart::setSourceString(const string& source)
{
	//source_���ұ߼�һ��" "�����ڽ�ȡ�ַ���
	source_ = strip(source) + " ";
	word_num_ = countSpace(source_);
}
//�õ�Nbest
void StringChart::getNbest()
{
}
//Ӧ���ȰѴ�������string�ַ����������ߵĿո���ȥ��
StringChart::StringChart(StringTrie* s_t):word_num_(0),source_(""),trie_(s_t)
{
}
StringChart::StringChart(const string& source, StringTrie* trie):source_(strip(source)),trie_(trie)
{

	word_num_ = countSpace(source_);
}

StringChart::~StringChart(void)
{
	delete(trie_);
	delete(feature_calculator_);
}