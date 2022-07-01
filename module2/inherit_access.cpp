#include <iostream>
using namespace std;

class Base1{
protected:
    Base1(){
        cout<<"Base1()"<<endl;
    }

};

class Sub1:  Base1{
public:
   Sub1(){
       cout<<"Sub1()"<<endl;
   }

};

int main()
{
    Sub1 s1;

}


