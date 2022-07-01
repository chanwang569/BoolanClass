#include <iostream>
using namespace std;

#include <iostream>
#include <memory>

std::weak_ptr<int> wptr;

void check() {
    std::cout << "wptr 引用计数 " << wptr.use_count() << endl;
    
    if ( !wptr.expired()) {

        std::shared_ptr<int>&& sptr = wptr.lock();

        std::cout << "wptr 引用计数 " << wptr.use_count() << endl;
        std::cout << "sptr 引用计数 " << sptr.use_count() << endl;
        
        
        std::cout << "当前值 " << *sptr << '\n';
    }
    else {
        std::cout << "wptr 已销毁\n";
    }

    std::cout << "wptr 引用计数 " << wptr.use_count() << endl;
        
}
int main() {
    {
        shared_ptr<int> s = std::make_shared<int>(42);
        wptr = s;
        check();
    } // s 销毁
    check();
}

