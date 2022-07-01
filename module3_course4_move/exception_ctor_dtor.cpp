
#include <iostream>
#include <exception>
using namespace std;
// Index: 2 
class MyClass1{
public:
    MyClass1(){
        invalid_argument exp("MyClass1 Ctor Exception");
        throw exp;
        cout<<"MyClass 1 初始化"<<endl;
    }

    ~MyClass1(){
        cout<<"MyClass 1 析构"<<endl;
    }

};

class MyClass2{
public:
    MyClass2(){
        cout<<"MyClass 2 初始化"<<endl;
    }

    ~MyClass2(){
        cout<<"MyClass 2 析构"<<endl;
    }

};

// class BigClass{
//     MyClass2 mc2; //mc2如果构造好了，RAII仍然会保证mc2的析构
//     MyClass1 mc1;
// };


class BigClass{
    MyClass2 *mc2; //mc2如果构造好了，RAII仍然会保证mc2的析构
    MyClass1 *mc1;

public:
    BigClass()
    {
        cout<<"BigClass ctor"<<endl;
        mc2=new MyClass2();
        mc1=new MyClass1(); 
    }

    ~BigClass()
    {
        cout<<"BigClass dtor"<<endl;
        delete mc2; // mc2 构造成功，但是mc1 没有构造成功，这样
        delete mc1;
    }
};


void process() 
{
    cout<<"process start"<<endl;

    BigClass bc;

    cout<<"process end"<<endl;
}

int main() {

    try {
        process();
      
   } catch(invalid_argument& e) {
       cerr<<"invalid arg: " << e.what()<<endl;
   }

}
