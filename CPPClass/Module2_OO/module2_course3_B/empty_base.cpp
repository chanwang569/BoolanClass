#include <iostream>
using namespace std;


class Base{
public:
    void process()
    {

    }
 
};

class Sub1{
    Base b; //组合 1
    double data; //8

public:
    void func(){
        b.process();
    }
};

// 私有继承 == 组合
class Sub2: public Base { //
    double data; //8

public:
    void func(){
        Base::process();
    }
};



int main()
{
    Base b;
    cout<<sizeof(b)<<endl;// 1
    cout<<sizeof(Sub1)<<endl;// 
    cout<<sizeof(Sub2)<<endl;//  

    
}