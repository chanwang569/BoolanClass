// g++ -O2 -std=c++17 10_rvo_unnamed.cpp
//

#include <iostream>  // std::cout

using namespace std;

// No copy and move
class A {
public:
    A() { cout << "Create A\n"; }
    ~A() { cout << "Destroy A\n"; }
    A(const A&) = delete;
    A(A&&) = delete;
};

A getA_unnamed()
{
    return A();
}

int main()
{
    auto a = getA_unnamed();
}
