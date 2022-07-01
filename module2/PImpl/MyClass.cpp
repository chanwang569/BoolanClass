#include "MyClass.h"
#include <iostream>
using namespace std;

class MyClass::Impl {

public:
	virtual void invoke()
	{
		cout << text << endl;
	}

	string text;
	int data;
    
};


MyClass::MyClass()
	: pimpl(new Impl())
{
	
}

MyClass::~MyClass()
{
    delete pimpl;
}

// 赋值与拷贝

MyClass::MyClass(const MyClass& other)
	: pimpl(new Impl(*other.pimpl))
{
}

MyClass& MyClass::operator=(MyClass rhs)
{
	swap(pimpl, rhs.pimpl);
	return *this;
}


void MyClass::process()
{
	return pimpl->invoke();
}
