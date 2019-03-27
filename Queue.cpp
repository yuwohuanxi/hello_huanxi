#include"Queue.h"
	CCircleQueue::CCircleQueue(int size ) // 构造函数
	{
		msize = size;
		mfront = mrear = 0;
		mpQue = new int[msize];
	}
	CCircleQueue::~CCircleQueue() // 析构函数
	{
		delete[]mpQue;
		mpQue = nullptr;
	}
	CCircleQueue::CCircleQueue(const CCircleQueue &src) // 拷贝构造函数
	{
		this->mpQue = new int[src.msize];
		for (int i = src.mfront; 
			i != src.mrear; 
			i=(i+1)%src.msize)
		{
			mpQue[i] = src.mpQue[i];
		}
		mfront = src.mfront;
		mrear = src.mrear;
		msize = src.msize;
	}
	void CCircleQueue::operator=(const CCircleQueue &src) // 赋值重载函数
	{
		if (this == &src)
			return;

		delete[]mpQue;

		this->mpQue = new int[src.msize];
		for (int i = src.mfront;
			i != src.mrear;
			i = (i + 1) % src.msize)
		{
			mpQue[i] = src.mpQue[i];
		}
		mfront = src.mfront;
		mrear = src.mrear;
		msize = src.msize;
	}

	void CCircleQueue::addQue(int val) // 入队
	{
		if (full())
			resize();
		mpQue[mrear] = val;
		mrear = (mrear + 1) % msize;
	}
	void CCircleQueue::delQue() // 出队
	{
		if (empty())
			return;
		mfront = (mfront + 1) % msize;
	}
	int CCircleQueue::front() // 返回队头元素
	{
		return mpQue[mfront];
	}
	int CCircleQueue::back() // 返回队尾元素
	{
		return mpQue[(mrear-1+msize)%msize];
	}
	bool CCircleQueue::full() { return (mrear + 1) % msize == mfront; } // 判满
	bool CCircleQueue::empty() { return mrear == mfront; } // 判空


	void CCircleQueue::resize() // 2倍扩容循环队列
	{
		int *ptmp = new int[msize * 2];
		int j = 0;
		for (int i = mfront;
			i != mrear;
			i = (i + 1) % msize, j++)
		{
			ptmp[j] = mpQue[i];
		}
		delete[]mpQue;
		mpQue = ptmp;
		mfront = 0;
		mrear = j;
		msize *= 2;
	}