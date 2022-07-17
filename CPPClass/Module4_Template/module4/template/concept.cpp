#include <concepts>
#include <iostream>
#include <vector>

using namespace std;


template<integral T >
T sum(vector<T>& v, T s)
{
    for (auto x : v) s += x;
    return s;
}

int main()
{
    vector v{1,2,3,4,5};
    int s=100;
    cout<<sum(v,s);


}