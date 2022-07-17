#include <iostream>
using namespace std;



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
    
    //invoke("abc");//左值
    invoke("abc"s);//string
    invoke(string("abc"));

    //"hello"[0]='a';

    

}