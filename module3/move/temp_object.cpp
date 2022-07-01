#include <iostream>
using namespace std;


class Point{
public:
    int m_x;
    int m_y;

    Point():m_x(0),m_y(0){
        cout<<"Point()"<<endl;
    }

    Point(int x, int y):m_x(x), m_y(y)
    {
        cout<<"Point(int x, int y)"<<endl;
    }

    Point(const Point& p):m_x(p.m_x),m_y(p.m_y)
    {
        cout<<"Point(const Point& p)"<<endl;
    }

    Point& operator=(const Point& p)
    {
        if(this==&p) return *this;

        this->m_x=p.m_x;
        this->m_y=p.m_y;
        cout<<"operator=(const Point& p)"<<endl;

        return *this;
    }

    void print() const
    {
        cout<<"["<<m_x<<","<<m_y<<"]"<<endl;
    }
    ~Point()
    {
        cout<<"~Point()"<<endl;
    }
};


Point process()
{
    Point p(100,200);
    return p;
}

void fooi(int data)
{
    cout<<"foo(int data):" <<data<<endl;
}

void foos(string data)
{
    cout<<"foo(string data):" <<data<<endl;
}

void foop(Point&& data)
{
    cout<<"foo(Point data):"<<data.m_x<<","<<data.m_y <<endl;
}

int processi()
{
    return 100;
}

int main()
{
    //string s;
    //string()="cpp hello";

    Point p{100,200};
    Point()=p;

    process()=p;



    foop(Point());

    // Point&& p=process();
    // Point p2(10,20);
    // p.print();

    //Point p2;
  

    //const Point&& r=(Point());
    //r.print();
    //Point& r2=(Point()={100,200});
    //r2.print();

    //const int& dr=(int()=3);
    //int& dr=(int()=3);
    //int()=3;
    //char()='a';
}