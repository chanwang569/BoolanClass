#include <iostream>
using namespace std;


class Base{
public:
    void process()
    {

    }
 
};


class Sub1{  //16byte
    Base b; //1+7
    double data; //8

public:
    void func(){
        b.process();
    }
};

// 私有继承 == 组合
class Sub2: private Base { 
    double data; 

public:
    void func(){
        Base::process();
    }
};



int main()
{
    int d1;
    Base b;
    int d2;
    cout<<sizeof(b)<<endl;// 1
    cout<<sizeof(Sub1)<<endl;// 16byte
    cout<<sizeof(Sub2)<<endl;//  8

    
}