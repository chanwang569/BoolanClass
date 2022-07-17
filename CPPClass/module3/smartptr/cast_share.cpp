#include <iostream>
#include <memory>
using namespace std;

class Base 
{ 
public:
    int a; 
    virtual void process()  { 
        std::cout << "Base.process()"<<endl;
    }
    virtual ~Base(){

        cout<<"~Base"<<endl;
    }
};
 
class Sub : public Base
{
public:
    void process()  override{ 
        std::cout << "Sub.process()"<<endl; 
    }

    void invoke(){
        std::cout << "Sub.invoke()"<<endl;
    }
    ~Sub(){

        cout<<"~Sub"<<endl;
    }
};
 
int main(){

    {
        // Base* b1=new Base();
        // Sub* s1=new Sub();

        // Base* b2=s1;
        // b2->process();

        // Sub* s3=dynamic_cast<Sub*> (b2);
        // s3->process();

        // delete b1;
        // delete b2; //非虚析构，非多态删除

    }
    cout<<"block 1--------"<<endl;

    {
        // Base* b1=new Base();
         Sub* s1=new Sub();

        // shared_ptr<Base> sp1{b1};
        shared_ptr<Base> sp2{s1};

        shared_ptr<Base> sp3{s1};
        
        // sp3->process();
        // sp3.reset();

    }
    
    cout<<"block 2--------"<<endl;
 
    {

        shared_ptr<Base> sp1{new Base()};
        shared_ptr<Sub> sp2{new Sub()};
        shared_ptr<Base> sp3{sp2};
      
        cout<<sp3.use_count()<<endl;

        //1. 先对原生指针static_cast 2.再拷贝构造一个目标指针的shared_ptr
        shared_ptr<Base> sp4 = std::static_pointer_cast<Base>(sp2); 
        cout<<sp4.use_count()<<endl;

        //shared_ptr<Sub> sp5 {dynamic_cast<Sub*>(sp4.get())};
        //sp5->process();

        shared_ptr<Sub>  sp6 = std::dynamic_pointer_cast<Sub>(sp4);    
        cout <<  sp6.use_count() <<endl;



        shared_ptr<Base> sp2{new Sub()};
        delete ~Sub()

        // unique_ptr<Base> sp2{new Sub(), [](Sub* s){delete s;}};
        // delete ~Base()
    } 



    Widget w(100);

    vector<Widget> v;
    v.emplace_back(w);


    return  v;
    
}
/*

template< class T, class U > 
std::shared_ptr<T> static_pointer_cast( const std::shared_ptr<U>& r ) noexcept
{
    auto p = static_cast<typename std::shared_ptr<T>::element_type*>(r.get());
    return std::shared_ptr<T>{r, p};
}


template< class T, class U > 
std::shared_ptr<T> dynamic_pointer_cast( const std::shared_ptr<U>& r ) noexcept
{
    if (auto p = dynamic_cast<typename std::shared_ptr<T>::element_type*>(r.get())) {
        return std::shared_ptr<T>{r, p};
    } else {
        return std::shared_ptr<T>{};
    }
}



*/