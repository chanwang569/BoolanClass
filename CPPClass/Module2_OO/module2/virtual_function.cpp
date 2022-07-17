#include <iostream>

using namespace std;


class Base1{
public:
    long long d1;

    virtual unique_ptr<Base1> clone(){

    }
};

class Base2{
public:
    long long d2;
    
    virtual void M2(){
        
    }
};

class Sub: public Base1, public Base2{
public:
    long long d3;

    virtual void M3(){

    }
};

int main(){
    Base1 b1;


    Sub s;

    b1=s;

    b1.d1=100;
    Base2 b2;
    b2.d2=200;
    Sub s;
    s.d1=100;
    s.d2=200;
    s.d3=300;
    cout<<sizeof(b1)<<endl;
    cout<<sizeof(b2)<<endl;
    cout<<sizeof(s)<<endl;//16+16+8= 32+8=40

    long long* p1=(long long*)&b1;
    long long* pvt1=p1;
    cout<<*p1<<",";
    p1++;
    cout<<*p1<<endl;

    long long* p2=(long long*)&b2;
    long long* pvt2=p2;
    cout<<*p2<<",";
    p2++;
    cout<<*p2<<endl;

    long long* p3=(long long*)&s;
    long long* pvt3=p3;
    cout<<*p3<<",";
    p3++;
    cout<<*p3<<",";
    p3++;
    long long* pvt4=p3;
    cout<<*p3<<",";
    p3++;
    cout<<*p3<<",";
    p3++;
    cout<<*p3<<endl;


    cout<<*pvt1<<":"<< *((long long*)(*pvt1))<<endl;
    cout<<*pvt2<<":"<< *((long long*)(*pvt2))<<endl;
    
    cout<<*pvt3<<":"<< *((long long*)(*pvt3))<<endl;

    cout<<*pvt4<<":"<< *((long long*)(*pvt4))<<endl;


}

