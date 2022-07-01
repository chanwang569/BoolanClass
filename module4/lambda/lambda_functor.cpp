
#include <iostream>
#include <vector>

using namespace std;

class Point{
public:
    double x;
    double y;
    void print() const{
        std::cout << x<< ", "<<y<<endl;;
    }
};



// struct Lambda_Ref{

    // Point& p1;
    // Point& p2;

//     Lambda( Point& p1, Point& p2):p1(p1),p2(p2)
//     {

//     }
//     void operator()(int n) {
//         p1.x+=n;
//         p1.y+=n;
//         p2.x+=n;
//         p2.y+=n;
//     }
// };

// struct Lambda_Value{

//     Point p1;
//     Point p2;

//     Lambda(const Point& p1, const Point& p2):p1(p1),p2(p2)
//     {

//     }
//     void operator()(int n) {
//         p1.x+=n;
//         p1.y+=n;
//         p2.x+=n;
//         p2.y+=n;
//     }
// };


int main()
{
	Point p1{100,200};
    Point p2{100,200};

  

	auto lambda1 = [&] (int n)
	{
		p1.x+=n;
        p1.y+=n;
        p2.x+=n;
        p2.y+=n;
	};

    lambda1(1);
  
    p1.print();
    p2.print();
    cout<<sizeof(lambda1)<<endl;



    auto lambda2 = [=] () 
	{
		p1.print();
        p2.print();

	};

     lambda2();
     p1.print();
     p2.print();
     cout<<sizeof(lambda2)<<endl;
    
	
}
