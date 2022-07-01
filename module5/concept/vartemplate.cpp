#include <iostream>
using namespace std;



void process1 ()
{
    cout<<endl;
}

template<typename T, typename... TT>
void process1 (T firstArg, TT... args)
{
  cout << firstArg << ' ';  
  process1(args...);          
}


/*
void process1 (int firstArg , string , int, double)
{
  cout << firstArg << ' ';  
  process1(args...);          
}

void process1 (string firstArg , int, double)
{
  cout << firstArg << ' ';  
  process1(args...);          
}

void process1 (int firstArg, double)
{
  cout << firstArg << ' ';  
  process1(args...);          
}

void process1 (double firstArg)
{
  cout << firstArg << ' ';  
  process1();          
}*/



template<typename T>
void process2 (T arg) // 接受一个参数
{
  std::cout << arg << ' ';  
}


template<typename T, typename... Types>
void process2 (T firstArg, Types... args)
{
  
  process2(firstArg);  
  cout<<sizeof...(Types)<<": ";       
  process2(args...);           
}


template<typename... T>
auto accumulate (T... s) {
  return (... + s); // s1+...+ s2
}

template<typename... Types>
void process3 (Types const&... args)
{
  (std::cout << ... << args)<<" " << '\n';
}

int main()
{

  process1(100,"Hello",300,24.34);

  process2(100,"Hello",300,3023.42242);
  
   cout<<endl<<accumulate(1,3,5,7,9)<<endl;
   //cout<<endl<<accumulate()<<endl;
  
  process3(100,"Hello",300,3023.42242);
}
