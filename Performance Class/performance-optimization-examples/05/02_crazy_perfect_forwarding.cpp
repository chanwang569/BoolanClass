// g++ -O2 -std=c++17 02_crazy_perfect_forwarding.cpp
//

#include <iostream>     // std:cout
#include <string>       // std::string
#include <type_traits>  // std::enable_if_t/is_assignable_v
#include <utility>      // std::forward

using namespace std;

class person {
public:
    person(string name) : name_(std::move(name)) {}

    template <typename String,
              typename = enable_if_t<is_assignable_v<string&, String>>>
    void set_name(String&& name)
    {
        name_ = forward<String>(name);
    }

    friend ostream& operator<<(ostream& os, const person& p)
    {
        os << "Person{" << p.name_ << "}";
        return os;
    }

private:
    string name_;
};

int main()
{
    person p("Peter");
    p.set_name("Devil");
    cout << p << '\n';
}
