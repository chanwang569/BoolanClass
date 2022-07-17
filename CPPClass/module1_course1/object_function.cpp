#include <iostream>
using namespace std;

class Point{
public:
    int x;
    int y;//实例变量
    static int data;

    void process()
    {
        cout<<this->x<<endl;
        std::cout<<x<<endl;
        y++;

         sprocess();

         process2(100);
    }

    void process2(int d)
    {

    }

    static void sprocess();
    {
        //x++;
        data++;

       
    }

};

int Point::data=100;

//解释编译器是如何工作的。 主要是看this是怎么处理的。或者说转化为C语言后的形式是如何的。 
/*
struct Point {
    int x;
    int y;
};

void process(Point * this)
{
    cout<<this->x<<endl;
    std::cout<<this->x<<endl;
    this->y++;

    sprocess();

    process2(this, 100);
}

void process2(Point * this, int d)
{
    
}

void sprocess()
{
    //x++;
    Point::data++;
    
}
*/



int main(){

    Point pt;
    pt.process(); // process(&pt); JMP 0x000064
}