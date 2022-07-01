#include <iostream>
using namespace std;


class Base1{
    int x;
    int y;
 
public:
    virtual void process1()
    {}
    virtual void process2()
    {}
    virtual void process3()
    {}

    virtual void process4()
    {}
 
};




class Sub1: public Base1{
    double data;


};





class Base2{
    int u;
    int v;
};

class Sub2: public Base1, public Base2
{
    double data;
};





int data;


void process(const vector<Base1*>& v)
{

}
int main()
{

    cout<<sizeof(Base1)<<endl;//16
    cout<<sizeof(Base2)<<endl;//8
    cout<<sizeof(Sub1)<<endl;//16+8=24
    cout<<sizeof(Sub2)<<endl;//16+8+8=32

    Base1* pbarray= new Base1[10];

    vector<Sub1*> v1(10);
    process(v1);

    Base1* pbarray= new Sub1[10];
    for(int i=0;i<10;i++)
    {
      
        pbarray[i]->process();//pbarray[i] pbarray+ sizeof(Base1)*i
    }

}