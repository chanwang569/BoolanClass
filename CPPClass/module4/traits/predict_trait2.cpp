#include <iostream>
using namespace std;

class MyClass {
  public:
    MyClass() {  
      
    }
    virtual ~MyClass() = default;
};

int main()
{
  
  cout << is_default_constructible_v<MyClass> << '\n';            // true
  cout << is_trivially_default_constructible_v<MyClass> << '\n';  // false
  cout << is_nothrow_default_constructible_v<MyClass> << '\n';    // false
  cout << is_copy_constructible_v<MyClass> << '\n';               // true 
  cout << is_trivially_copy_constructible_v<MyClass> << '\n';     // true
  cout << is_nothrow_copy_constructible_v<MyClass> << '\n';       // true 
  cout << is_destructible_v<MyClass> << '\n';                     // true 
  cout << is_trivially_destructible_v<MyClass> << '\n';           // false
  cout << is_nothrow_destructible_v<MyClass> << '\n';             // true
}
