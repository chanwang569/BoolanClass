#include <utility>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

template<typename Iter, typename Callable, typename... Args>
void foreach (Iter current, Iter end, Callable op, Args const&... args)
{
  while (current != end) {     
    std::invoke(op,            
                args...,       
                *current);     
    ++current;
  }
}


class MyClass {
  public:
    void memfunc(int i) const {
      std::cout << "MyClass::memfunc() called for: " << i << '\n';
    }

    void print(){
        cout<<"print"<<endl;
    }
};

template <class _Fn, class _T1>
auto myInvoke(_Fn __f, _T1& __t1) {
    return (__t1.*__f)();
}

int main()
{
    MyClass mc;

    myInvoke(&MyClass::print, mc);


  std::vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19 };


  foreach(primes.begin(), primes.end(),        
          [](std::string const& prefix, int i) { 
            std::cout << prefix << i << '\n';
          },
          "- value: ");                         
    
  MyClass obj;
  foreach(primes.begin(), primes.end(),  
          &MyClass::memfunc,             
          obj);                          
}

