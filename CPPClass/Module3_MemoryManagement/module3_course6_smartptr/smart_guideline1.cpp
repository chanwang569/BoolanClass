//原生指针没有所有权
void f()
{
    // 不好: 原生指针拥有了所有权
    int* p1 = new int{7}; 
    // ...
}

template<typename T>
class X {
    public:
    T* p; // 不好: 不清楚 p 所有权
    T* q; // 不好: 不清楚 q 所有权
    // ...
};

// 不好: 不清楚返回值所有权
Gadget* make_gadget(int n) 
{
    Gadget* p = new Gadget{n};
    // ...
    return p;
}
void caller(int n)
{
    // 要记得 delete p
    Gadget* p = make_gadget(n); 
    // ...
    delete p;
}
