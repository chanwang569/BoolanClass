
#ifndef Widget_HPP
#define Widget_HPP

struct Widget {
    int value;
    constexpr Widget() : 
    value{1024} {  

    }
};

constexpr Widget myWidget;   // 全局对象


#endif 

