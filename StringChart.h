#ifndef _STRING_CHART_H_
#define _STRING_CHART_H_

#include "Util.h"
#include "StringTrie.h"
#include "MaxHeap.h"
#include "FeatureScoreCal.h"

//根据source源端来初始化chart,source应该是一个word的序列，按空格分隔
//chart图里面的单元内包含一个指针，指向一个最大堆heap，堆内的元素包含chart元素规定的source端span的所有target译文，以及译文后的特征分数(最大堆按照span译文的特征分数来建立)
class StringChart
{
private:
	unsigned int word_num_;
	string source_;
	MaxHeap chart[MAX_WORD_NUM][MAX_WORD_NUM];//对象数组，调用默认构造函数
	StringTrie* trie_; //chart用到了短语表的trie结构，强依赖关系
	FeatureScoreCal* feature_calculator_;
public:
	void setFeatureHandel(FeatureScoreCal* feature_calculator){feature_calculator_ = feature_calculator;}//在进行解码之前，需要new一个feature_calculator把句柄赋值给StringChart
	void initializeChart();//利用string初始化stringchar(枚举string来初始化所有的可能的短语到stringchart中)
	void complete(int start, int end); //对string的start到end的部分进行推导，新生成的推导加入chart[start,end]的MaxHeap中
	void runCKYDecode();//运行解CYK解码
	void getNbest();
	StringChart(StringTrie* trie_);
	StringChart(const string& source, StringTrie* trie_);
	void setSourceString(const string& source);
	~StringChart(void);
};
#endif
