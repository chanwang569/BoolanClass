#include <cinttypes>
#include <iostream>
#include <functional>
#include <variant>
#include <memory>

using namespace std;

class Base{ 
    //virtual void process(){}
 };
class Sub : public Base{ };


int main()
{
    Sub * ps=new Sub();
    Base* pb0=ps;
    Base * pb= dynamic_cast<Base*> (ps);

    Sub* ps2=dynamic_cast<Sub*>(pb);
    delete ps; 
}