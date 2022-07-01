
#include <iostream>
#include <array>

// 运行时
inline int squareR(int x) {
  return x * x;
}

// 编译时、运行时
constexpr int squareCR(int x) {
  return x * x;
}

// 编译时
consteval int squareC(int x) {
  return x * x;
}

int main()
{
  int i = 42;


  std::cout << squareR(i) << '\n';      // OK
  std::cout << squareCR(i) << '\n';     // OK 
  //std::cout << squareC(i) << '\n';       // ERROR


  std::cout << squareR(42) << '\n';     // OK
  std::cout << squareCR(42) << '\n';    // OK 
  std::cout << squareC(42) << '\n';     // OK: 


  //std::array<int, squareR(42)> arr1;   // ERROR
  std::array<int, squareCR(42)> arr2;   // OK: 
  std::array<int, squareC(42)> arr3;    // OK: 
  //std::array<int, squareC(i)> arr4;    // ERROR
}


