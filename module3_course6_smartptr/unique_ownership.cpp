#include <iostream>
#include <memory>
 
using namespace std;


class Widget{
    int m_x;
    int m_y;
    int m_z;

public:
    Widget(int x=0,int y=0 , int z=0):
        m_x(x), m_y(y),m_z(z)
    {}

    void print() const{
        cout<<m_x<<","<<m_y<<","<<m_z<<endl;
    }

     ~Widget()
    {
        cout<<"Widget dtor"<<endl;
    }
};






unique_ptr<Widget> createWidget()
{
    unique_ptr<Widget> w(new Widget(0,0,0));

    return w;
}



// 获取 widget 的所有权
void process1(unique_ptr<Widget> w)
{
    w->print();
}


//推荐使用， 仅仅使用这个 widget，不表达任何所有权
void process2(const Widget& w)
{
    w.print();
}


//可行， 仅仅使用这个 widget，不表达任何所有权
void process3(Widget* w)
{
    w->print();
}


// 可行，不常用：打算重新指向别的对象
void process4(unique_ptr<Widget>&); 

// 不推荐： 通常不是想要的
void process5(const unique_ptr<Widget>&); 

int main()
{
    unique_ptr<Widget> w1(new Widget(1,2,3));
    unique_ptr<Widget> w2(new Widget(10,20,30));
    unique_ptr<Widget> w3;

    process1( std::move(w1));//转移所有权
    
    //w1==nullptr;


    process2(*w2);
    
    w3=createWidget();

    process3(w3.get());

}





