#include <iostream>
#include <thread>
using namespace std;

#include <iostream>
#include <memory>
 int main() {

    auto sp = std::shared_ptr<std::atomic_int>(new std::atomic_int());

    //Reader
    std::thread r([wp = std::weak_ptr<std::atomic_int>(sp)]() { 
        while(true) {
            if(auto p = wp.lock()) {
                std::cout << p.use_count() <<" 值:"<<*p << "\n";
            } else {
                break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    //Writer
    std::thread w([mp = std::move(sp)]() { 
        for(int i=1; i<=5; i++) {
            *mp = i; 
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    w.join();
    r.join();
    return 0;
}