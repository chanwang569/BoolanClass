#include <utility>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;





template <class _Fn, class _T1>
auto invoke_pointer(_Fn __f, _T1& __t1) {
    return (__t1.*__f)();
}

template <class _Fn, class _T1>
auto invoke_functor(_Fn& __f, _T1&& __a0)
{
    return __f(__a0);
}

class MyClass {
  public:
 
    void print(){
        cout<<"print"<<endl;
    }
};

struct Printer {
    void operator() (int data) const {  
      cout  << data << ","<<endl;
    }
};


int main()
{
    MyClass mc;
    Printer p;

    invoke_pointer(&MyClass::print, mc);
    invoke_functor(p,100);

    invoke(&MyClass::print, mc);
    invoke(p,100);
  
}

