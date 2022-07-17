// 全局（静态或堆）对象，或者有别名的局部对象 ...
shared_ptr<widget> g_p = ...;

void f(widget& w){
    g();
    use(w); 
}

void g() {
   // 如是最后一个shared_ptr，会销毁widget
    g_p = ...; 
}

void process() {
    // 不好: 传递从非局部智能指针中获得的指针或引用
    f(*g_p);

    // 不好: 将其作为“this”指针传递
    g_p->func();
}


//改进的版本
void process()
{
    // 正确的做法: 获取该指针的一个局部副本，保持一个引用计数
    shared_ptr<widget> p = g_p;

    // OK: 传递的是从当前函数局部的非别名智能指针中获得的指针或引用
    f(*p);

    // OK: 原因相同
    p->func();
}
