#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

class Shape {

};

class Rectangle : public Shape{

};


int main()
{
    Shape* ps{new Rectangle()};

    vector<Shape>* v0{ new vector<Shape>()};


    vector<Shape>* v1{ new vector<Rectangle>()};

    vector<Shape> v2{ vector<Rectangle>()};

    vector<Shape*> v3{ vector<Rectangle*>()};



}