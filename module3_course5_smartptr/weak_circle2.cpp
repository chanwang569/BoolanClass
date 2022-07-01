#include <iostream>
#include <memory>
 
using namespace std;
#include <memory>
#include <iostream>


struct BClass;

struct AClass
{
    shared_ptr<BClass> pb; //强引用
    ~AClass() { std::cout << "~AClass()\n"; }
};
struct BClass
{
    weak_ptr<AClass> pa;//弱引用
    ~BClass() { std::cout << "~BClass()\n"; }
};

struct CClass
{
    shared_ptr<AClass> pa;
    ~CClass() { std::cout << "~CClass()\n"; }
};

int main()
{
    {
        shared_ptr<AClass> a = std::make_shared<AClass>();
        shared_ptr<BClass> b = std::make_shared<BClass>();
        shared_ptr<CClass> c = std::make_shared<CClass>();

        a->pb = b; //强引用
        b->pa = a; //weak引用

        c->pa = a; //强引用
        // 释放，顺序？c, 
    }

    
}

