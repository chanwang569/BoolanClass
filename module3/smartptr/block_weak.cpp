#include <iostream>
#include <memory>
using namespace std;

class MyClass{

public:
    MyClass(int x,int y, int z):x(x),y(y),z(z){}

    long x,y,z;
};

 
 void deleteFunction(MyClass* w) { 
    delete w;
    cout<<"------ deleteFunction delete w"<<endl;
} 
 
int main(){

    {
        cout<<"shared_ptr构造器创建的对象 和 控制块（两块内存）："<<endl;
        MyClass* p{new MyClass{10,20,30}};
        shared_ptr<MyClass> w {p,deleteFunction};
        shared_ptr<MyClass> w2{w};
        shared_ptr<MyClass> w3{w};
        weak_ptr<MyClass> w4{w};
        weak_ptr<MyClass> w5{w};
        weak_ptr<MyClass> w6{w};
        
        
        cout<<"共享引用计数："<<w.use_count()<<endl;
        cout<<"共享引用计数："<<w5.use_count()<<endl;

        cout<<"裸对象地址："<<(long)p<<endl;
        long* pd=(long*) &w;
        cout<<"裸对象地址："<<*pd<<endl;
        
        cout<<"控制块地址："<<*(pd+1)<<endl;

        long* pObject=(long*)*pd;
        long* pBlock= (long*)*(pd+1);
    
        cout<<"虚表地址："<<*(pBlock)<<endl;
        cout<<"共享计数："<<*(pBlock+1)<<endl;
        cout<<"弱引用计数："<<*(pBlock+2)<<endl;
        cout<<"裸对象地址："<<*(pBlock+3)<<endl;
        
        cout<<"x："<<*(pObject)<<endl;
        cout<<"y："<<*(pObject+1)<<endl;
        cout<<"z："<<*(pObject+2)<<endl;
   
    }

    {
        cout<<"make_shared创建的对象 和 控制块（一块内存）："<<endl;
        shared_ptr<MyClass> w =std::make_shared<MyClass>(10,20,30); 
        shared_ptr<MyClass> w2{w};
        shared_ptr<MyClass> w3{w};
        weak_ptr<MyClass> w4{w};
        weak_ptr<MyClass> w5{w};
        weak_ptr<MyClass> w6{w};
        
        
        cout<<"共享引用计数："<<w.use_count()<<endl;
        cout<<"共享引用计数："<<w5.use_count()<<endl;

        long* pd=(long*) &w;
        cout<<"裸对象地址："<<*pd<<endl;
        
        cout<<"控制块地址："<<*(pd+1)<<endl;

        long* pBlock= (long*)*(pd+1);
    
        cout<<"虚表地址："<<*(pBlock)<<endl;
        cout<<"共享计数："<<*(pBlock+1)<<endl;
        cout<<"弱引用计数："<<*(pBlock+2)<<endl;
        cout<<"x："<<*(pBlock+3)<<endl;
        cout<<"y："<<*(pBlock+4)<<endl;
        cout<<"y："<<*(pBlock+5)<<endl;
    
    }
    
}