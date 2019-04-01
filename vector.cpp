
#include <iostream>
#include <string>
using namespace std;

# if 0
容器的空间配置器 allocator
作用：
对象的内存开辟和对象构造分离开
对象的析构和内存释放分离开

allocate ： 内存开辟
deallocate ： 内存释放

construct : 对象构造
destroy : 对象析构
#endif
#if 0
template<typename T>
int findValueIndex(  T arr[], int size, const  T & val)
{

	for(int i=0;i<size;i++)
	{
		if(arr[i]==val)
		{
			return i;
		}
	}
	return -1;
}
template<>
int findValueIndex<const char*>(  const char** p, int size, const  char * const   &find)
{

	for(int i=0;i<size;i++)
	{
		if(strcmp(p[i],find)==0)
		{
			return i;
		}
	}
	return -1;
}
#endif

#if 0
template<typename T>
class Vector // 类的模板名字
{
public:
	Vector();
	~Vector();
	Vector(const Vector<T> &vec);
	Vector(Vector<T> &&vec);
	void operator=(const Vector<T> &vec);
	void operator=(Vector<T> &&vec);	
	void push_back(const T &val); // 末尾添加元素
	void pop_back(); // 末尾删除元素
	bool empty()const; // 判空
	bool full()const; // 判满
	void show()const; // 打印vector容器的所有元素
private:
	T *mpvec;
	int mcur;
	int msize;
	void resize(); // vector容器底层默认2倍扩容
};

template<typename T>
Vector<T>::Vector()
	:mcur(0)
	, msize(0)
	, mpvec(nullptr) {}

template<typename T>
Vector<T>::~Vector()
{
	delete  []mpvec;
	mpvec=nullptr;
}

template<typename  T>
Vector<T>::Vector(const Vector<T> &vec)
{
	mpvec=new T [vec.msize];
	msize=vec.msize;
	mcur=vec.mcur;
	for(int i=0;i<mcur;i++)
	{
		mpvec[i]=vec.mpvec[i];
	}
}
template<typename  T>
Vector<T>::Vector(Vector<T> &&vec)
{
	mpvec=vec.mpvec;
	msize=vec.msize;
	mcur=vec.cur;
	vec.mpvec=nullptr;
}
template<typename  T>
void Vector<T>:: operator=(const Vector<T> &vec)
{
	if(this==&vec)
	{
		return;
	}
	delete  []mpvec;
	mpvec=new T [vec.msize];
	msize=vec.msize;
	mcur=vec.mcur;
	for(int i=0;i<mcur;i++)
	{
		mpvec[i]=vec.mpvec[i];
	}
}
template<typename  T>
void Vector<T>:: operator=(Vector<T> &&vec)  
{
	if(this==&vec)
	{
		return;
	}
	delete  []mpvec;
	mpvec=vec.mpvec;
	msize=vec.msize;
	mcur=vec.cur;
	vec.mpvec=nullptr;

}
template<typename  T>
void Vector<T>::push_back(const T &val) // 末尾添加元素
{
	
	if(full())
	{
		resize();
	}
	mpvec[mcur++]=val;

}
template<typename  T>
void Vector<T>::pop_back()
{
	if(empty())
	{
		return;
	}
	mcur--;
}
template<typename  T>
bool Vector<T>::empty()const
{
	return mcur==0;
}
template<typename  T>
bool Vector<T>::full()const
{
	return mcur==msize;
}
template<typename  T>
void Vector<T>::show()const
{
	if(empty())
	{
	   return;
	}
	for(int i=0;i<mcur;i++)
	{
		cout<<mpvec[i]<<" " ;
	}
	cout<<endl;
	return;
}
template<typename  T>
void Vector<T>::resize()
{
	if(msize==0)
	{
		mpvec =new T [1];
		msize=1;
		return;  
	}
	T * tmp =new T [msize*2];
	for(int i=0;i<msize;i++)
	{
		tmp[i]=mpvec[i];
	}
	delete []mpvec;
	mpvec=tmp;
	tmp=nullptr;
	msize=msize*2;
}
int main()
{
	Vector<int> intVec;
	intVec.push_back(20);
	intVec.push_back(30);
	intVec.pop_back();
	Vector<int>intVec1=intVec;
	Vector<int>intVec2;
	intVec2=intVec;
	intVec.show();
	intVec1.show();
	intVec2.show();
	
	Vector<string> strVec;
	strVec.push_back("hello");
	strVec.push_back("world");
	strVec.show();
	system("pause");
	return 0;
}
#endif


template<typename T>
struct myallocator
{
	// 内存开辟
	T* allocate(size_t size) 
	{
		return (T*)malloc(size * sizeof(T));
	}

	// 内存释放
	void deallocate(T *ptr)
	{
		free(ptr);
	}

	// 对象构造 1.new 2.new const 3.定位new
	void construct(T *ptr, const T &obj)
	{
		new (ptr) T(obj); // 定位new
	}

	// 对象析构
	void destroy(T *ptr)
	{
		ptr->~T();
	}
};

template<typename T,
		typename _Alloc= myallocator<T>>
class Vector // 类的模板名字
{
public:
	Vector();
	~Vector();
	Vector(const Vector<T> &vec);
	Vector(Vector<T> &&vec);
	void operator=(const Vector<T> &vec);
	void operator=(Vector<T> &&vec);

	void reserve(int size); // 预留函数
	
	void push_back(const T &val); // 末尾添加元素
	void pop_back(); // 末尾删除元素
	bool empty()const; // 判空
	bool full()const; // 判满
	int size()const; // 返回vector容器元素的个数
	void show()const; // 打印vector容器的所有元素
private:
	T *mpvec;
	int mcur;
	int msize;
	_Alloc malloctor; // 定义空间配置器对象 

	void resize(); // vector容器底层默认2倍扩容
};

template<typename T,typename _Alloc>
Vector<T,_Alloc>::Vector(): mpvec(nullptr)
     ,mcur(0)
	 ,msize(0){}

template<typename T,typename _Alloc>
Vector<T,_Alloc>::~Vector()
{
	for (int i = 0; i < mcur; ++i)
	{
		// 析构容器中有效的对象
		malloctor.destroy(mpvec+i);
	}
	// 把容器内存释放掉
	malloctor.deallocate(mpvec);
	mpvec = nullptr;
}

template<typename T,typename _Alloc>
Vector<T,_Alloc>::Vector(const Vector<T>& vec)//左值拷贝构造
{
	msize = vec.msize;//空间大小
	mcur = vec.mcur;//现在存的元素个数

	mpvec = malloctor.allocate(msize);
	for (int i = 0; i < mcur; i++)
	{
		malloctor.construct(mpvec+i, vec.mpvec[i]);
	}
}

template<typename T,typename _Alloc>
Vector<T,_Alloc>::Vector(Vector<T>&& vec)
{
	mpvec = vec.mpvec;
	vec.mpvec = nullptr;
	mcur = vec.mcur;
	msize = vec.msize;
}

template<typename T,typename _Alloc>
void Vector<T,_Alloc>::operator=(const Vector<T>& vec)
{
	if (this == &vec)
	{
		return;
	}
	for (int i = 0; i < mcur; i++)
	{
		malloctor.destroy(mpvec+i);
	}
	malloctor.deallocate(mpvec);

	msize = vec.msize;//空间大小
	mcur = vec.mcur;//现在存的元素个数
	mpvec = malloctor.allocate(msize);
	for (int i = 0; i < mcur; i++)
	{
		malloctor.construct(mpvec+i, vec.mpvec[i]);
	}
}

template<typename T,typename _Alloc>
void Vector<T,_Alloc>::operator=(Vector<T>&& vec)
{
	if (this == &vec)
	{
		return;
	}

	for (int i = 0; i < mcur; i++)
	{
		malloctor.destroy(mpvec+i);
	}
	malloctor.destroy(mpvec);

	msize = vec.msize;
	mcur = vec.mcur;
	mpvec = vec.mpvec;
	vec.mpvec = nullptr;
}

template<typename T,typename _Alloc>
void Vector<T,_Alloc>::reserve(int size)
{
	  if (size <= msize)
		return;
	 T *ptmp = malloctor.allocate(size);
	 mpvec=ptmp;
	 msize=size;
	
}

template<typename T,typename _Alloc>
void Vector<T,_Alloc>::push_back(const T & val)//尾部添加
{
	if (full())
	{
		resize();
	}
	malloctor.construct(mpvec+mcur,val);
	mcur++;
}

template<typename T,typename _Alloc>
void Vector<T,_Alloc>::pop_back()//尾部删除
{
	if (empty())
	{
		return;
	}
	malloctor.destroy(mpvec+(mcur-1));
	mcur--;
}

template<typename T,typename _Alloc>
bool Vector<T,_Alloc>::empty() const
{
	return mcur == 0;
}

template<typename T,typename _Alloc>
bool Vector<T,_Alloc>::full() const
{
	return mcur == msize;
}

template<typename T,typename _Alloc>
int Vector<T,_Alloc>::size() const
{
	return mcur;
}

template<typename T,typename _Alloc>
void Vector<T,_Alloc>::show() const
{
	for (int i = 0; i <mcur; i++)
	{
		 (mpvec+i)->show();
	}
	cout << endl;
}

template<typename T,typename _Alloc>
void Vector<T,_Alloc>::resize()//扩容
{
	if (msize > 0)
	{
		T *ptmp = malloctor.allocate(msize * 2);
		for (int i = 0; i < msize; i++)
		{
			malloctor.construct(ptmp+i, mpvec[i]);
			// 析构容器中有效的对象
			malloctor.destroy(mpvec + i);
		}
		// 把容器内存释放掉
		malloctor.deallocate(mpvec);
		mpvec = ptmp;
		msize *= 2;
	}
	else
	{
		mpvec = malloctor.allocate(1); // size * sizeof(T)
		msize = 1;
		mcur = 0;
	}
}

class Test
{
public:
	Test() :mptr(new int[10]) 
	{
		cout << "Test()" << endl;
	}
	~Test() 
	{ 
		delete[]mptr; 
		cout << "~Test()" << endl; 
	}
	Test(const Test& src)
	{
		cout << "Test(const Test&)" << endl;
		mptr = new int[10];
		memcpy(mptr, src.mptr, 10 * 4);
	}
	void operator=(const Test& src)
	{
		cout << "operator=" << endl;
		if (this == &src)
			return;
		delete[]mptr;
		mptr = new int[10];
		memcpy(mptr, src.mptr, 10 * 4);
	}
	void show()
	{
		cout<<"  show()"<<endl;
	}
private:
	int *mptr;
};
int main()
{
	Test t1, t2, t3;
	cout << "------------" << endl;
	Vector<Test> vec;
	vec.reserve(10); // 只想预留空间
	cout << "------------" << endl;
	vec.push_back(t1);
	vec.push_back(t2);
	vec.push_back(t3);
	cout << "------------" << endl;
	vec.pop_back();
	cout << "------------" << endl;
	Vector<Test>vec1=vec;
    Vector<Test>vec2;
	vec2=vec1;
	//vec2.show();
	return 0;
	system("pause");
}
