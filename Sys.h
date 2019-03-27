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
	void runChild(); // 系统二级菜单的启动函数	
	void loading();
	void exitt();
private:
	CStack mstack;
    CCircleQueue mqueue;
	Link mlink;
	int mDsChoice; // 表示主菜单选择的数据结构

};