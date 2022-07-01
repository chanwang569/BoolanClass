#include <vector>
#include <iostream>

using namespace std;


void zero(auto& container){
    for(auto&& val: container){
        val={};
    }
}

void print(auto& container){
    for(auto&& val: container){
        cout<<val<<" ";
    }
    cout<<endl;
}


int main()
{
    
    vector<int> vc={1,2,3};
    print(vc);
    zero(vc);
    print(vc);

    vector<bool> vb={true,false,true};
     zero(vb);


     //bool& b=&vb[0];
     print(vb);

  
}

