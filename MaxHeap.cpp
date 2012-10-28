#include "MaxHeap.h"

void swap(Drivation** heap, int a, int b)
{
	Drivation* temp = heap[a];
	heap[a] = heap[b];
	heap[b] = temp;

}
void MaxHeap::sink(int i)
{
	if(i < 0 || i >= MAX_HEAP_LENGTH)
	{
		return;
	}
	int left_child = i*2, right_child = i*2+1;
	if(left_child <= heap_size_ && right_child <= heap_size_)
	{
		int max = (dri_heap_[left_child]->getFeatureScore() < dri_heap_[right_child]->getFeatureScore()) ? right_child : left_child;//�õ�key����
		if(dri_heap_[i]->getFeatureScore() < dri_heap_[max]->getFeatureScore())
		{
			swap(dri_heap_, i, max);
			sink(max);
		}
	}
	else if(left_child <= heap_size_ && right_child > heap_size_)//ֻ�Ǵ�������ӽڵ㣿
	{
		if(dri_heap_[i]->getFeatureScore() < dri_heap_[left_child]->getFeatureScore())
			swap(dri_heap_, i, left_child);
		return;
	}
}
//����������beam�ļ�֦����
void MaxHeap::addDrivation(Drivation* drivation)
{
	//��ֵ��֦��������heap������õ�featurescore��Ҫ��a���ı�
	if(heap_size_ >= 1)
	{
		if(drivation->getFeatureScore() < (getMax()->getFeatureScore()) + log(THRESHOLD))
		{
			//ɾ���Ƶ�
			cout << "ɾ���Ƶ�" << drivation->getTargetSeq() << endl;
			delete(drivation);
			return;
		}
	}
	//����ģ�Ͷ�һ����drivation����Ҫ�ϲ�
	for(int i = 1; i <= heap_size_; i++)
	{
		if(dri_heap_[i]->getTargetSeq() == drivation->getTargetSeq())
		{
			if(dri_heap_[i]->getFeatureScore() >= drivation->getFeatureScore())
			{
				delete(drivation);
				return;
			}
			else
			{
				dri_heap_[i]->setFeatureScore(drivation->getFeatureScore());
				delete(drivation);
				return;
			}
		}
	}
	//��״ͼ��֦
	if(heap_size_ == BEAM)
	{
		//�ҵ�������С���Ƶ�
		int min_dri = heap_size_;
		for(int i = heap_size_; i > 1; i++)
			if(dri_heap_[i]->getFeatureScore() < dri_heap_[min_dri]->getFeatureScore())
				min_dri = i;
		if(drivation->getFeatureScore() > dri_heap_[min_dri]->getFeatureScore())
		{
			swap(dri_heap_, min_dri, 1); //����С�ĺ����Ľ���
			delete(dri_heap_[heap_size_]); //ɾ������С���Ƶ�
			dri_heap_[1] = drivation; //���βδ��ݵ��Ѷ�
			sink(1);
		}
		else
		{
			delete(drivation);
			return;
		}
	}
	heap_size_++;
	dri_heap_[heap_size_] = drivation;
	swap(dri_heap_, 1, heap_size_);
	sink(1);
}

//�õ����ѵö���Ԫ��
Drivation* MaxHeap::getMax()
{
	if(heap_size_ >= 1)
		return dri_heap_[1];
	else
	{
		cerr << "drivation heap's size is null, can't get maxSize" << endl;
		return NULL;
	}
}
void MaxHeap::popMax()
{
	swap(dri_heap_, 1, heap_size_);
	heap_size_--;//���ѵĳ��ȼ�ȥ1
	sink(1);
}
//��dri_heap_�е�now_size�������
void MaxHeap::buildMaxHeap(int now_size)
{
	for(int i = now_size; i > 0; i--)
	{
		sink(i);
	}
}

MaxHeap::MaxHeap(void)
{
	//cout << "MaxHeap constructor" << endl;
	heap_size_ = 0;
	//ָ����ֵΪnull
	for(int i = 0; i < MAX_HEAP_LENGTH; i++)
		dri_heap_[i] = NULL;
}

MaxHeap::~MaxHeap(void)
{
	for(int i = 0; i< MAX_HEAP_LENGTH; i++)
		delete(dri_heap_[i]);
}
