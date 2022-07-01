#include <iostream>
#include <memory>
 
using namespace std;


struct Widget {
    ~Widget()
    {
        cout<<"~Widget()"<<endl;
    }
};

void process( std::shared_ptr<Widget> p3) {
    std::cout << "process 计数: " << p3.use_count() << "\n"; 
}


int main() {

    // Widget* w1=new Widget();
    // Widget* w2=w1;
    // Widget* w3=w1;

    shared_ptr<Widget> p1(new Widget());
    //auto p1 = std::make_shared<Widget>();
    
    std::cout << "计数: " << p1.use_count() << "\n"; 
    
    auto p2 = p1;//copy ctor
    std::cout << "计数: " << p2.use_count() << "\n";  
    std::cout << "计数: " << p1.use_count() << "\n"; 
    process(p2); //copy ctor
    std::cout << "计数: " << p2.use_count() << "\n"; 


    std::cout << "计数: " << p1.use_count() << "\n"; 
    p1.reset();//p1=nullptr;
    std::cout << "计数: " << p1.use_count() << "\n"; 

    std::cout << "计数: " << p2.use_count() << "\n"; 

    cout<<sizeof(p2)<<endl;

   
   shared_ptr<Widget> p5(new Widget());

    return 0;
}