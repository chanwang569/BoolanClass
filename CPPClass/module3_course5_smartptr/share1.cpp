#include <iostream>
#include <memory>
 
using namespace std;
#include <memory>
#include <iostream>

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
    
    shared_ptr<Widget> p0(new Widget());
    auto p1 = std::make_shared<Widget>();
    
    std::cout << "计数: " << p1.use_count() << "\n"; 
    
    auto p2 = p1;//copy ctor
    std::cout << "计数: " << p2.use_count() << "\n";   
    process(p2); //copy ctor
    std::cout << "计数: " << p2.use_count() << "\n"; 


    std::cout << "计数: " << p1.use_count() << "\n"; 
    p1.reset();
    std::cout << "计数: " << p1.use_count() << "\n"; 

    std::cout << "计数: " << p2.use_count() << "\n"; 

    cout<<sizeof(p2)<<endl;

   

    return 0;
}