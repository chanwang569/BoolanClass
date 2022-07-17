#include <memory>
#include <iostream>

using namespace std;



class Widget{
    int m_x;
    int m_y;
    int m_z;

public:
    Widget(int x,int y , int z):
        m_x(x), m_y(y),m_z(z)
    {}

    void print(){
        cout<<m_x<<","<<m_y<<","<<m_z<<endl;
    }

    unique_ptr<Widget> getWidget() {

        //delete this;
        // unique_ptr<Widget>(this); //delete this;
    }

    ~Widget()
    {
        cout<<"Widget dtor"<<endl;
    }
};

// unique_ptr<Widget> getWidget(Widget* this)
// {
//     return unique_ptr<Widget>(this);
// }





int main()
{

    
    {
        // Widget* p=new Widget(1,2,3);
        // unique_ptr<Widget> w1{p};
        // unique_ptr<Widget> w2{p};
    }



    {
         Widget* p=new Widget(1,2,3);

         //Widget w(1,2,3);

         //unique_ptr<Widget> w2{p};
         //w.print();
         unique_ptr<Widget> w3=p->getWidget();// getWidget(p)
         unique_ptr<Widget> w4=p->getWidget();// getWidget(p)

         //delete p;

    }

    {
        Widget* p=new Widget(1,2,3);
        unique_ptr<Widget> w1{p};

        unique_ptr<Widget> w2=w1->getWidget();
        w1.release();
        w2->print();
    }
}





