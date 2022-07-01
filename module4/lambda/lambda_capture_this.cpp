
#include <iostream>
#include <vector>

using namespace std;


// struct lambda{
//     Point* this;
//     int data;

//     void operator ()(){
//             this->x++;
//             this->y++;
//             cout<<data;
     
//     };

// };

class Point{
public:
    int x;
    int y;
    int z;
    int w;
    int u;
    void print() const{
        std::cout << x<< ", "<<y<<endl;;
    }

    auto invoke()
    {
        int data=100;

        auto lambda = [=] ()
        {
            this->x++;
            this->y++;
            cout<<data;

            
        };

        return lambda;

    }
};

// void process(int* x)
// {
//     *x=300;

// }

// int d1=100;
// int*p=d1;
// process(p);

int main()
{
	Point p1{100,200};
    auto lambda=p1.invoke();// invoke(&p1);
    lambda();
    cout<<sizeof(lambda)<<endl;
    p1.print();



	
}