#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
void process1(T& value)
{
     cout<<value<<endl;
}

template<typename T>
void process2(T value)
{
    cout<<value<<endl;
}

template<typename T>
void invoke(T&& value)
{
    //do(std::forward<T>(value));

}

int main()
{

    vector<int> c1(100);
    vector c2{10,20,30};

    pair<int, string> keyv1{100, "C++"s};
    pair keyv2{200,"Java"};
    auto keyv3=make_pair(300,"GO"s);
    keyv3=keyv2;
    cout<<keyv3.first<<":"<<keyv3.second<<endl;

    //auto s=make_unique(c);

    int data1=100;
    int& data2=data1;
    const int data3=data1;
    const int& data4=data1;

    //template<typename T> void process1(T& value);
    process1(data1);//  T是int, value 是int&
    process1(data2);//  T是int, value 是int&
    process1(data3);//  T是const int, value 是const int&
    process1(data4);//  T是const int, value 是const int&

    process2(data1);// T 是int, value 是 int
    process2(data2);// T 是int, value 是 int
    process2(data3);// T 是int, value 是 int
    process2(data4);// T 是int, value 是 int
    
}