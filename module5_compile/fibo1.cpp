#include <iostream>
#include <vector>
using namespace std;

template<int n>
constexpr int fib()
{
    return fib<n-1>() + fib<n-2>();
}

template<>
constexpr int fib<1>()
{
    return 1;
}

template<>
constexpr int fib<2>()
{
    return 1;
}



int main()
{
    //1,1,2,3,5,8,13,21,34,55
    constexpr int f6= fib<6>();

    constexpr int f10= fib<10>();

    cout<<f6<<endl;
    cout<<f10<<endl;
}



