#include<iostream>
#include<vector>
#include<set>

using namespace std;


template<typename Coll, typename T>
requires std::convertible_to<T, typename Coll::value_type>
void add(Coll& coll, const T& val)
{
    coll.push_back(val);
}

int main(){
    std::vector<int> vec;
    add(vec, 42); 
    //add(vec, "hello"); 


}