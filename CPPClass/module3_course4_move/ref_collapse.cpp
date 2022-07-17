#include <iostream>
using namespace std;
// Index: 5 
// 讨论string 左值还是右值
template<typename T>
void invoke(T& data) 
{
    cout<<"T &data"<<endl;
}

template<typename T>
void invoke(T&& data) 
{
    cout<<"T&& data"<<endl;
}


int main()
{
    
    invoke("abc");//左值 类型为const char* 
    invoke("abc"s);//右值 类型为string，后缀加s，其实是操作符重载
    /* 
      basic_string<char> operator "" s( const char *__str, size_t __len )
    {
        return basic_string<char> (__str, __len);
    }
    */
    invoke(string("abc"));//右值 显示声明为string

    //"hello"[0]='a';

    auto *p=&("hello");//s 证明"hello"为左值
    cout<<p<<endl;

}