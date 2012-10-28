#include "FeatureScoreCal.h"

void FeatureScoreCal::initialEnvironment()
{
	lm_handle->load_lang_model();
}
//调用LanguageModel里面的计算n_gram语言模型的方法;
double FeatureScoreCal::getLMScore(const string& s, int ngram_num)
{
	return 0.5;
	//return lm_handle->cal_ngram_probability(s);
}
double FeatureScoreCal::getInitialFeatureScore(Record& trie)
{
	double feature_score = 0.0;
	for(int i = 0; i < FEATURE_NUM; i++)
		feature_score += (feature_weight_[i]) * log(trie.getFeatures()[i]);

	//语言模型分数
	//feature_score += (lm_handle->lm_alpha) * loge(lm_handle->cal_ngram_probability(trie.getString()));
	feature_score += lm_handle->lm_alpha * log(0.5);
	//调序模型+

	return feature_score;
}
//Drivation的合并，下面两条的合并分数由3部分组成
Drivation* FeatureScoreCal::getPositiveDrivation(const Drivation* left, const Drivation* right)
{
	string s1 = left->getTargetSeq();
	string s2 = right->getTargetSeq();
	string s1_r, s2_l;
	int wordNumS1 = countSpace(s1);
	int wordNumS2 = countSpace(s2);

	if(wordNumS1 > LM_NGRAM_NUM)
		s1_r = lstrip(subString(s1, wordNumS1 - (LM_NGRAM_NUM - 1), wordNumS1));
		//s1_r = s1.substr(s1.length() - (LM_NGRAM_NUM - 1), s1.length());
	if(wordNumS2 > LM_NGRAM_NUM)
		s2_l = lstrip(subString_en(s2, 0, LM_NGRAM_NUM - 1));

	string positive_string = s1 + s2;
	double feature_score = left->getFeatureScore() + right->getFeatureScore();
	double lmA = getLMScore(s1_r+s2_l, LM_NGRAM_NUM) - getLMScore(s1_r, LM_NGRAM_NUM) - getLMScore(s2_l, LM_NGRAM_NUM);
	Drivation* new_d = new Drivation(positive_string, feature_score + lmA);
	return new_d;
}

Drivation* FeatureScoreCal::getReverseDrivation(const Drivation* left, const Drivation* right)
{
	string s1 = left->getTargetSeq();
	string s2 = right->getTargetSeq();

	string s1_l, s2_r;
	int wordNumS1 = countSpace(s1);
	int wordNumS2 = countSpace(s2);

	if(wordNumS1 > LM_NGRAM_NUM)
		s1_l = subString(s1, 0, LM_NGRAM_NUM - 1);
	if(wordNumS2 > LM_NGRAM_NUM)
		s2_r = subString(s2, wordNumS2 - (LM_NGRAM_NUM - 1), wordNumS2);
	
	string reverse_string = s2 + s1;
	double feature_score = left->getFeatureScore() + right->getFeatureScore();
	double lmA = getLMScore(s2_r+s1_l, LM_NGRAM_NUM) - getLMScore(s2_r, LM_NGRAM_NUM) - getLMScore(s1_l, LM_NGRAM_NUM);
	Drivation* new_d = new Drivation(reverse_string, feature_score + lmA);
	return new_d;
}
FeatureScoreCal::FeatureScoreCal(void)
{
	for(int i = 0; i < FEATURE_NUM; i++)
		feature_weight_[i] = 1.0;
}

FeatureScoreCal::~FeatureScoreCal(void)
{
}