#include <iostream>
using namespace std;
// Index:5 阐述如何处理类中使用其他成员的处理， 如果继承父类也用同样的处理方式
class MyClass
{
public:
    MyClass() {}

    MyClass(const MyClass &rhs)
    {
        cout << "MyClass copy ctor" << endl;
    }
    MyClass(MyClass &&rhs)
    {
        cout << "MyClass move ctor" << endl;
    }

    MyClass &operator=(const MyClass &rhs)
    {
        cout << "MyClass copy assignment" << endl;
        return *this;
    }

    MyClass &operator=(MyClass &&rhs)
    {
        cout << "MyClass move assignment" << endl;
        return *this;
    }
};

class Point
{
    int m_x;
    int m_y;

public:
    Point(int x, int y) : m_x(x), m_y(y)
    {
    }
};

class Widget : public MyClass
{
    Point *data;
    int value;

public:
    Widget(int x = 0, int y = 0) : data(new Point(x, y))
    {
        cout << "ctor" << endl;
    }
    Widget(const Widget &rhs) : value(rhs.value), MyClass(rhs)
    {
        if (rhs.data != nullptr)
        {
            data = new Point(*rhs.data);
        }
        else
        {
            data = nullptr;
        }
        cout << "copy ctor" << endl;
    }

    Widget(Widget &&rhs) :                          // 1. 窃取源对象的指针值
                           MyClass(std::move(rhs)), // move ctor *** 这是必要的，不然会调用copy构造
                           // rhs在函数使用内部已经变成了左值了，所以要move
                           data(rhs.data),
                           value(rhs.value)
    {

        rhs.data = nullptr; // 2. 将源对象的值设为无效状态
        cout << "move ctor" << endl;
    }

    Widget &operator=(Widget &&rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        value = rhs.value;
        // mc=std::move(rhs.mc);//move assignment
        MyClass::operator=(std::move(rhs));

        delete this->data;  // 1. 删除当前值
        data = rhs.data;    // 2. 窃取源对象的值
        rhs.data = nullptr; // 3. 将源对象的值设为有效状态

        cout << "move assignment" << endl;
        return *this;
    }

    Widget &operator=(const Widget &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        if (rhs.data != nullptr)
        {
            if (data != nullptr)
            {
                *data = *rhs.data;
            }
            else
            {
                data = new Point(*rhs.data);
            }
        }
        else
        {
            delete data;
            data = nullptr;
        }

        cout << "copy assignment" << endl;
        return *this;
    }

    ~Widget()
    {
        delete data;
        cout << "dtor" << endl;
    }
};

Widget createWidget()
{
    Widget w(10, 20);
    return w;
}

int main()
{

    Widget w1;
    w1 = createWidget();

    Widget w2(std::move(w1));
}
