#include <iostream>
#include <memory>
using namespace std;

class Base 
{ 
public:
    int a; 
    virtual void process()  { 
        std::cout << "Base.process()"<<endl;
    }
    virtual ~Base(){
        cout<<"~Base()"<<endl;
    }
};
 
class Sub : public Base
{
public:
    void process()  override{ 
        std::cout << "Sub.process()"<<endl; 
    }

    void invoke(){
        std::cout << "Sub.invoke()"<<endl;
    }
    ~Sub(){
        cout<<"~Sub()"<<endl;
    }
};

void cast()
{

}
 
int main(){
    auto b1 = std::make_unique<Base>();
    b1->process();
 
    // Sub* ps1=new Sub();
    // unique_ptr<Sub> u1{ps1};
    // unique_ptr<Sub> u2{ps1};

    auto s1 = std::make_unique<Sub>();
    s1->process();
 
    unique_ptr<Base> b2 {std::move(s1)};
    b2->process();
 
    unique_ptr<Sub>  s2 ( dynamic_cast<Sub*>(b2.release()));
    s2->invoke();
    
    
}