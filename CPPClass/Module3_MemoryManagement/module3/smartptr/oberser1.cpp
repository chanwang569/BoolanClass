#include <iostream>
using namespace std;

#include <iostream>
#include <memory>
 
struct Event {  string eventArgs };
class Listener {
public:
 void onEvent(Event e) {
    //处理事件
  }
};

class Source {
public: 
 void dispatchEvent(Event e) {
     for(auto& ls: listener){
        if(listener)
            listener->onEvent(e);
        }
    }
 void registerListener(Listener* lp) {
   listener.push_back(lp);
 }
private:
  vector<Listener*> listener;
};
 