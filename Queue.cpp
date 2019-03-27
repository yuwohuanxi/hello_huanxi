#include"Queue.h"
	CCircleQueue::CCircleQueue(int size ) // ���캯��
	{
		msize = size;
		mfront = mrear = 0;
		mpQue = new int[msize];
	}
	CCircleQueue::~CCircleQueue() // ��������
	{
		delete[]mpQue;
		mpQue = nullptr;
	}
	CCircleQueue::CCircleQueue(const CCircleQueue &src) // �������캯��
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
	void CCircleQueue::operator=(const CCircleQueue &src) // ��ֵ���غ���
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

	void CCircleQueue::addQue(int val) // ���
	{
		if (full())
			resize();
		mpQue[mrear] = val;
		mrear = (mrear + 1) % msize;
	}
	void CCircleQueue::delQue() // ����
	{
		if (empty())
			return;
		mfront = (mfront + 1) % msize;
	}
	int CCircleQueue::front() // ���ض�ͷԪ��
	{
		return mpQue[mfront];
	}
	int CCircleQueue::back() // ���ض�βԪ��
	{
		return mpQue[(mrear-1+msize)%msize];
	}
	bool CCircleQueue::full() { return (mrear + 1) % msize == mfront; } // ����
	bool CCircleQueue::empty() { return mrear == mfront; } // �п�


	void CCircleQueue::resize() // 2������ѭ������
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