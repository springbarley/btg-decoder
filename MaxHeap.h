#ifndef _MAX_HEAP_H_
#define _MAX_HEAP_H_
#include "header.h"
#define MAX_HEAP_LENGTH 100
#define THRESHOLD 0.5 //阈值剪枝法的倍率，倍率越大，剪枝越多的
#define BEAM 20 //用于柱状图剪枝，只保留20个最好的推导

//存储span内的target端的word sequence和对应的特征分数,按照特征分数的值建立最大堆
class Drivation
{
private:
	string target_seq_;
	double feature_score_;
public:
	Drivation(const string& seq_):target_seq_(seq_),feature_score_(0.0){}
	Drivation(const string& seq_, double feature_score):target_seq_(seq_),feature_score_(feature_score){}
	Drivation():target_seq_(""),feature_score_(0.0){}
	double getFeatureScore()const{return feature_score_;}
	const string& getTargetSeq()const {return target_seq_;}
	void setFeatureScore(double score){feature_score_ = score;}
};

class MaxHeap
{
private:
	int heap_size_;
	//这里的heap只存储堆内存里面的Drivation对象的指针,下标从1开始到heap_size_
	Drivation* dri_heap_[MAX_HEAP_LENGTH + 1];
public:
	MaxHeap(void);
	~MaxHeap(void);
	void addDrivation(Drivation* dirvation);
	void sink(int cur_pos);
	void buildMaxHeap(int now_size);
	int size(){return heap_size_;}
	Drivation* getMax();
	friend void swap(Drivation* heap, int a, int b);
	//Drivation** getArray(){return dri_heap_;}
	const Drivation* operator[](int i){return dri_heap_[i];}
	void popMax();
};
#endif
