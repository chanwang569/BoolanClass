#include <iostream>
#include <numeric>
using namespace std;



void process(int&& data);
void process(int& data);

void process(int&& data)
{
    cout<<"right value ref"<<endl;
    process(data); //right, or left? 
    //int*p= &data;
}
void process(int& data)
{
    cout<<"left value ref"<<endl;
}


int main()
{
    int x=100;
    int y=200;
    
    process(x);
    process(100);

    //int*p=&(x++);
     process(++x);
     process(x++);

     process(x=300);
     process(x+y);
  
    
    auto *p=&("hello");//s
    cout<<p<<endl;
    
    
}