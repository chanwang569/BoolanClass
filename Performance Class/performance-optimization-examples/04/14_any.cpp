// g++ -std=c++17 14_any.cpp
//

#include <any>       // std::any
#include <iostream>  // std::cout/endl
#include <string>    // std::string
#include <typeinfo>  // std::type_info

using namespace std;

int main()
{
    any obj = string("Hello world");
    cout << obj.type().name() << ": " << any_cast<string>(obj) << endl;
    obj = 42;
    cout << obj.type().name() << ": " << any_cast<int>(obj) << endl;
    if (auto ptr = any_cast<int>(&obj)) {
        cout << "Found int value " << *ptr << endl;
    }
    cout << any_cast<string>(obj) << endl;  // Boom
}
