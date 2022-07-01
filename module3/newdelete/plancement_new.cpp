#include <iostream>
using namespace std;


class Point{
public:
  Point(int x, int y, int z):x(x),y(y),z(z){ 
    cout<<"ctor"<<endl;
  }
  ~Point(){ cout<<"dtor"<<endl;}

  virtual void print(){
    cout<<x<<" "<<y<<" "<<z<<endl;
  }

  int x;
  int y;
  int z;
};


int main()
{
  
   cout<<sizeof(Point)<<endl;

   void* memory = std::malloc(sizeof(Point));

  int* p1=(int*)memory;
  for(int i=0;i<6;i++)
  {
    cout<<*p1<<" ";
    p1++;
  }
  
   Point* myObject = ::new (memory) Point[{100,200,300}];
   myObject->print();

  long* p=(long*)memory;
  cout<<*p<<endl;
  p++;

  int* pi=reinterpret_cast<int*>(p);
  cout<<*pi++<<endl;
  cout<<*pi++<<endl;
  cout<<*pi<<endl;
  
   myObject->~Point();
   std::free(memory);

 
  // int data=100;
  // double dvalue=234.323;
  // //static_cast：相关类型转型
  // int value=static_cast<int>(dvalue); 

  // //dynamic_cast: 多态转型 , 基类必须有虚函数(虚析构函数)
  // Sub s1;
  // Base& base=s1;
  // Sub& s=dynamic_cast<Sub&> (base);

  // //reinterpret_cast: 二进制一致性转型
  // //const_cast: 去常量性
  
    void* memory = std::malloc(3*sizeof(Point));
    Point* myObject = reinterpret_cast<Point*>(memory);
    std::uninitialized_fill_n(myObject, 3, Point{100,200,300});
    std::destroy_at(myObject);
    std::free(memory);
}




