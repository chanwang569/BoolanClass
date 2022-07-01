#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <utility>

using namespace std;



template<typename Seq, typename Index>
decltype(auto) element(Seq& s, Index i)
{
    return s[i];
}

int main(){

    vector<int> v1{1,2,3,4,5};
    vector<bool> v2={true,false,true,false,true};

    element(v1,3)=100;
    element(v2,3)=true;

    cout<<v1[3]<<endl;
    cout<<v2[3]<<endl;
    

    auto uptr1=make_shared<int>(100);
    
    decltype(auto) uptr3{new int(300)};

    


}