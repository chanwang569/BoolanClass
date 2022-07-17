#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;


class Shape {
public:
    virtual ~Shape () = default;
    virtual void process()=0;
    virtual unique_ptr<Shape> clone() const = 0;

};


template <typename T>
class CloneShape : public Shape {
public:
    unique_ptr<Shape> clone() const override {
        return make_unique<T>(static_cast<T const&>(*this));
    }
};

class Rectangle : public CloneShape<Rectangle>{
public:
    Rectangle(){}
    Rectangle(const Rectangle& rhs){
        cout<<"Rectangle deep clone"<<endl;
    }

  

    void process() override{
        cout<<"Rectangle process"<<endl;
    }

};

class Circle : public CloneShape<Circle>{
public:
    Circle(){}
    Circle(const Circle& rhs){
        cout<<"Circle deep clone"<<endl;
    }

    void process() override{
        cout<<"Circle process"<<endl;
    }
};

void invoke(const Shape& shape)
{
    unique_ptr<Shape> ps=shape.clone();
    
    ps->process();
}


int main(){

    Rectangle r;
    invoke(r);

    Circle c;
    invoke(c);


}