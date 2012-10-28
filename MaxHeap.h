#ifndef _MAX_HEAP_H_
#define _MAX_HEAP_H_
#include "header.h"
#define MAX_HEAP_LENGTH 100
#define THRESHOLD 0.5 //��ֵ��֦���ı��ʣ�����Խ�󣬼�֦Խ���
#define BEAM 20 //������״ͼ��֦��ֻ����20����õ��Ƶ�

//�洢span�ڵ�target�˵�word sequence�Ͷ�Ӧ����������,��������������ֵ��������
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
	//�����heapֻ�洢���ڴ������Drivation�����ָ��,�±��1��ʼ��heap_size_
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
