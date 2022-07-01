#include <iostream>
using namespace std;

#include <iostream>
#include <memory>
 
struct Event {
 //..
};


class Listener {
public:
 virtual void onEvent(Event e) {
    //处理事件
 }
 //...
};

class Source {
public: 
    void dispatchEvent(Event e) {
      
      for(std::weak_ptr<Listener>& weakListener: listener){

          if(std::shared_ptr<Listener> shareListener = weakListener.lock()) 
          {
            shareListener->onEvent(e);

        }

      listener.erase( std::remove_if( listener.begin(), listener.end(), 
            []( const std::weak_ptr<Listener>& o )
            {
                return o.expired();
            } ), listener.end() );
    
    }

    void registerListener(const std::shared_ptr<Listener>& lp) {
        listener.push_back(lp);
    }
 //...
private: 
    //弱引用
    vector<weak_ptr<Listener>> listener;
};



class Client: public Listener, public enable_shared_from_this<Client>
{

  public void process()
  {
    Source s;

    s.registerListener(shared_from_this());

  }

  void onEvent(Event e) override {
    //处理事件
 }
}