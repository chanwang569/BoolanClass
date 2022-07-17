#include <iostream>
#include <memory>
#include <map>
#include <string>
using namespace std;

struct Shape
{
  virtual ~Shape() = default;

  virtual void draw() = 0;

 
};

struct Line : Shape
{

  void draw() override
  {
    cout << "draw the line" << endl;
  }

};

struct Rectangle : Shape
{
  void draw() override
  {
    cout << "draw the rectangle" << endl;
  }
};

struct Circle : Shape
{
  void draw() override
  {
    cout << "draw the circle" << endl;
  }

  ~Circle() override{
      cout<<"~Circle"<<endl;
  }
};

int main(){

    unique_ptr<Shape> pShape=make_unique<Circle>();

    pShape->draw();

}