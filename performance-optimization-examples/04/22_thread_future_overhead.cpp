// g++ -O2 -std=c++17 -pthread -I../common 22_thread_future_overhead.cpp
//

#include <future>    // std::async
#include <iostream>  // std::cout
#include <thread>    // std::thread
#include "rdtsc.h"   // rdtsc

#define LOOPS 10000

int main()
{
    {
        auto t1 = rdtsc();
        for (int i = 0; i < LOOPS; ++i) {
            std::thread([] {}).join();
        }
        auto t2 = rdtsc();
        std::cout << (t2 - t1) / LOOPS << " cycles for each thread\n";
    }
    {
        auto t1 = rdtsc();
        for (int i = 0; i < LOOPS; ++i) {
            std::async(std::launch::async, [] {}).wait();
        }
        auto t2 = rdtsc();
        std::cout << (t2 - t1) / LOOPS << " cycles for each async future\n";
    }
    {
        auto t1 = rdtsc();
        for (int i = 0; i < LOOPS; ++i) {
            std::async(std::launch::deferred, [] {}).wait();
        }
        auto t2 = rdtsc();
        std::cout << (t2 - t1) / LOOPS << " cycles for each deferred future\n";
    }
}
