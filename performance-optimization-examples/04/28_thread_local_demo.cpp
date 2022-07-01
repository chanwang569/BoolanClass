// g++ -O2 -std=c++17 -pthread 28_thread_local_demo.cpp
//

#include <iostream>
#include <thread>

using namespace std;

class Obj {
public:
    static Obj& get_instance();
    void op() { cout << "Obj::op()\n"; }

private:
    Obj() { cout << "A new instance is created\n"; }
    ~Obj() { cout << "An instance is destroyed\n"; }
    static thread_local Obj inst_;
};

thread_local Obj Obj::inst_{};

Obj& Obj::get_instance()
{
    return inst_;
}

int main()
{
    cout << "In main\n";
    Obj::get_instance().op();
    Obj::get_instance().op();
    std::thread t{[] {
        cout << "In new thread\n";
        Obj::get_instance().op();
        Obj::get_instance().op();
        cout << "Exiting the new thread\n";
    }};
    t.join();
    cout << "Exiting main\n";
}
