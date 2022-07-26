#include <iostream>
using namespace std;

// Index: 3 解释5大函数的使用场景
// 
class Point{
    int m_x;
    int m_y;
public:
    Point(int x, int y):m_x(x),m_y(y)
    {
    }
};

class Widget {
    Point *data;
    int value;
public:	
    // 构造函数
    Widget(int x, int y):data(new Point(x,y))
    {
        cout<<"ctor"<<endl;
    }

    //拷贝构造
    Widget(const Widget& rhs):value(rhs.value)	
    {
        if(rhs.data!=nullptr)
        {
            data=new Point(*rhs.data);
        }
        else 
        {
            data=nullptr;
        }
        cout<<"copy ctor"<<endl;
    }	

    void process()
    {
        
    }

    //移动构造
    Widget(Widget&& rhs): data(rhs.data),// 1. 窃取源对象的指针值
    	value(rhs.value)//平凡值要拷贝而不能重用
    { 
        rhs.data = nullptr;                 // 2. 将源对象的值设为有效状态
        cout<<"move ctor"<<endl; 
    }	    
   
    //移动赋值运算符
    Widget& operator=(Widget&& rhs)		
    {	
        if(this==&rhs)
        {
            return *this;
        }
        value=rhs.value;
        delete this->data;	    // 1. 删除当前值 			
        data = rhs.data;	    // 2. 窃取源对象的值					
        rhs.data = nullptr;	    // 3. 将源对象的值设为有效状态	

        cout<<"move assignment"<<endl;	
        return *this; 			
    }

	Widget& operator=(const Widget& rhs)	
    {
        if(this== &rhs){
            return *this;
        }

        if(rhs.data!=nullptr){
            if(data!=nullptr){
                *data = *rhs.data; //为啥不需要new？ 这里改的是指针指向的内容，直接将现有指针指向的内容替换为原object中的内容
            }
            else{
                data=new Point(*rhs.data);
            }
        }
        else
        {
            delete data;
            data=nullptr;
        }

        cout<<"copy assignment"<<endl;
        return *this;
    }	


    ~Widget(){
        delete data;
        cout<<"dtor"<<endl;
    }
};


Widget createWidget()
{
    Widget w(100,200);
    return w;
    //return std::move(w);//不必要！
}

void process_c(Widget param)
{

}
class MyClass
{
    Widget w;
    int data;

};

int main()
{

    Widget w1(10,20);
    Widget w2 = w1;		 // 左值源 ⇒ 拷贝构造
    w1 = w2;             // 左值源 ⇒ 拷贝赋值
    cout<<"=========="<<endl;
    w1 = std::move(w2);//移动转型 			          
    
    //w2.process(); //危险！因为w2已经空了～～

     cout<<"**********"<<endl;
    
      w2 = createWidget();	      // 右值源 ⇒ 移动赋值

      cout<<"----------"<<endl;
      Widget w3(createWidget());  // 返回值优化 > 移动 > 拷贝
      //返回值优化的条件比较苛刻：1. 只能构造新object，2临时变量，3，临时变量被返回

      cout<<"&&&&&&&&&&&"<<endl;

     const Widget w4(10,20);
     process_c(w4);//注意这里是值传递，会调用拷贝构造
     process_c(std::move(w4)); //常量对象不可移动，退化成拷贝
}





