#include "MyClass2.h"
#include <iostream>
using namespace std;

class MyClass::Impl {

public:
	virtual void invoke()
	{
		cout << "invoke" << endl;
	}


	virtual ~Impl(){
		cout<<"Impl dtor"<<endl;
	}

    Impl(){
		cout<<"Impl ctor"<<endl;
	}
	
	string text;
	int data;

};


//Note：主要差别就在这里。 在当前的cpp中能是能看到impl的完整定义的。所以uniptr可以析构。
//析构
MyClass::~MyClass()=default;// 这里生成的析构器可以看到Impl的定义

//移动构造
MyClass::MyClass( MyClass&& other)=default;

//移动赋值
MyClass& MyClass::operator=(MyClass&& rhs)=default;


MyClass::MyClass()
	: pimpl(make_unique<Impl>())
{
	
}

//拷贝
MyClass::MyClass( const MyClass& other)
: pimpl(make_unique<Impl>(*other.pimpl))
{

}

// 赋值
MyClass& MyClass::operator=(const MyClass& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}

	*pimpl=*rhs.pimpl;
	return *this;
}



void MyClass::process()
{
	return pimpl->invoke();//延迟分发点
}
