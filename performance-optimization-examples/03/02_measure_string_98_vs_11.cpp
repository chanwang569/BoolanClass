// (cd ../common && g++ -O2 -std=c++11 -pthread -c profiler.cpp)
//
// Then:
//
// g++ -O2 -std=c++98 -pthread -I../common 02_measure_string_98_vs_11.cpp ../common/profiler.o
//
// or
//
// g++ -O2 -std=c++11 -pthread -I../common 02_measure_string_98_vs_11.cpp ../common/profiler.o
//

#include <iostream>      // std::cout/endl
#include <string>        // std::string
#include "fast_mutex.h"  // nvwa::fast_mutex
#include "profiler.h"    // PROFILE_CHECK

enum profiled_functions {
    PF_SAY_HI,
};

name_mapper name_map[] = {
    {PF_SAY_HI, "say_hi"},
    {-1, NULL}};

std::string say_hi(const char* name)
{
    PROFILE_CHECK(PF_SAY_HI);
    return std::string("Hi, ") + name + ". Nice to meet you!";
}

std::string input = "John Smith";
std::string result;
nvwa::fast_mutex mutex;

#define LOOPS 10000

int main()
{
    for (int i = 0; i < LOOPS; ++i) {
        nvwa::fast_mutex_autolock guard(mutex);
        result = say_hi(input.c_str());
    }
    std::cout << result << std::endl;
}
