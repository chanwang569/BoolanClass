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

    void process() { 
      sub()->process_imp(); //编译时分发
    }

    //如果不实现，类似纯虚函数
    void process_imp() { 
      cout<<"Base::process()"<<endl;
    }

    //将基类指针转型为子类T的指针
    T* sub() { return static_cast<T*>(this); }

     ~Base()
    {
      //delete static_cast<T*>(this);
      cout<<"~Base()"<<endl;
    }


  void destroy() 
  { 
      delete static_cast<T*>(this); }

  };


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







template <typename T>
void invoke(Base<T>* pb)
{
  pb->process();
}


int main()
{


   Sub1 *ps1=new Sub1();
  ps1->process();// sub1. process()

  Base<Sub2> *ps2=new Sub2();
  //ps2->process();// sub2. process()

  invoke(ps1);
  invoke(ps2);

  //delete ps1;
  ps1->destroy();
  //ps1->destroy();

  //delete ps2;
  //destroy(ps2);


}