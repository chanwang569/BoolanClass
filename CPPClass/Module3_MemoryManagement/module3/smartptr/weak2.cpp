#include <iostream>
#include <thread>
using namespace std;

#include <iostream>
#include <memory>
 struct Item {
 //...
};

struct Cache {

 auto getItem(int id) {

  std::shared_ptr<Item> ret; 
 
  auto itr = itemsById.find(id);   
  if(itr != itemsById.end()) {
   
   ret = itr->second.lock();
  }

  if(!ret) {
   ret = std::make_shared<Item>();    
   itemsById[id] = ret; 
  }
 
  return ret;
 }

 std::map<int, std::weak_ptr<Item>> itemsById; 
};

   