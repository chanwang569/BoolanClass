void fun(shared_ptr<Widget> sp1, 
    shared_ptr<Widget> sp2);


// 不好：可能会泄漏
// 异常不安全的，编译器可能会把两个用以创建函数的两个参数的表达式重新排序。 
// 可能会首先为两个对象先进行内存分配，然后再试图调用二者的 Widget 构造函数。
// 一旦其中一个构造函数调用抛出了异常，那么另一个对象的内存可能永远不会被释放了！

fun(shared_ptr<Widget>(new Widget(a, b)), 
    shared_ptr<Widget>(new Widget(c, d)));

p1=new Widget(a, b)
p2=new Widget(c, d)
shared_ptr<Widget>(p1)
shared_ptr<Widget>(p2)


// 好多了，但不太干净
shared_ptr<Widget> sp1(new Widget(a, b)); 
shared_ptr<Widget> sp2(new Widget(a, b));
fun(sp1, sp2);


// 性能最好，也很干净
fun(make_shared<Widget>(a, b), make_shared<Widget>(c, d));
