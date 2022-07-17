#include <iostream>
using namespace std;


class Base1{
    double d1;
 


};

class Sub1: public virtual  Base1{
    double d2;

};

class Sub2:  virtual public Base1{
    double d3;

};

class Sub3: public Sub1, public Sub2{
    double d4;

};



int main()
{
    cout<<sizeof(Base1)<<endl;//32
    cout<<sizeof(Sub1)<<endl;// 32(B1)+8(S1)+8(vb*)=40 
    cout<<sizeof(Sub2)<<endl;// 32(B1)+8(S2)+8(vb*)=40  
    cout<<sizeof(Sub3)<<endl; // 32(B1)+8(S1)+8(S2)+8(S1vb*)+8(S2vb*)+8(S3)=72


}