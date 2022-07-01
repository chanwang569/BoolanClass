

#include <memory>
#include <iostream>
using namespace std;

struct Node
{
    int data;
    std::unique_ptr<Node> next;

    ~Node()
    {
        cout<<"dtor: "<<data<<endl;
    }
};

struct List
{

    std::unique_ptr<Node> head;
 
    void push(int data)
    {
        head = std::unique_ptr<Node>(new Node{data, std::move(head)});
    }

    //解开析构函数的递归调用，防止栈溢出
    // ~List()
    // {
    //     while (head)
    //         head = std::move(head->next);
    // }
};

int main()
{
    
    List wall;
    for (int beer = 0; beer != 10; ++beer)
    {
        wall.push(beer);
    }

}