#include <iostream>
#include <memory>
 
using namespace std;
#include <memory>
#include <iostream>

/*
template<typename Y, typename Deleter>
shared_ptr(std::unique_ptr<Y,Deleter>&& u);
*/

std::unique_ptr<std::string> foo()
{
    return std::make_unique<std::string>("foo");
}

int main()
{
   
    std::shared_ptr<std::string> sp1 = foo(); 


    auto up = std::make_unique<std::string>("Hello World");

    std::shared_ptr<std::string> sp2 = std::move(up); 
    //std::shared_ptr<std::string> sp3 = up; 

    if(sp2.unique())
        cout<<"only 1 count"<<endl;

}

