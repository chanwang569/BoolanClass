// g++ -std=c++17 05_sv_fp_map.cpp
//

#include <functional>   // std::function
#include <iostream>     // std::cout/endl
#include <map>          // std::map
#include <string_view>  // std::string_view
#include <gsl/span>     // gsl::span

using namespace std;

static map<string_view, int (*)(int, int), less<>> op_dict{
    {"+", +[](int x, int y) { return x + y; }},
    {"-", +[](int x, int y) { return x - y; }},
    {"*", +[](int x, int y) { return x * y; }},
    {"/", +[](int x, int y) { return x / y; }},
};

#define PRINT(expr) cout << #expr << " is " << expr << endl;

int main()
{
    string s;
    s += '+';
    PRINT(op_dict[s](3, 4));
    PRINT(sizeof(int (*)(int, int)));
    PRINT(sizeof(function<int(int, int)>));
    PRINT(sizeof(string));
    PRINT(sizeof(string_view));
    PRINT(sizeof(gsl::span<char>));
    PRINT(sizeof(gsl::span<char, 8>));
}
