// g++ std=c++17 -I../common 03_vector_move.cpp
//

#include <iostream>              // std::cout
#include <vector>                // std::vector
#include <boost/type_index.hpp>  // boost::typeindex::type_id
#include "vector.h"              // Vector

using std::cout;
using boost::typeindex::type_id;

class obj1 {
public:
    obj1()
    {
        cout << "obj1()\n";
    }
    obj1(const obj1&)
    {
        cout << "obj1(const obj1&)\n";
    }
    obj1(obj1&&)
    {
        cout << "obj1(obj1&&)\n";
    }
};

class obj2 {
public:
    obj2()
    {
        cout << "obj2()\n";
    }
    obj2(const obj2&)
    {
        cout << "obj2(const obj2&)\n";
    }
    obj2(obj2&&) noexcept
    {
        cout << "obj2(obj2&&)\n";
    }
};

template <typename Container>
void test()
{
    cout << "\n*** Testing on " << type_id<Container>() << '\n';
    Container v;
    v.reserve(2);
    v.emplace_back();
    v.emplace_back();
    v.emplace_back();
}

int main()
{
    test<std::vector<obj1>>();
    test<std::vector<obj2>>();
    test<Vector< obj1>>();
    test<Vector< obj2>>();
}
