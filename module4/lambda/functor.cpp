#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename Container, typename F>
void foreach (Container c, F op)
{
    for(auto& data : c)
    {
        op(data);
    }                    
}

using FPointer=void (*)(int );


void print(int data)
{
  cout << data << " ";
}

template<typename T>
struct Printer {

    // int n;
    // Printer(int n):n(n){

    // }    
    
    void operator() (T data) const {  
      cout  << data << ",";
    }
};

template<typename T>
struct Comparer {
    bool operator() (T  x, T y) { 
        return x > y; 
    }
};

template<typename T>
bool compare(T x, T y) { 
    return x > y; 
}

// struct ___LambdaXXXX {    
//     void operator() (int data) const {  
//       cout << data <<"-";
//     }
// };

// template<typename T>
// struct ___LambdaXXXX {    
//     void operator() (T data) const {  
//       cout << data <<"-"
//     }
// };

int main()
{
    vector<string> v = { "1","2","3","4","5" };

    // FPointer p=print;
    // //p(100);
    // foreach(v,p);   //函数指针 
    // cout<<endl;

    // Printer pobj;
    // pobj(100);
    // foreach(v, pobj); 

    // cout<<endl;

    // 函数指针
    //foreach(v,print<t);    
    //cout<<endl;

    // 函数对象
    foreach(v, Printer<string>{});
    cout<<endl;

    // Labmda表达式
    foreach(v,  [] (auto data)  {                  
                    cout << data <<"-";
                });
    //foreach(v, ___LambdaXXXX{});

    // 函数指针
    //sort(v.begin(),v.end(), compare);                                    
    // 函数对象
    sort(v.begin(),v.end(), Comparer<string>{});  
    // Labmda表达式
    sort(v.begin(),v.end(), [](auto x, auto y) ->bool { return x > y; });   

    

    // //foreach(v, ___LambdaXXXX{} );

    // cout<<endl;

    // foreach(v,[](auto data) {                  
    //                 cout << data <<"-";
    //             });
    // cout<<endl;
  
    
}
