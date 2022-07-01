#include <iostream>
#include <memory>
using namespace std;


 
struct Event {
 //..
};


class Listener {
public:
 void onEvent(Event e) {
    //处理事件
 }
 //...
};

class Source {
public: 
    void dispatchEvent(Event e) {
      
      for(auto& shareListener: listener){

              shareListener->onEvent(e);
      }
    }

    void registerListener(const std::shared_ptr<Listener>& lp) {
        listener.push_back(lp);
    }
 //...
private: 
    //共享引用
    vector<shared_ptr<Listener>> listener;
};