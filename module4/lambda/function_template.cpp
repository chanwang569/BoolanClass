#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>

using namespace std;


template<typename Seq, typename Value>
Value accumulate(const Seq& s, Value v)
{
    for(auto& x: s)
    {
        v+=x;
    }

    return v;
}

template<typename T>
void func(T a, T b)
{
    std::cout << sizeof(a) << sizeof(b) << std::endl;
}


int main(){

    vector<int> v{1,2,3,4,5};
    int s1=accumulate<vector<int>, int> (v,100);
    cout<<s1<<endl;

    double d[5]{1.1,2.2,3.3,4.4,5.5};
    auto s2=accumulate(d,100.00);
    cout<<s2<<endl;


    func("Tom","Jerry");

    
}