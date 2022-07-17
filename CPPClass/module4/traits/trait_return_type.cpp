#include <iostream>
#include <vector>

using namespace std;


struct Complex{
    int re;
    int im;

    Complex(int _re, int _im):re(_re),im(_im){

    }
};

Complex operator+(const Complex& r1, const Complex& r2)
{
    return Complex(r1.re+r2.re, r1.im+r2.im);
}

//traits template
template<typename T>
struct SumTraits;

template<>
struct SumTraits<char> {
    using SumT = int;
    constexpr static SumT  zero=0;
};

template<>
struct SumTraits<short> {
    using SumT = int;
    constexpr static SumT  zero=0;
};

template<>
struct SumTraits<int> {
    using SumT = long;
    constexpr static SumT  zero=0;
};

template<>
struct SumTraits<unsigned int> {
    using SumT = unsigned long;
    constexpr static SumT  zero=0;
};

template<>
struct SumTraits<float> {
    using SumT = double;
    constexpr static SumT  zero=0;
};

template<>
struct SumTraits<Complex> {
    using SumT = Complex;
    inline static Complex const zero=Complex{0,0};
};



template<typename Iter>
auto sum (Iter start, Iter end)
{
    using value_type = typename std::iterator_traits<Iter>::value_type;

    value_type total=SumTraits<value_type>::zero;
 
    while (start != end) {
        total =total+ *start;
        ++start;
    }
    return total;
}

int main()
{

   
    vector<int> v1{10,20,30,40,50};

    vector<Complex> v2{ Complex{1,2}, Complex{3,4}, Complex{5,6}};

    Complex s2=sum(v2.begin(), v2.end());
    
    cout<<s2.re<<"+" <<s2.im<<"i"<<endl;

}


