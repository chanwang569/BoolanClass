#include<iostream>
//Concept Basic Usage. 
using namespace std;

template<typename T>
concept IsPointer = std::is_pointer_v<T>;


// Use traits is also option, but the grammar is complicated. And it is not power enough as concept. 
// template<typename T>
// requires (!std::is_pointer_v<T>)
// T add(T a, T b)
// {
//     return a+b;
// }


template<typename T> requires (!IsPointer<T>)
T add_concept(T a, T b)
{
    return a+b;
}

int main()
{
    int x = 100;
    int y = 200;
    // cout << add(x, y) << '\n'; 
    // cout << add(&x, &y) << '\n';

    cout <<add_concept(x,y)<<endl;
   //cout <<add_concept(&x,&y)<<endl;//will return error since &a cannot pass concept check IsPointer<T>

}