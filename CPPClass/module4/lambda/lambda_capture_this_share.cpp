#include <functional>
#include <iostream>
#include <vector>

using namespace std;

struct TCPSession: public enable_shared_from_this<TCPSession>{

    int data;

    TCPSession(int d):data(d)
    {

    }

    TCPSession(const TCPSession& rhs):data(rhs.data){
        cout<<"TCPSession copy ctor"<<endl;
    }

    void process() const{
        cout<<"process:"<<data<<endl;

    }

    // auto getLambda3(){
        
    //     

        //所有都是值捕获（*this对象被拷贝）
        auto lam=[ p=*this]() mutable{

            p.process();
            p.data++;
            p.data++;
            cout<<p.data<<endl;
            cout<<p.data<<endl;

        };

        return lam;
    }

    // auto getLambda2(){
        
     

        //所有都是值捕获（*this对象被拷贝）
        auto lam=[*this]() mutable{
            process();
            (*this).data++;
            cout<<(*this).data<<endl;

            // p.process();
            // p.data++;
            // p.data++;
            // cout<<p.data<<endl;
            // cout<<p.data<<endl;

        };

        return lam;
    }

     auto getLambda1(){
        
        
        auto self=shared_from_this();


        auto lam=[this,self]() {

            cout<<this->data<<endl;

        }; 

        return lam;
    }

    ~TCPSession(){
        cout<<"~TCPSession"<<endl;
    }
};


int main(){

    std::function<void(void)> func;
    {
        shared_ptr<TCPSession> tsObj=make_shared<TCPSession>(100);
        
        //TCPSession* tsObj=new TCPSession(201);

        func=tsObj->getLambda1();
        cout<<tsObj->data++<<endl;

        func();

        cout<<tsObj->data++<<endl;
        cout<<"计数3："<<tsObj.use_count()<<endl;
    }
    
    func();


    auto l1=[] <typename T> (T x) { /* ... */ }
    auto l2=[] <typename T> (T* p) { /* ... */ }
    auto l3=[] <typename T, int N> (T (&a)[N]) { /* ... */ }


}