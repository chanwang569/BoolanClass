#include <iostream>
#include <vector>

class Point{
    int m_x;
    int m_y;
public : 
    Point(int x, int y) : m_x(x), m_y(y) {}
};


class Widget{
    Point *data;
    int value;
public : 
    Widget() = default;
    Widget(int x, int y) : data(new Point(x,y)) {
        std::cout << " constructor " << std::endl;
    }
    Widget(const Widget& rhs){
        if(rhs.data != nullptr) {
            data = new Point(*rhs.data);
        }else{
            data = nullptr;
        }
        std::cout << "copy constructor" << std::endl;
    }

    Widget(Widget&& rhs) : data(rhs.data){
        value = rhs.value;
        rhs.data = nullptr;
        std::cout << "move constructor" << std::endl;  
    }

    Widget& operator=(Widget&& rhs){
        if(&rhs == this) return *this;
        delete data;
        data = rhs.data;
        rhs.data = nullptr;
        std::cout << "move assigment " << std::endl;
        return *this;
    }
    Widget& operator=(const Widget & rhs){
        if(this == &rhs) { return *this;}
        if(rhs.data != nullptr) {
            if(data != nullptr) {
                *data = *rhs.data;
            }else {
                data = new Point(*rhs.data);
            }
        }else{
            delete data;
            data = nullptr;
        }
        std::cout << "copy assignment" << std::endl;
        return *this;
    }
    ~Widget(){
        delete data;
        std::cout << "destructor" << std::endl;
    }
};

class BigClass{
    Widget w; 
    int data;
    std::vector<int> v;
public : 
    BigClass(){}
    ~BigClass(){
        std::cout << "big class destructor" << std::endl;
    }
    BigClass(BigClass&&  rhs) noexcept = default;
    BigClass& operator=(BigClass&& rhs) noexcept = default;
    BigClass(const BigClass&  rhs) noexcept = default;
    BigClass& operator=(const BigClass& rhs) noexcept = default;
};

Widget createWidget(){
    Widget w(100, 200);
    return w;
}

BigClass creatBig(){
    BigClass bc;
    return bc;
}

int main(){
    // Widget w1(10, 20);
    // Widget w2 = w1;
    // w1 = w2;
    // w1 = std::move(w2);
    // // w2 = createWidget();
    // std::cout << "------------" << std::endl;
    // Widget w3(createWidget());
    // std::cout << "-----0-0------" << std::endl;

    BigClass bc1;
    BigClass bc2 (std::move(bc1));
    std::cout << "-----*-*------" << std::endl;
    

    return 0;
}

