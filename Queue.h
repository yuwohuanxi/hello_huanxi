#ifndef QUEUE_H
#define QUEUE_H
#endif
class CCircleQueue
{
public:
	CCircleQueue(int size = 10) ;
	~CCircleQueue() ;
	CCircleQueue(const CCircleQueue &src) ;
	void operator=(const CCircleQueue &src);
	void addQue(int val) ;
	void delQue() ;
	int front() ;
	int back() ;
	bool full() ;
	bool empty() ;

private:
	int *mpQue; //保存队列元素的数据结构
	int mfront; //队头下标
	int mrear; //队尾下标
	int msize; //扩容的总长度

	void resize() ;
};