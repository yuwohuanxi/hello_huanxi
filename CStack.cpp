#include<iostream>
using namespace std;
#include"CStack.h"

CStack::CStack(int size)
{
	mtop=0;
	msize=size;
	mpstack=new int[msize];
}
CStack::CStack(const CStack &src)
{
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
}
void CStack::operator=(const CStack &src)
{
		
		if (this == &src)
			return;
		delete[]mpstack;
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
}
CStack::~CStack() // 析构函数，释放对象
{
		delete[]mpstack;
		mpstack = nullptr;
}
void CStack::show()
{
     	int m=mtop;  
		while(!((*this).empty()))
		{
			int tmp=0;
			tmp=(*this).top();
			cout<<tmp<<" ";
			(*this).pop();
		}
		cout<<endl;
		mtop=m;


}
void CStack::push(int val) // 入栈
{
		if (full())
			resize();
		mpstack[mtop++] = val;
}
void CStack::pop() // 出栈
{
		if (empty())
			return;
		--mtop;
}
int CStack::top()
{
		if (empty())
			throw "stack is empty!";
		return mpstack[mtop-1];
}
bool CStack::full() { return mtop == msize; }
bool CStack::empty() { return mtop == 0; }
void CStack::resize()
{
		int *ptmp = new int[msize * 2];
		for (int i = 0; i < msize; ++i)
		{
			ptmp[i] = mpstack[i];
		}
		delete []mpstack;
		mpstack = ptmp;
		msize *= 2;
}
bool CStack::sele(int val)
{
	int m=mtop;  
	while(!((*this).empty()))
	{
		int tmp=0;
		tmp=(*this).top();
		if(tmp==val)
		{
			mtop=m;
			return true;

		}
		(*this).pop();
	}
		mtop=m;
		return false;
}