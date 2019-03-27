#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<windows.h>
using namespace std;

#if 0
class A
{
public:
	A(int data=10):ma(data){}
private:
	int ma;
};
int main()
{
	(A)7=(A)10;
	(A)7=10;
	A(7)=10;
	*(int*)7=10;
}
#endif

#  if 0
class CStack
{
public:

	CStack(int size = 3) 
	{
		mtop = 0;
		msize = size;
		mpstack = new int[msize];
	}
	CStack(const CStack &src)
	{
		cout << this << "CStack(const CStack&)" << endl;
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	void operator=(const CStack &src)
	{
		cout << "operator=" << endl;

		// ��ֹ�Ը�ֵ
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
	~CStack() // �����������ͷŶ���
	{
		cout << this << " ~CStack()" << endl;
		delete[]mpstack;
		mpstack = nullptr;
	}
	void push(int val) // ��ջ
	{
		if (full())
			resize();
		mpstack[mtop++] = val;
	}
	void pop() // ��ջ
	{
		if (empty())
			return;
		--mtop;
	}
	int top()
	{
		if (empty())
			throw "stack is empty!";
		return mpstack[mtop-1];
	}
	bool full() { return mtop == msize; }
	bool empty() { return mtop == 0; }
private:
	int *mpstack; // �洢ջ������
	int mtop; // ��ʾջ���±�
	int msize; // ��ʾջ���ܳ���

	void resize()
	{
		int *ptmp = new int[msize * 2];
		//memcpy(ptmp, mpstack, sizeof(int)*msize);
		//realloc  �������ݽ�ֹʹ��realloc/memcpy��Щ����!!!
		for (int i = 0; i < msize; ++i)
		{
			ptmp[i] = mpstack[i];
		}
		delete []mpstack;
		mpstack = ptmp;
		msize *= 2;
	}
};
class CCircleQueue
{
public:
	CCircleQueue(int size = 10) // ���캯��
	{
		msize = size;
		mfront = mrear = 0;
		mpQue = new int[msize];
	}
	~CCircleQueue() // ��������
	{
		delete[]mpQue;
		mpQue = nullptr;
	}
	CCircleQueue(const CCircleQueue &src) // �������캯��
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
	void operator=(const CCircleQueue &src) // ��ֵ���غ���
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

	void addQue(int val) // ���
	{
		if (full())
			resize();
		mpQue[mrear] = val;
		mrear = (mrear + 1) % msize;
	}
	void delQue() // ����
	{
		if (empty())
			return;
		mfront = (mfront + 1) % msize;
	}
	int front() // ���ض�ͷԪ��
	{
		return mpQue[mfront];
	}
	int back() // ���ض�βԪ��
	{
		return mpQue[(mrear-1+msize)%msize];
	}
	bool full() { return (mrear + 1) % msize == mfront; } // ����
	bool empty() { return mrear == mfront; } // �п�

private:
	int *mpQue; //�������Ԫ�ص����ݽṹ
	int mfront; //��ͷ�±�
	int mrear; //��β�±�
	int msize; //���ݵ��ܳ���

	void resize() // 2������ѭ������
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
};
class Link
{
public:
	Link() // ���캯��
	{
		mphead = new Node(); // new Node;
	}
	~Link() // ��������
	{
		Node *pcur = mphead;
		while (pcur != nullptr)
		{
			mphead = mphead->mpnext;
			delete pcur;
			pcur = mphead;
		}
	}
	void insertHead(int val)
	{
		Node *ptmp = new Node(val); // Node node(val);
		ptmp->mpnext = mphead->mpnext;
		mphead->mpnext = ptmp;
	}
	void insertTail(int val)
	{
		Node *pcur = mphead;
		while (pcur->mpnext != nullptr)
		{
			pcur = pcur->mpnext;
		}
		pcur->mpnext = new Node(val);
	}
	void remove(int val) // ɾ������ֵΪval�Ľڵ�
	{
		Node *ppre = mphead;
		Node *pcur = mphead->mpnext;

		while (pcur != nullptr)
		{
			if (pcur->mdata == val)
			{
				ppre->mpnext = pcur->mpnext;
				delete pcur;
				pcur = ppre->mpnext;
			}
			else
			{
				ppre = pcur;
				pcur = pcur->mpnext;
			}
		}
	}
	void show()
	{
		Node *pcur = mphead->mpnext;
		while (pcur != nullptr)
		{
			cout << pcur->mdata << " ";
			pcur = pcur->mpnext;
		}
		cout << endl;
	}
private:
	// �ڵ�����
	struct Node
	{
		Node(int data = 0)
		{
			mdata = data;
			mpnext = nullptr;
		}
		int mdata;
		Node *mpnext;
	};
	Link(const Link&);
	void operator=(const Link&);

	Node *mphead;
};
class System
{
public:
	void  loading()
	{
		cout<<"����������"<<endl;


		cout<<"�������"<<endl;

	}

	void  exitt()
	{
		cout<<"���ݱ�����"<<endl;

		cout<<"������ϣ��˳�ϵͳ"<<endl;
		Sleep(1000);

	}
	void menu()
	{   
		cout << "1.�鿴" << endl;
		cout << "2.����" << endl;
		cout << "3.ɾ��" << endl;
		cout << "4.��ѯ" << endl;
		cout << "5.����" << endl;
		cout << "-------------" << endl;
		cout << "��ѡ��:";
	}
	void run() 
	{
		while(1)
		{
		cout << "-------------" << endl;
		cout << "1.������" << endl;
		cout << "2.ջ" << endl;
		cout << "3.����" << endl;
		cout << "4.�˳�ϵͳ" << endl;
		cout << "-------------" << endl;
		cout << "��ѡ��:";
	    cin >> mDsChoice;

		switch (mDsChoice)
		{
		  case 1:
		  case 2:
		  case 3:
			    runChild();
		     	break;
		  case 4:
			     exitt();   //�������ݵ��ļ���
			     exit(0);
		}
		}
	}
	void runChild() // ϵͳ�����˵�����������
	{
		int choice = 0;
	    int input;
		while(1)
		{
		if(mDsChoice==1)
		{
		     cout << "��ǰѡ������ݽṹ��:" << "������" << endl;
		       menu();
			 cin>>choice;
			 switch(choice)
			 {
		        case 1:  mlink.show(); break;
			    case 2:  cout<<"input the data"<<endl;
					    cin>>input;
					    mlink.insertHead(input);
						break;
				case 3: cout<<"input the data you want to delete"<<endl;
			             cin>>input;
						 mlink.remove(input);
						 break;
				case 4:  cout<<"input the data you want to select"<<endl;
					       cin>>input;
						   //mlink.
						   break;
				case 5:  return;
					     break;
			 }    
		}
		else if(mDsChoice==2)
		{
			  cout << "��ǰѡ������ݽṹ��:" << "ջ" << endl;
			  menu();
			  cin>>choice;
			  int input;
			 switch(choice)
			 {
		        case 1:    //mstack.show(); break;
			    case 2:  cout<<"input the data"<<endl;
					    cin>>input;
					    mstack.push(input);
						break;
				case 3 : mstack.pop();
						 break;
				case 4:    cout<<"input the data you want to select"<<endl;
					       cin>>input;
						   //mstack.
						   break;
				case 5:  return;
					     break;
			 }  
		}
		else if(mDsChoice==3)
		{
			  cout << "��ǰѡ������ݽṹ��:" << "����" << endl;
			  menu();
			  cin>>choice;
			  int input;
			 switch(choice)
			 {
		        case 1:    //mqueue.show(); break;
			    case 2:  cout<<"input the data"<<endl;
					    cin>>input;
					    mqueue.addQue(input);
						break;
				case 3 : mqueue.delQue();
						 break;
				case 4:    cout<<"input the data you want to select"<<endl;
					       cin>>input;
						   //mqueue.
						   break;
				case 5:  return;
					     break;
			 }  
		}	
		}
	}
	
private:
	CStack mstack;
	CCircleQueue mqueue;
	Link mlink;
	int mDsChoice; // ��ʾ���˵�ѡ������ݽṹ

};
#endif
#if 0
const int RIGHT =0;
const int  DOWN=1;
const int LEFT=2;
const  int UP=3;
const int WAY_NUM=4;
const int OK=5;
const int ERROR=6;

class MazeNode
{
private:
	int _x;
	int _y;
	int _val;
	int _state[WAY_NUM];
};
class CStack
{
	MazeNode * _pstack;
	int _top;
	int _size;
};
#endif


class Maze
{
public:
	Maze(int row,int col)
	   {
		   _rows=row;
		   _cols=col;
		   _pmaze=new int*  [_rows];
		   for(int i=0;i<_rows;i++)
		   {
			   _pmaze[i]=new int[_cols];
		   }
	   }
	   ~Maze()
	   {
		    for(int i=0;i<_rows;i++)
		   {
			   delete  []_pmaze[i];
		   }
			delete   []_pmaze;
	   }

	   void initMazeNode(int data,int i,int j)
	   {
		   _pmaze[i][j]=data;
	   }

	   void findMazePath()
	   {
		   int** visited=new int* [_rows];
		   for(int i=0;i<_rows;i++)
		   {
			   visited[i]=new int[_cols];
		   }
		   for(int i=0;i<_rows;i++)
		   {
			   for(int j=0;j<_cols;j++)
			   {
				   visited[i][j]=_pmaze[i][j];
			   }
		   }
		  if(hasPathCore(0,0,visited))
		  {
			  showResult(visited);
		  }
		  else
		  {
			  cout<<"not found"<<endl;
		  }

		  for(int i=0;i<_rows;i++)
		   {
			   delete  []visited[i];
		   }
			delete   []visited;

	   }
	   bool hasPathCore(int startx,int starty,int** visited)
	   {
		   if(startx==_rows-1&&starty==_cols-1&&visited[startx][starty]==0)
		   {
			   visited[startx][starty]=2;
			   return true;
		   }
		   bool hasPath=false;
		   if(startx>=0&&
			   startx<_rows&&
			   starty>=0&&
			   starty<_cols&&
			   (visited[startx][starty]==0))
		   {
			   visited[startx][starty]=2;
		  
			   if(hasPathCore(startx,starty+1,visited))
			   {
				   hasPath=true;
			   }
			   else if(hasPathCore(startx+1,starty,visited))
			   {
				   hasPath=true;
			   }
			   else if(hasPathCore(startx,starty-1,visited))
			   {
				   hasPath=true;
			   }
			   else  
			   {
				   hasPath=hasPathCore(startx-1,starty,visited);
			   }
			   /*
		       hasPath=(hasPathCore(startx+1,starty,visited)||
			       hasPathCore(startx-1,starty,visited)||
				   hasPathCore(startx,starty-1,visited)||
				   hasPathCore(startx,starty+1,visited));
				   */

		       if(!hasPath)
	         {
		        	visited[startx][starty]=1;
	    	 }
		   }

		   return hasPath;

	   }
	   void showResult(int ** visited)
	   {
		   for(int i=0;i<_rows;i++)
		   {
			   for(int j=0;j<_cols;j++)
			   {
				   if(visited[i][j]==2)
				   {
					   _pmaze[i][j]=2;
				   }
			   }
		   }

		      for(int i=0;i<_rows;i++)
		   {
			   for(int j=0;j<_cols;j++)
			   {
				  cout<<_pmaze[i][j]<<" ";
			   }
			   cout<<endl;
		   }

	   }
private:
	int _rows;
	int _cols;
	int ** _pmaze;
};
int main()
{
	int x,y;
	cout<<"������������"<<endl;
	cin>>x>>y;
	Maze  maze(x,y);
	cout<<"����������  0 1ֵ��0��ʾ����ͨ����1��ʾ�޷�ͨ��"<<endl;
	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		{
			int data;
			cin>>data;

			maze.initMazeNode(data,i,j);
		}
		//cout<<endl;
	}
	maze.findMazePath();
	system("pause");

	return 0;
}


/*oopʵ��һ���Թ�·����Ѱ������ 
�������Թ�·������������ 5  5
�������Թ��ľ���·����Ϣ�� 0 ��ʾ���� 1 ����
��ʼѰ���Թ�·��...
nofound  ��ӡ��ʾ��Ϣ 
�ҵ��ˣ����Թ�·����ӡһ��  *��ʾ·��
*/