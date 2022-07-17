
#include <utility>
#include <string>
#include <iostream>
#include <type_traits>
#include <complex>

using namespace std;


/*
template <bool, class _Tp = void> 
struct  enable_if {};

template <class _Tp> struct 
enable_if<true, _Tp> {typedef _Tp type;};

//C++ 14提供
template <bool _Bp, class _Tp = void> 
using enable_if_t = typename enable_if<_Bp, _Tp>::type;
*/



template<typename T, typename= std::enable_if<is_arithmetic<T>::value>>
void process(T& data) {
    data++;

}

template<typename T, typename=std::enable_if<is_arithmetic_v<T>>>
void process0(T& data) {
    data++;

}



template<typename T, typename=std::enable_if_t<is_arithmetic_v<T>>>
void process1(T& data) {
    data++;

}


/*
template<typename T>
typename std::enable_if<is_arithmetic_v<T>,T>::type process2(T& data) {
    data++;

    return data;
}*/


//使用别名
// template<typename T>
// using sure_arithmetic = std::enable_if_t<is_arithmetic<T>>;

// template<typename T>
// sure_arithmetic<T> void process(T& data) {
//     data++;
// }

template<typename T>
typename std::enable_if<(sizeof(T) > 4)>::type
invoke() {
}

int main(){

    int data=100;
    process(data);
    cout<<data<<endl;

    // string text="hello"s;
    // process(text);

    invoke<double>();
}
