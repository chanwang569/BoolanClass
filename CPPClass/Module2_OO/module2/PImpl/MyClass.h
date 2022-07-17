using namespace std;

class MyClass {
public:
	
	~MyClass();
	MyClass();

	
	MyClass::MyClass(const MyClass& other);
	MyClass& MyClass::operator=(MyClass rhs);

	void process();


private:
	// 内部实现
	class Impl;

	// 实现类指针
	Impl* pimpl;
};
