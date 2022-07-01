#include <iostream>
#include <any>

using namespace std;



int alloc_times = 0; 
int dealloc_times = 0; 
int allocated = 0; 



void* operator new(size_t size)  { 
  void* p = std::malloc(size); 
  allocated+=size;
  alloc_times++;
  return p; 
} 
 
void operator delete(void* p) noexcept  { 
  dealloc_times++;
  return std::free(p); 
}

void* operator new[](size_t size)   {
  void* p = std::malloc(size); 
  allocated+=size;
  alloc_times++;

  return p; 
} 
void operator delete[](void* p) noexcept  { 
  dealloc_times++;
  return std::free(p); 
}

struct WidgetA{
    double x{};
    WidgetA(){}
    WidgetA(const WidgetA& w)
    {
        cout<<"copy ctor"<<endl;
    }

    WidgetA(WidgetA&& w)
    {
        cout<<"move ctor"<<endl;
    }

    ~WidgetA(){
        cout<<"dtor"<<endl;
    }
};

struct WidgetB{
    double x{};
    double y{};
};
struct WidgetC{
    double x{};
    double y{};
    double z{};
    double u{};
    double v{};
    double w{};
};

union WidgetABCU{
    WidgetA a;
    WidgetB b;
    WidgetC c;

    WidgetABCU(){}
    ~WidgetABCU(){}
    
};

struct MyVisitor {

  void operator()(WidgetA const& a) {
    cout << "It's an WidgetA!"<<endl;
  }
  void operator()(WidgetB const& b) {
    cout << "It's a WidgetB!"<<endl;
  }
  void operator()(WidgetC const& b) {
    cout << "It's a WidgetC!"<<endl;
  }
};

int main(){

    using WidgetABC = std::variant<WidgetA, WidgetB,WidgetC>;
    
    cout<<"std::variant : -----------"<<endl;
    {
        WidgetABC w1=WidgetA{};
        WidgetABC w2=w1;
        cout<<sizeof(w1)<<endl;

        MyVisitor visitor;

        std::visit(visitor, w1);
    }
    cout<<"union : -----------"<<endl;
    {
        WidgetABCU w3;
        cout<<sizeof(w3)<<endl;
        w3.c= {WidgetC()};

        cout<<sizeof(w3)<<endl;

        w3.c.~WidgetC();
    }

    cout<<"总分配："<< allocated<<" bytes, 分配次数："<<alloc_times<<" 释放次数："<<dealloc_times<<endl;
  
    


}
