struct Item {
    //...
};

struct Cache {

    shared_ptr<Item> getItem(int id) {

        std::shared_ptr<Item> ret;  
        auto itr = itemsById.find(id);   
        if(itr != itemsById.end()) {
            ret = itr->second.lock();//将弱引用指针转为共享指针
        }

        if(ret==nullptr) {
            ret = std::make_shared<Item>(); //插入新的共享指针     
            itemsById[id] = ret; 
        }
 
        return ret;
    }

    std::map<int, std::weak_ptr<Item>> itemsById; //Cache结构
};


struct Client {
    
    std::shared_ptr<Item> item;
};    