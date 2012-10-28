#ifndef _FEATURE_BASED_LOG_LINEAR_MODEL_H_
#define _FEATURE_BASED_LOG_LINEAR_MODEL_H_
#include "StringTrie.h"
#include "MaxHeap.h"
#include "FeatureScoreCal.h"
#include "LanguageModel.h"

class FeatureScoreCal
{
private:
	double feature_weight_[FEATURE_NUM];
	LanguageModel* lm_handle;
public:
	//����lm_handle
	void setLanguageModelHandle(LanguageModel* languageModel){lm_handle = languageModel;}
	//load language model
	void initialEnvironment();
	//ͨ����ǰTrien node��һ��record�˼�¼���õ��ϲ���Ĺ���һ���Ƶ���feature score��nά��������nά����Ȩ��
	double getInitialFeatureScore(Record& record);
	//��CYK�����У�ͨ�������Ƶ����õ�һ��������Ƶ�
	Drivation* getPositiveDrivation(const Drivation* left, const Drivation* right);
	//��CYK�����У�ͨ�������Ƶ����õ�һ��������Ƶ�
	Drivation* getReverseDrivation(const Drivation* left, const Drivation* right);
	double log2(double num){return log(num)/log((double)2);}
	FeatureScoreCal(void);
	~FeatureScoreCal(void);
	//�������ģ�͵ķ���
	double getLMScore(const string& s, int ngram_num);
	//������ķ���������CYK�ĺϲ������Ƶ��Ľ׶�,�������ط����������
	double getReorderingScor(const Drivation* left, const Drivation* right){return 0.0;}
};
#endif
