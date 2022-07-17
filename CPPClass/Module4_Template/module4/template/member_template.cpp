#include <iostream>
using namespace std;


template <typename T>
class Complex{
    T re, im;

   

public:

    using SType=typename SumTraits<T>::SumType;

    struct Point{int x,int y};

    Complex(const Complex&)=default;

    T real() const {return re;}
    T imag() const {return im;}

    Complex(T _re, T _im):re{_re}, im{_im}
    {}

    template<typename U>
    Complex(const Complex<U>& c):
        re{static_cast<T>(c.real())},
        im{static_cast<T>(c.imag())}
        {

        }
    
    virtual void print(){
        cout<<"["<<re<<","<<im<<"]"<<endl;
    }

    template<typename U>
    virtual void add(U r, U i) // 不可以是虚函数
    {
        this->re+=r;
        this->im+=i;
    }
};

int main(){
    Complex<int> c1{100,200};
    Complex<double> c2{34.7, 89.9};
    Complex<int> c3=c2;

    // c1.print();
    // c2.print();
    // c3.print();

    c2.add(100,200);
    c2.add(100.234,200.234);

    // c2.print();

}