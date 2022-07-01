
#include <iostream>
#include <vector>

using namespace std;




class Point{
public:
    int x;
    int y;
    int z;
    int w;
    void print() const{
        std::cout << x<< ", "<<y<<endl;;
    }
};

/*
struct Lambda_Ref{

    Point& p1;
    Point& p2;



/*
struct Lambda_Ref{

    Point& p1;
    Point& p2;

   

    Lambda_Ref( Point& p1, Point& p2):p1(p1),p2(p2)
    {

    }
    void operator()(int n) {
        p1.x+=n;
        p1.y+=n;
        p2.x+=n;
        p2.y+=n;
    }
};*/

/*
struct Lambda_Value{

    Point p1;
    Point p2;

    Lambda_Value(const Point& p1, const Point& p2):p1(p1),p2(p2)
    {

    }
    void operator()(int n) {
        p2.x++;
		p1.print();
        p2.print();

        p3.x++;//全局变量
        p3.y++;

    }
};*/

Point p3{100,200};

int main()
{
	Point p1{100,200};
    Point p2{100,200};
    int data=1;

    auto lambda1 = [=] () mutable
	{
        p2.x++;
		p1.print();
        p2.print();
        
        p3.x++;//全局变量
        p3.y++;

	};

    //Lambda_Value l(p1,p2);
    
    lambda1();
    cout<<"---------"<<endl;
    p1.print();
    p2.print();
    p3.print();

    cout<<sizeof(lambda1)<<endl;




    auto lambda2 = [&] (int n)
	{
		p1.x+=n;
        p1.y+=n;
        p2.x+=n;
        p2.y+=n;
	};

     lambda2(1);
     lambda2(2);
     lambda2(3);
     p1.print();
     p2.print();
     cout<<sizeof(lambda2)<<endl;
    //return lambda2;

    auto lambda3 = [=, &p1] ()
	{
		p1.x++;
        p1.y++;
        p2.print();
	};

     auto lambda4 = [ &, p1] ()
	{
        p1.print();
		p2.x++;
        p2.y++;
        
	};

    auto lambda5 = [p1, auto p=std::move(p2)] () mutable
	{
		p1.x++;
        p1.y++;
        p2.x++;
        p2.y++;
	};
	
    // lambda5();
    // lambda2();

	
}
