#include <iostream>
using namespace std;

class Widget{
public:	
    Widget(){}
    Widget(const Widget& rhs){ cout<<"copy ctor"<<endl;}	
    Widget(Widget&& rhs){ cout<<"move ctor"<<endl; }	    
    Widget& operator=(Widget&& rhs)	{	
        cout<<"move assignment"<<endl;	
        return *this; 			
    }
	Widget& operator=(const Widget& rhs){
        cout<<"copy assignment"<<endl;
        return *this;
    }	
};

void process(const Widget& param)
{
    cout<<"process left value"<<endl;
} 
void process(const Widget&& param)
{
    cout<<"process right value"<<endl;
}



// void logAndProcess(Widget&& param){ 
//         cout<<"right hello"<<endl;
//         //...
//         process(std::move(param)); 
// }

// void logAndProcess(Widget& param){ 
//         cout<<"left hello"<<endl;
//         //...
//         process(param);  
// }


template<typename T>
void logAndProcess( T&& param){ 
        cout<<"left or right? "<<endl;
        process(std::forward(param));  
}

/*
template<typename T>
void logAndProcess(T& param){ 
        cout<<"left value"<<endl;
        process(forward<T>(param));  
}*/



/*
template<typename T>
void logAndProcess(const T&& param){ 
        cout<<"right! "<<endl;
        process(std::move(param));  
}*/


// template<typaname T>
// class Vector{

// public:
//     void process(T&& t)
//     {


//     }
// }

//  Vector<int> v;
//  v.procees(100);

void process(const Widget w);

int main()
{
    Widget w;

    //process(w);//Widget&

    Widget&& wr=...;
    
    auto&& w1=w;//w：Widget& , w1: Widget& &&--> Widget&
    auto& w2=w;// w: Widget&, w2: Widget& & --> Widget&

    auto&& w3=wr; // Widget&& && ---> Widget&&
    auto& w4=wr; //  Widget&& & ---> Widget&

    //logAndProcess(w); //w：Widget& ,  param: Widget& &&-> Widget& 左值
    logAndProcess(std::move(w)); // std::move(w): Widget&&, param: Widget&& &&-> Widget&& 右值

  

}         


// template<typename T>                   
// T&& forward(T&& param){
//     if (is_lvalue_reference<T>::value) { 
//         return param;                      
//     } else {       
//         return move(param);               
//     }
// }
