#include <iostream>
#include <optional>

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

struct Widget{
    double x{};
    double y{};
    double z{};
    double u{};
    double v{};
    double w{};
    Widget(){}
    Widget(const Widget& w)
    {
        cout<<"copy ctor"<<endl;
    }

    Widget(Widget&& w)
    {
        cout<<"move ctor"<<endl;
    }

    ~Widget(){
        cout<<"dtor"<<endl;
    }
};

int main(){

    
    {
        optional<Widget> op1=Widget{};
        
        optional<Widget> op2=op1;

        optional<int> op3=100;
        optional<double> op4=10.23;

        cout<<sizeof(op1)<<endl;
        cout<<sizeof(op2)<<endl;
        cout<<sizeof(op3)<<endl;
        cout<<sizeof(op4)<<endl;
        
        
        
    }
    

    cout<<"总分配："<< allocated<<" bytes, 分配次数："<<alloc_times<<" 释放次数："<<dealloc_times<<endl;
  
    


}
