#include <memory>
#include <iostream>

using namespace std;

struct Widget {
    int m_number;

    Widget(int number):m_number(number)
    {
        cout<<"Widget()"<<endl;
    }
    Widget(const Widget& w):m_number(w.m_number)
    {
        cout<<"Widget(const Widget& w)"<<endl;
    }
    ~Widget()
    {
        cout<<"~Widget()"<<endl;
    }
};

struct MyClass {

    //Widget* w;

    std::unique_ptr<Widget> m_p;

    MyClass(int data):m_p(new Widget{data})
    {

    }

    MyClass(const MyClass& rhs):
        m_p(new Widget(*rhs.m_p))
    {

    }

    MyClass& operator=(const MyClass& rhs)
    {
        if(this==&rhs) return *this;

        MyClass temp(rhs);
        m_p.swap(temp.m_p);
        return *this;
    }

    MyClass(MyClass&& rhs) noexcept = default;
    MyClass& operator=(MyClass&& rhs) noexcept = default;
    ~MyClass() = default;
};

void process(MyClass c)
{

}

int main()
{
    MyClass a{42};
    MyClass b{std::move(a)}; //a.m_p 为nullptr

   // MyClass c{b};
    //std::cout << (*c.m_p).m_number << std::endl;
    MyClass d{50};
    MyClass c=std::move(d); //d.m_p 为nullptr
    std::cout << (*c.m_p).m_number << std::endl;

    process(d);
}