
#include <iostream>
#include <memory>
#include <vector>

using namespace std;


/*
struct overloaded : Lam1,Lam2,Lam3,Lam4 { 

    using Lam1::operator();
    using Lam2::operator();
    using Lam3::operator();
    using Lam4::operator();
    
};

struct overloaded { 

    operator()(int data){

    }
    operator()(double data){

    }
    operator()(bool data){

    }

    operator()(string data){

    }
};


struct Lam1{
    operator()(int data){

    }
};

struct Lam2{
    operator()(double data){

    }
};

struct Lam3{
    operator()(bool data){

    }
};

struct Lam4{
    operator()(string data){

    }
};


*/



template<class... Ts> 
struct overloaded : Ts... { 
    using Ts::operator()...;  //继承父类所有operator() 操作符
};

template<class... Ts> 
overloaded(Ts...) -> overloaded<Ts...>; //自定义模板推导

int main(){


    std::variant<int,double ,bool, string> numbers;
    numbers="Hello";
    
    auto lams=overloaded{
                        [](int d) { cout <<"int:"<< d; },
                        [](double d) { cout <<"double:"<< d; },
                        [](bool d) { cout <<"bool: "<< d; },  
                        [](string d) { cout <<"string: "<< d; }     
    };
   
     std::visit(lams, numbers);


}