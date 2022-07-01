#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <forward_list>

using namespace std;

//可支持编译器、也可支持运行时
constexpr bool isPrime (unsigned int p)
{
    //cout<<"hello"<<endl;

    for (unsigned int d=2; d<=p/2; ++d) {
        if (p % d == 0) {
            return false; 
        }
    }


    return p > 1; 
}






int main()
{
    int data=100;
    bool b1=isPrime(data);
    //constexpr bool b2=isPrime(197);

    //cout<<b2<<endl;
    cout<<b1<<endl;
    
    // bool b3=isPrime(197);
    // cout<<b3<<endl;

}

