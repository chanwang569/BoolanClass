// g++ -O3 -std=c++17 01_volatile.cpp
//

#include <stdio.h>   // printf
#include <string.h>  // memset
#include <time.h>    // clock

int main()
{
    constexpr auto LOOPS = 10000000;

    {
        volatile char buffer[80];
        auto t1 = clock();
        for (auto i = 0; i < LOOPS; ++i) {
            memset(const_cast<char*>(buffer), 0, sizeof buffer);
        }
        auto t2 = clock();
        printf("%g\n", (t2 - t1) * 1.0 / CLOCKS_PER_SEC);
    }

    {
        volatile char buffer[80];
        auto t1 = clock();
        for (auto i = 0; i < LOOPS; ++i) {
            for (size_t j = 0; j < sizeof buffer; ++j) {
                buffer[j] = 0;
            }
        }
        auto t2 = clock();
        printf("%g\n", (t2 - t1) * 1.0 / CLOCKS_PER_SEC);
    }
}
