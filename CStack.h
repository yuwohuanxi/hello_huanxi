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
	   int *mpstack; // �洢ջ������
	   int mtop; // ��ʾջ���±�
	   int msize; // ��ʾջ���ܳ���
	   void resize();
};