
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

    ~Widget()
    {
        cout<<"Widget dtor"<<endl;
    }
};


int main()
{

    {
        //unique_ptr<Widget> w1=new Widget(1,2,3); 错误
        unique_ptr<Widget> w1(new Widget(1,2,3));
        w1->print();

        auto w2= unique_ptr<Widget>(new Widget(10,20,30));
        //auto w2=w1;
         auto w2=std::move(w1);
         //if(w1==nullptr) cout<<"w1 is nullptr"<<endl;
        // w2->print();

        //w1.swap(w2);
        //w1->print();
        //w2->print();

        //w2.reset();
        w2.reset(new Widget(11,22,33)); 
        //w2=nullptr; //等价

        if(w2!=nullptr)
        {
            cout<<"w2 is not null"<<endl;
        }
        else 
        {
            cout<<"w2 is null_ptr"<<endl;
        }

    }
    cout<<"----------"<<endl;


    {
        auto w3 = make_unique<Widget>(100,200,300);
        w3->print();

        //auto w4=w3;// 错误

        auto w4=std::move(w3); //OK，w3不能用
       
        unique_ptr<Widget> w5{std::move(w4)};

        Widget* rawp1=w5.get(); 

        //process(w5.get());
        w5->print();
        //delete rawp1;

         Widget* rawp=w5.release();//释放所有权
         if(w5==nullptr) cout<<"w5 is null_ptr"<<endl;
         delete rawp; //必须负责释放d

    }
    
    



    //foo(w1); //错误

    
}
