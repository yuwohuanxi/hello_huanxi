#ifndef SYS_H
#define SYS_H
#endif
#include"Link.h"
#include"Queue.h"
#include"CStack.h"

class Sys
{
public:
	void menu();
	void run() ;	
	void runChild(); // ϵͳ�����˵�����������	
	void loading();
	void exitt();
private:
	CStack mstack;
    CCircleQueue mqueue;
	Link mlink;
	int mDsChoice; // ��ʾ���˵�ѡ������ݽṹ

};