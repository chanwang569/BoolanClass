
#include <iostream>
#include <memory>
#include <vector>

using namespace std;




template <class... T>
struct overloaded;

template <class T>
struct overloaded<T> : T {
  overloaded(T one) : T(one) {}
  using T::operator();
};

template <class T, class...U>
struct overloaded<T, U...> : T, overloaded<U...> {

  overloaded(T t, U...u) : 
    T(t), overloaded<U...>(u...) 
  {  }

  using T::operator();
  using overloaded<U...>::operator();
};


template <class... T>
overloaded<T...> make_overload(T... t) {
  return overloaded<T...>(t...);
};


int main(){

  

    std::variant<int,double ,bool, string> numbers;
    numbers="Hello";
    
    auto lams=make_overload(
                        [](int d) { cout <<"int:"<< d; },
                        [](double d) { cout <<"double:"<< d; },
                        [](bool d) { cout <<"bool: "<< d; },  
                        [](string d) { cout <<"string: "<< d; }     
    );
   


     std::visit(lams, numbers);

    

}