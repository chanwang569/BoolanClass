#include <memory>

using namespace std;

class MyClass {
public:
	
	~MyClass();
	MyClass();

	MyClass(const MyClass& other);
	MyClass& operator=(const MyClass& rhs);

	MyClass( MyClass&& other);
	MyClass& operator=( MyClass&& other);

	void process();


private:
	// 内部实现
	class Impl;

	// 实现类指针
	unique_ptr<Impl> pimpl;
};
