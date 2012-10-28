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
		int max = (dri_heap_[left_child]->getFeatureScore() < dri_heap_[right_child]->getFeatureScore()) ? right_child : left_child;//得到key最大的
		if(dri_heap_[i]->getFeatureScore() < dri_heap_[max]->getFeatureScore())
		{
			swap(dri_heap_, i, max);
			sink(max);
		}
	}
	else if(left_child <= heap_size_ && right_child > heap_size_)//只是存在左儿子节点？
	{
		if(dri_heap_[i]->getFeatureScore() < dri_heap_[left_child]->getFeatureScore())
			swap(dri_heap_, i, left_child);
		return;
	}
}
//待续，增加beam的剪枝策略
void MaxHeap::addDrivation(Drivation* drivation)
{
	//阈值剪枝：剪掉比heap里面最好的featurescore还要少a倍的边
	if(heap_size_ >= 1)
	{
		if(drivation->getFeatureScore() < (getMax()->getFeatureScore()) + log(THRESHOLD))
		{
			//删除推导
			cout << "删除推导" << drivation->getTargetSeq() << endl;
			delete(drivation);
			return;
		}
	}
	//语言模型端一样的drivation，需要合并
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
	//柱状图剪枝
	if(heap_size_ == BEAM)
	{
		//找到堆中最小的推导
		int min_dri = heap_size_;
		for(int i = heap_size_; i > 1; i++)
			if(dri_heap_[i]->getFeatureScore() < dri_heap_[min_dri]->getFeatureScore())
				min_dri = i;
		if(drivation->getFeatureScore() > dri_heap_[min_dri]->getFeatureScore())
		{
			swap(dri_heap_, min_dri, 1); //把最小的和最大的交换
			delete(dri_heap_[heap_size_]); //删除掉最小的推导
			dri_heap_[1] = drivation; //把形参传递到堆顶
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

//得到最大堆得顶部元素
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
	heap_size_--;//最大堆的长度减去1
	sink(1);
}
//把dri_heap_中的now_size变成最大堆
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
	//指针域赋值为null
	for(int i = 0; i < MAX_HEAP_LENGTH; i++)
		dri_heap_[i] = NULL;
}

MaxHeap::~MaxHeap(void)
{
	for(int i = 0; i< MAX_HEAP_LENGTH; i++)
		delete(dri_heap_[i]);
}
