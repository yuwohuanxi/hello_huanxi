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
	int *mpQue; //�������Ԫ�ص����ݽṹ
	int mfront; //��ͷ�±�
	int mrear; //��β�±�
	int msize; //���ݵ��ܳ���

	void resize() ;
};