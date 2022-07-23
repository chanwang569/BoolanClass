#include "impl.h";
using namespace std;


class MyClass {
public:
	
	~MyClass();
	MyClass();

	MyClass::MyClass(const MyClass& other);
	MyClass& MyClass::operator=(MyClass rhs);

	void process();

private:

	Impl impl; // 编译时 类定义必须可见

};
