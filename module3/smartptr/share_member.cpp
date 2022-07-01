#include <iostream>
#include <memory>
 
using namespace std;

struct Widget{
    int data;

    ~Widget(){
        cout<<"~Widget()"<<endl;
    }
};

struct SelfCircle{
    shared_ptr<SelfCircle> self;

    SelfCircle(){
        cout<<"SelfCircle()"<<endl;
    }
    ~SelfCircle(){
        cout<<"~SelfCircle()"<<endl;
    }
};

int main()
{
   
    {
        Widget* p=new Widget();
        shared_ptr<Widget> spw(p);
        //shared_ptr<Widget> spw2(p);

        shared_ptr<int> spd(spw, &spw->data); //如何共用计数



         cout<<spd.use_count()<<endl;
         cout<<spw.use_count()<<endl;
         spw.reset();
         cout<<"after reset..."<<endl;
         cout<<spd.use_count()<<endl;
         cout<<spw.use_count()<<endl;


    }

    {
        shared_ptr<SelfCircle> spCircle{new SelfCircle()};
        spCircle->self=spCircle;
        cout<<spCircle.use_count()<<endl;
    }
}


//创建ptr的指针，与r共享所有权
// template< class Y >
// shared_ptr( const shared_ptr<Y>& r, element_type* ptr ) noexcept;
