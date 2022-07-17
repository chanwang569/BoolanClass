#include <memory>
#include <iostream>

using namespace std;


class Widget;

void process(const std::shared_ptr<Widget> tp);

class Widget {

public:
    weak_ptr<Widget> weak_w;

    Widget()
    {
        cout<<"Widget()"<<endl;
    }


    shared_ptr<Widget> getWidget() {

        //return shared_ptr<Widget>(this); 

         if(!weak_w.expired())
            return weak_w.lock();
    }

    void invoke(){

        process(weak_w.lock());
        //process(shared_ptr<Widget>(this)); //如何实现？ 奇异递归模板。 在构造shared_from_this时实现
    }

    void print(){
        cout<<"print"<<endl;
    }

    ~Widget()
    {
        cout<<"~Widget()"<<endl;
    }
 
};

void process( std::shared_ptr<Widget> tp)
{
    tp->print();
    cout<<"ref count: "<<tp.use_count()<<endl;
    cout<<"process--------"<<endl;
}


// shared_ptr<Widget> getWidget(Widget* this) {

//     return shared_ptr<Widget>(this); 
// }



int main() {

    shared_ptr<Widget> sw1;
    {
        Widget* pw=new Widget();
        sw1=shared_ptr<Widget>(pw);//

        //shared_ptr<T>构造器内部会使pw->weak_w
        //指向当前对象共享指针
        //pw->weak_w=sw1;

        shared_ptr<Widget> sw2=sw1->getWidget();// getWidget(pw);
        sw1->invoke();
        //shared_ptr<Widget> sw2{pw};// getWidget(pw);
        //shared_ptr<Widget> sw2{sw1};

        // shared_ptr<Widget> sw3 =sw1->getWidget(); 
        // cout<<"ref count: "<<sw1.use_count()<<endl;
        // sw1->invoke();
        // cout<<"ref count: "<<sw1.use_count()<<endl;
    }
    cout<<"block-----"<<endl;
    cout<<"ref count: "<<sw1.use_count()<<endl;
}





//enable_shared_from_this 底层实现
/*
template<class T>
class enable_shared_from_this {
    mutable weak_ptr<T> weak_this;
public:

    // 如果普通构造，weak_this为nullptr
    // 如果使用shared_ptr构造， weak_this 指向一个shared_ptr<T>(this);
    enable_shared_from_this()
    {

    }

    // 调用时将weak_ptr转为shared_ptr

    shared_ptr<T> shared_from_this() {
        return shared_ptr<T>(weak_this); 
    }
 
    shared_ptr<const T> shared_from_this() const {
        return shared_ptr<const T>(weak_this); 
    }

    template <class U> friend class shared_ptr;
};*/
