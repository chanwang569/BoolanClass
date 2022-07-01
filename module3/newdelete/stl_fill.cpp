#include <iostream>
using namespace std;

class Point{
public:
  Point(int x, int y, int z):x(x),y(y),z(z){ cout<<"ctor"<<endl;}
  ~Point(){ cout<<"dtor"<<endl;}

  void print(){
    cout<<x<<" "<<y<<" "<<z<<endl;
  }

  int x;
  int y;
  int z;
};


int main()
{


    void* memory = std::malloc(sizeof(Point));
    Point* myObject = reinterpret_cast<Point*>(memory);
    std::uninitialized_fill_n(myObject, 1, Point{100,200,300});
    cout<<"----"<<endl;
    std::destroy_at(myObject);
    cout<<"----"<<endl;
    std::free(memory);
}




