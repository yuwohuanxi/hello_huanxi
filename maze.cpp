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
	cout<<"请输入行列数"<<endl;
	cin>>x>>y;
	Maze  maze(x,y);
	cout<<"请输入具体的  0 1值，0表示可以通过，1表示无法通过"<<endl;
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


/*oop实现一个迷宫路径的寻找问题 
请输入迷宫路径的行列数： 5  5
请输入迷宫的具体路径信息： 0 表示可以 1 不行
开始寻找迷宫路径...
nofound  打印提示信息 
找到了，把迷宫路径打印一遍  *表示路径
*/
