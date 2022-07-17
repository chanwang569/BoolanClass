#include <iostream>
#include <memory>
 
using namespace std;
#include <memory>
#include <iostream>


void process1(const widget& ); // 极力推荐
void process2(widget*  );  //OK, 但是建议用&
void process3(unique_ptr<widget>); //较少，一般不推荐：强取豪夺所有权
void process4(share_ptr<widget>); //比unique_ptr好一点

void process5(const unique_ptr<widget>&); 
void process(const share_ptr<widget>&);

widget* process( ); // 不推荐！
unique_ptr<widget> void process(); //较为推荐，常用(大多是工厂函数)
share_ptr<widget> void process(); //OK，但不常用

unique_ptr<widget> w(new widget());
process1(*w);
process2(w.get());


unique_ptr<widget> void process1()
{
  unique_ptr<widget> w{new widget()};
  return w;
}

unique_ptr<widget> void process2(unique_ptr<widget>& r)
{

  return r;
}

int main()
{
  unique_ptr<widget> w{new widget()};
  w=process1();//移动

  unique_ptr<widget> w2=process1();//返回值优化

  unique_ptr<widget> w3=process2(w2);//移动

}















struct Base { 

 virtual ~Base() { }
};
struct Derived1 : public Base {
 
 ~Derived1() { }
};
struct Derived2 : public Base {
 
 ~Derived2() { }
};

unique_ptr<Base> factory(int t) {
 switch(t) {
   case 1:
     return std::make_unique<Derived1>();
   case 2:
     return std::make_unique<Derived2>();
   default:
     return nullptr;
 }
}




int main()
{
   
    unique_ptr<Base>  u=factory(2);

    shared_ptr<Base> p1 = std::move(u);

  


}











/*
  unique_ptr<Base>  p2 = factory(1);
    shared_ptr<Base> s1 =move(p2);
*/