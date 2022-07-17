#include <iostream>
#include <type_traits>
using namespace std;

// Index: 4 
// To identify cases of lValue | rValue
void process(int&& data);
void process(int& data);

void process(int&& data)
{
    cout<<"right value ref"<<endl;
    auto l = std::is_reference_v<decltype(data)>; //true, why?
    //See decltype definition: Inspects the declared type of an entity or the type and value category of an expression.
    // data is lvalue, but it is declared as rvalue. 
    process(data); //right, or left? 
    // data is rvalue since it has name. 
   
    //int*p= &data;
}
void process(int& data)
{
    cout<<"left value ref"<<endl;
}

void testTypes()
{
    int x=100;
    int y=200;
    auto lDeclType = std::is_reference_v<decltype(x)>; //false.
    lDeclType = std::is_reference_v<decltype(200)>; //true.
    lDeclType = std::is_reference_v<decltype(x++)>; //false 
    lDeclType = std::is_reference_v<decltype(++x)>; //true
}
int main()
{
    testTypes();
    int x=100;
    int y=200;
  
    process(x);
    process(100);

    //int*p=&(x++);
     process(++x);
     process(x++);

     process(x=300);
     process(x+y);
  
     //"hello"
     //"hello"s


    
    // cout<<sizeof("hello")<<endl;
}