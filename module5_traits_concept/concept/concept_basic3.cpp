#include<iostream>
#include<concepts> 

using namespace std;

template<typename T>
concept IsPointer = std::is_pointer_v<T>;


template<typename T> 
T add(T a, T b)
{
    return a+b;
}   

template<IsPointer T> //Another way to use concept in Template variable. 
auto add( T a,  T b) 
{
    return add(*a, *b); 
}


// auto add(auto a, auto b)
// {
//     return a+b;
// }   


// auto add(IsPointer auto a, IsPointer auto b) 
// {
//     return add(*a, *b); 
// }


int main()
{
    int x = 100;
    double y = 200.98;

    auto px=&x;
    auto py=&y;
    //cout << add(x, y) << endl; 
    //cout << add(px, py) << endl;

    // auto ppx=&px;
    // auto ppy=&py;
    // cout << add(ppx, ppy) << endl;


}