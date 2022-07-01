#include <cstdlib>
#include <iostream>
using namespace std;
// Index:1
// A simple version of unique ptr
template <typename T>
class SmartPtr {
public:
    explicit SmartPtr(T* p = nullptr)
        : p_(p) {}

    ~SmartPtr() { 
        delete p_;
    }
    void release() { 
        delete p_;
        p_ = nullptr; 
    }
   
    T* operator->() { return p_; }
    const T* operator->() const { return p_; }

    T& operator*() { return *p_; }
    const T& operator*() const { return *p_; }
	
private:
    T* p_;
    SmartPtr(const SmartPtr&) = delete; 
    SmartPtr& operator=(const SmartPtr&) = delete;
};

class MyClass{
public:
    MyClass(){
        cout<<"MyClass 初始化"<<endl;
    }

    ~MyClass(){
        cout<<"MyClass 析构"<<endl;
    }

};


void process(int data) 
{
    cout<<"process start"<<endl;

    //MyClass mc;

    MyClass* p=new MyClass(); //Using raw pointer is not exception safe. 
    
    //SmartPtr p(new MyClass());

    if(data<0){
        invalid_argument exp("data");
        throw exp;
    }
    
    cout<<"process end"<<endl;
    //delete p;
}

int main() {

    try {

      process(-100);
      
   } catch(invalid_argument& e) {
       cerr<<"invalid arg: " << e.what()<<endl;
   }

}