#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename Container, typename Func>
void foreach (Container c, Func op)
{
    for(auto& data : c)
    {
        op(data);
    }                    
}

struct Printer {

    int _n;
    Printer(int n):_n(n){

    }

    void operator() (int data) const {  
        for(int i=0;i<_n;i++)
        {
            cout  << data << ",";
        }
    }
};

struct Comparer {
    bool operator() (int  x, int y) { 
        return x > y; 
    }
};



template <class _RandomAccessIterator, class _Compare>
void sort(  _RandomAccessIterator __first, 
            _RandomAccessIterator __last, 
            _Compare __comp)
{
    //...
}

int main()
{
    //容器
    vector<int> v = { 1,2,3,4,5 };
  
    Printer p(2);
    p(100);// p.operator(100)

    Comparer c;
    bool a=c(90,50);

                                     
    // 算法 _RandomAccessIterator
    sort(v.begin(),v.end(), Comparer());  
  
    



    // // 函数对象
    // foreach(v, Printer());
    // cout<<endl;

   
  
    
}
