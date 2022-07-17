#include<iostream>

using namespace std;

class MyClass
{
    int data = 0;
 
    void f()
    {
        int number = 0;
 
        auto lambda1 = [=] { cout<<number;  data++; }; // i 是拷贝，this 指针拷贝（x引用）
        number = 1; 
        data = 1; 
        lambda1();          
 
        auto lambda2 = [number, this]{ 
            cout<<number;  data++;  }; // 显式声明
        number = 2; 
        data = 2; 
        lambda2();          
 
        auto lambda3 = [&]{ number++;  data++;  }; // i是引用，this 拷贝
        number = 3; 
        data = 3; 
        lambda3();          
 
        auto lambda4 = [&number, this]{ 
            number++;  
            data++;  }; // i是拷贝，this 捕获 

        number = 4; 
        data = 4; 
        lambda4();          
    }
};