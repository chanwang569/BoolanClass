// g++ -std=c++20 07_elements_view.cpp
//

#include <iostream>  // std::cout/cerr/endl
#include <map>       // std::map
#include <ranges>    // std::range/views
#include <string>    // std::string

using namespace std;
using std::ranges::range;

void clear_data(range auto&& ids)
{
    for (int id : ids) {
        cout << "Clearing data for ID " << id << endl;
    }
}

int main()
{
    map<int, string> mp{{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
    clear_data(mp | views::keys |
               views::filter([](int n) { return n % 2 == 0; }));
}
