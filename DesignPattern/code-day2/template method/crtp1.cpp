#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;

// 基类参数T包含了子类编译时信息
template <typename T> 
class Base {
public:

    Base() : i_(0) { }

    void process() { sub()->process_imp(); }
    void process_imp() { 
      cout<<"Base::process()"<<endl;
    }

    //将基类指针转型为子类T的指针
    T* sub() { return static_cast<T*>(this); }

    int get() const { return i_; }

    ~Base(){
      cout<<"~Base()"<<endl;
      
    }

    void destroy(){
      delete sub();
    }

protected:
    int i_;
};


// template <typename T> 
// void destroy(Base<T>* b) 
// { delete static_cast<T*>(b); }

class Sub1 : public Base<Sub1> {
public:
    ~Sub1()
    {
      cout<<"~Sub1"<<endl;
    }

    void process_imp() { 
      cout<<"Sub1::process()"<<endl;
    }
};

class Sub2 : public Base<Sub2> {
public:

    ~Sub2()
    {
      cout<<"~Sub2"<<endl;
    }

    void process_imp() { 
      cout<<"Sub2::process()"<<endl;
    }

};

int main()
{
  Base<Sub1> *ps1=new Sub1();

  //unique_ptr<Base<Sub1>> uptr(new Sub1(), [](Sub1* p){ p->destroy();});
  
  ps1->process();
  //delete ps1->sub();
  //delete ps1;
  ps1->destroy();

  // Base<Sub2> *ps2=new Sub2();
  // ps2->process();

 
  //ps2->destroy();
  
 
  // destroy(ps1);

  // //delete ps2;
  // destroy(ps2);
}