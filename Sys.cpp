#include<iostream>
using namespace std;
#include<stdio.h>
#include"Sys.h"

void Sys::menu()
	{   
		cout << "1.查看" << endl;
		cout << "2.增加" << endl;
		cout << "3.删除" << endl;
		cout << "4.查询" << endl;
		cout << "5.返回" << endl;
		cout << "-------------" << endl;
		cout << "请选择:";
	}
void Sys::run() 
	{
		loading();
		while(1)
		{
		cout << "-------------" << endl;
		cout << "1.单链表" << endl;
		cout << "2.栈" << endl;
		cout << "3.队列" << endl;
		cout << "4.退出系统" << endl;
		cout << "-------------" << endl;
		cout << "请选择:";
	    cin >> mDsChoice;

		switch (mDsChoice)
		{
		  case 1:
		  case 2:
		  case 3:
			    runChild();
		     	break;
		  case 4:
			     exitt();   //保存数据到文件中
			     exit(0);
		}
		}
	}
void Sys::runChild() // 系统二级菜单的启动函数
	{
		int choice = 0;
	    int input;
		while(1)
		{
		if(mDsChoice==1)
		{
		     cout << "当前选择的数据结构是:" << "单链表" << endl;
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
			  cout << "当前选择的数据结构是:" << "栈" << endl;
			  menu();
			  cin>>choice;
			  int input;
			 switch(choice)
			 {
		        case 1:   mstack.show(); break;
			    case 2:  cout<<"input the data"<<endl;
					    cin>>input;
					    mstack.push(input);
						break;
				case 3 : mstack.pop();
					   cout<<"success delete"<<endl;
						 break;
				case 4:    cout<<"input the data you want to select"<<endl;
					       cin>>input;
						   if(mstack.sele(input))
						   {
							   cout<<"the data exist"<<endl;

						   }
						   else
						   {
							   	   cout<<"the data not exist"<<endl;
						   }
						   break;
				case 5:  return;
					     break;
			 }  
		}
		else if(mDsChoice==3)
		{
			  cout << "当前选择的数据结构是:" << "队列" << endl;
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
void Sys::loading()
	{
		cout<<"加载数据中"<<endl;
		FILE *ostack=fopen("Stack.dat","rb");
		if(ostack==NULL)
		{
			cout<<"stack error open  "<<endl;
			exit(0);
		}
		CStack tstack;
		
		/*while(!feof(ostack))
		{
			int m=0;
		    fread(&m,4,1,ostack);
			tstack.push(m);  
		}
			*/
		int m=0;
		while(fread(&m,4,1,ostack)==1)
		{

			tstack.push(m);	
		}
	
		while(!(tstack.empty()))
		{
			int m=0;
			m=tstack.top();
			mstack.push(m);
			tstack.pop();
		

		}
		fclose(ostack);
		cout<<"加载完成"<<endl;
	}
void Sys::exitt()
	{
		cout<<"数据保存中"<<endl;
		FILE *cstack=fopen("Stack.dat","wb");
		if(cstack==NULL)
		{
			cout<<"stack error close  "<<endl;
			exit(0);
		}
		while(!mstack.empty())
		{
			int tmp=0;
			tmp=mstack.top();
			fwrite(&tmp,4,1,cstack);
			mstack.pop();
		}
		fclose(cstack);
		cout<<"保存完毕，退出系统"<<endl;
//		Sleep(2000);

	}