// g++ -std=c++17 08_tagged_dispatch.cpp

#include <iostream>     // std::cout/endl
#include <list>         // std::list
#include <type_traits>  // std::false_type/true_type/void_t
#include <vector>       // std::vector

using namespace std;

template <typename T, typename = void_t<>>
struct has_reserve : false_type {
};

template <typename T>
struct has_reserve<T, void_t<decltype(declval<T&>().reserve(1U))>>
    : true_type {
};

template <typename C, typename T>
void _put_data(C& container, T* ptr, size_t size, true_type)
{
    cout << __PRETTY_FUNCTION__ << endl;
    container.reserve(container.size() + size);
    for (size_t i = 0; i < size; ++i) {
        container.push_back(ptr[i]);
    }
}

template <typename C, typename T>
void _put_data(C& container, T* ptr, size_t size, false_type)
{
    cout << __PRETTY_FUNCTION__ << endl;
    for (size_t i = 0; i < size; ++i) {
        container.push_back(ptr[i]);
    }
}

template <typename C, typename T>
void put_data(C& container, T* ptr, size_t size)
{
    _put_data(container, ptr, size, has_reserve<C>{});
}

int main()
{
    list<int> lst;
    vector<int> vec;
    int a[] = {1, 2, 3, 4, 5};
    put_data(lst, data(a), size(a));
    put_data(vec, data(a), size(a));
}
