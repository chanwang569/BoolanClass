// g++ -O2 -std=c++17 -I../common 25_atomic_overhead.cpp
//

#include <atomic>    // std::atomic
#include <iostream>  // std::cout
#include "rdtsc.h"   // rdtsc

volatile int n;
std::atomic<int> a;

#define LOOPS 1000000

int main()
{
    {
        auto t1 = rdtsc();
        for (int i = 0; i < LOOPS; ++i) {
            ++n;
        }
        auto t2 = rdtsc();
        std::cout << "volatile increment: " << (t2 - t1) / LOOPS
                  << " cycles\n";
    }
    {
        auto t1 = rdtsc();
        for (int i = 0; i < LOOPS; ++i) {
            ++a;
        }
        auto t2 = rdtsc();
        std::cout << "atomic increment: " << (t2 - t1) / LOOPS
                  << " cycles\n";
    }
}
