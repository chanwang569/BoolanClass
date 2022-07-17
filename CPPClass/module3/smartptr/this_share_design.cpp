#include <memory>
#include <iostream>

using namespace std;




class Widget;

void process(const std::shared_ptr<Widget> tp);


//1. 必须公有继承，确保Widget可转型为enable_shared_from_this
//2. 必须使用Shared指针，调用 shared_from_this()
//   安全做法：将构造函数private禁止创建栈对象、使用静态工厂函数确保创建shared指针
class Widget : public std::enable_shared_from_this<Widget> {
public:
    
    std::shared_ptr<Widget> getWidget() {

        // if(weak_from_this().expired())
        // {
        //     cout<<"oops, expired..."<<endl;
        // }
         return shared_from_this(); // OK

         //return shared_ptr<Widget>(this);
    }

    void invoke(){
        process(shared_from_this());
        //process(shared_ptr<Widget>(this));错误！
    }


    void print(){
        cout<<"print"<<endl;
    }

    ~Widget()
    {
        cout<<"~Widget()"<<endl;
    }

    //工厂函数
    static std::shared_ptr<Widget> create() {
        return std::shared_ptr<Widget>(new Widget());
    }

private:
    Widget()=default;
};

void process(const std::shared_ptr<Widget> tp)
{
    tp->print();
    cout<<"ref count: "<<tp.use_count()<<endl;
    cout<<"process--------"<<endl;
}



int main() {
    {
        //  Widget* p=new Widget();
        //  shared_ptr<Widget> sp1 {p};

        //  auto sp2 = sp1->getWidget(); //sp2 is a copy of sp1
        //shared_ptr<Widget> sp2 {p};
        // process(sp1);
        // cout<<"ref count: "<<sp1.use_count()<<endl;
        // cout<<"ref count: "<<sp2.use_count()<<endl;

    }

    {
        //  Widget w1;
        //  shared_ptr<Widget> w2=w1.getWidget();// &w1
        //  cout<<"ref count: "<<w2.use_count()<<endl;

        //  Widget* p=new Widget();// w1;
        //  shared_ptr<Widget> w2=p->getWidget();// &w1
        //  delete p;
    }
    {

         shared_ptr<Widget> sp1=Widget::create();

        
         //auto sp2=sp1->getWidget();
         cout<<"ref count: "<<sp1.use_count()<<endl;
         cout<<"ref count: "<<sp2.use_count()<<endl;

         cout<< sizeof(Widget)<<endl;

    }

}






/*
template<class T>
class enable_shared_from_this {
     weak_ptr<T> weak_this;
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
