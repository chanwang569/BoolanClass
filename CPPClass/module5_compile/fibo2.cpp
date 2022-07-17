#include <iostream>
#include <vector>
using namespace std;

template<int n>
struct Fib
{
    static constexpr int value=Fib<n-1>::value+ Fib<n-2>::value;
};

template<>
struct Fib<1>
{
    static constexpr int value=1;
};

template<>
struct Fib<2>
{
    static constexpr int value=1;
};



int main()
{
    //1,1,2,3,5,8,13,21,34,55
    constexpr int f6= Fib<6>::value;

    constexpr int f10= Fib<10>::value;

    cout<<f6<<endl;
    cout<<f10<<endl;
}



