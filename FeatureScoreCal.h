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
	//设置lm_handle
	void setLanguageModelHandle(LanguageModel* languageModel){lm_handle = languageModel;}
	//load language model
	void initialEnvironment();
	//通过当前Trien node的一个record端记录，得到合并后的构成一个推导的feature score，n维特征乘以n维特征权重
	double getInitialFeatureScore(Record& record);
	//在CYK解码中，通过两个推导，得到一个正序的推导
	Drivation* getPositiveDrivation(const Drivation* left, const Drivation* right);
	//在CYK解码中，通过两个推导，得到一个逆序的推导
	Drivation* getReverseDrivation(const Drivation* left, const Drivation* right);
	double log2(double num){return log(num)/log((double)2);}
	FeatureScoreCal(void);
	~FeatureScoreCal(void);
	//获得语言模型的分数
	double getLMScore(const string& s, int ngram_num);
	//重排序的分数，用在CYK的合并两个推导的阶段,结合最大熵分类器的输出
	double getReorderingScor(const Drivation* left, const Drivation* right){return 0.0;}
};
#endif
