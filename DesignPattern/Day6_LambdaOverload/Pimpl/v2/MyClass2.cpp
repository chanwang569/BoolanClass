#include "MyClass2.h"
#include <iostream>
using namespace std;
//Note: 这个版本编译器会报错。原因是unique_ptr需要类型完整。
class MyClass::Impl {

public:
	virtual void invoke()
	{
		cout << "invoke" << endl;
	}


	~Impl(){
		cout<<"Impl dtor"<<endl;
	}

    Impl(){
		cout<<"Impl ctor"<<endl;
	}
	
	string text;
	int data;

};


MyClass::MyClass()
	: pimpl(make_unique<Impl>())
{
	
}



MyClass::MyClass( const MyClass& other)
: pimpl(make_unique<Impl>(*other.pimpl))
{

}

MyClass& MyClass::operator=(const MyClass& rhs)
{
	if(this==&rhs)
	{
		return *this;
	}

	*pimpl=*rhs.pimpl;

	// MyClass temp(rhs);
	// swap(this->pimpl, rhs.pimpl);

	return *this;
}



void MyClass::process()
{
	return pimpl->invoke();//延迟分发点
}
