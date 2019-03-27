#ifndef CSTACK_H
#define CSTACK_H
#endif

class CStack
{
   public:
	   CStack(int size =10);
	   CStack(const CStack &src);
	   void operator=(const CStack &src);
	   	~CStack();
       void pop();
	   void push(int val);
	   int top();
	   bool full() ;
	   bool sele(int val);

	   bool empty();
	   void show();
	   
   private:
	   int *mpstack; // 存储栈的数据
	   int mtop; // 表示栈顶下标
	   int msize; // 表示栈的总长度
	   void resize();
};