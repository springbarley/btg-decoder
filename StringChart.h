#ifndef _STRING_CHART_H_
#define _STRING_CHART_H_

#include "Util.h"
#include "StringTrie.h"
#include "MaxHeap.h"
#include "FeatureScoreCal.h"

//����sourceԴ������ʼ��chart,sourceӦ����һ��word�����У����ո�ָ�
//chartͼ����ĵ�Ԫ�ڰ���һ��ָ�룬ָ��һ������heap�����ڵ�Ԫ�ذ���chartԪ�ع涨��source��span������target���ģ��Լ����ĺ����������(���Ѱ���span���ĵ���������������)
class StringChart
{
private:
	unsigned int word_num_;
	string source_;
	MaxHeap chart[MAX_WORD_NUM][MAX_WORD_NUM];//�������飬����Ĭ�Ϲ��캯��
	StringTrie* trie_; //chart�õ��˶�����trie�ṹ��ǿ������ϵ
	FeatureScoreCal* feature_calculator_;
public:
	void setFeatureHandel(FeatureScoreCal* feature_calculator){feature_calculator_ = feature_calculator;}//�ڽ��н���֮ǰ����Ҫnewһ��feature_calculator�Ѿ����ֵ��StringChart
	void initializeChart();//����string��ʼ��stringchar(ö��string����ʼ�����еĿ��ܵĶ��ﵽstringchart��)
	void complete(int start, int end); //��string��start��end�Ĳ��ֽ����Ƶ��������ɵ��Ƶ�����chart[start,end]��MaxHeap��
	void runCKYDecode();//���н�CYK����
	void getNbest();
	StringChart(StringTrie* trie_);
	StringChart(const string& source, StringTrie* trie_);
	void setSourceString(const string& source);
	~StringChart(void);
};
#endif
