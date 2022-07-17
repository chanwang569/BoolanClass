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

        /*
        T* p=new  T( static_cast<T const&>(*this));
        unique_ptr<Shape> sptr{ p};
        return sptr;*/

        return make_unique<T>( static_cast<T const&>(*this));
    }
};

// Rectangle* p=new Rectangle();
// unique_ptr<Rectangle> p2=make_unique(*p);

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


struct Client{

    void invoke(const Shape& prototype)
    {
        unique_ptr<Shape> ps=prototype.clone();
        
        ps->process();
    }
};


int main(){

    Client client;

    Rectangle r;
    client.invoke(r);

    Circle c;
    client.invoke(c);

    

}