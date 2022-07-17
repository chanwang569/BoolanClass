#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


using FPointer=void (*)(int, int );

template<typename T>
bool compare(T x, T y) { 
    return x > y; 
}

template<typename T>
struct Greater {
    bool operator() (T  x, T y) { 
        return x > y; 
    }
};

struct Less {
    bool operator() (int  x, int y) { 
        return x > y; 
    }
};





int main()
{
    //vector<int> v = { 1,2,3,4,5 };
    list<int> c={1,2,3,4,5};

    // 函数指针
    sort(c.begin(),c.end(), compare<int> );  

    // 函数对象
    sort(c.begin(),c.end(), Greater<int>{});  

    // Labmda表达式
    sort(c.begin(),c.end(), [](int x, int y) { return x > y; });   

    for_each(c.begin(), c.end(),[] (auto data) { cout << data <<", "; });
    cout<<endl;

    unique_ptr<int> s;

    
}
