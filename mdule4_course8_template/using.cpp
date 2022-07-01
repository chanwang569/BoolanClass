#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

//template<typename T, typename Alloca=alloctor<T>> vector;

using svector=vector<string>; //指定所有参数，完整类型 // 注：类型别名

template<typename T>
using SmallVec=vector<T, SmallAlloca<T>>;//指定部分参数，模板类型 //注：模版别名

void process(){

    svector s{"hello"s, "boolan"s, "cpp"s, "camp"s};

    SmallVec<int> si{1,2,3,4,5};

}

template <typename T>
class Array {
private:
	T* ptr;
	int size;

public:
    using value_type=T;
    using iterator=Array_Iter<T>;
};

int data;
Array<int>::value_type data;



