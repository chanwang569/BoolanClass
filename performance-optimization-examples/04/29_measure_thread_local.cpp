// g++ -O2 -std=c++17 -pthread -I../common 29_measure_thread_local.cpp ../common/profiler.cpp
//

#include <string>        // std::string
#include "fast_mutex.h"  // nvwa::fast_mutex
#include "profiler.h"    // PROFILE_CHECK

enum profiled_functions {
    PF_SAY_HELLO_TO_GLOBAL,
    PF_SAY_HELLO_TO_THREAD,
};

name_mapper name_map[] = {
    {PF_SAY_HELLO_TO_GLOBAL, "say_hello_to_global"},
    {PF_SAY_HELLO_TO_THREAD, "say_hello_to_thread"},
    {-1, NULL}};

std::string global_result;
thread_local std::string thread_result;

__attribute__((noinline)) void say_hello_to_global(const char* name)
{
    PROFILE_CHECK(PF_SAY_HELLO_TO_GLOBAL);
    std::string temp = "Hi, ";
    temp += name;
    global_result = temp;
}

__attribute__((noinline)) void say_hello_to_thread(const char* name)
{
    PROFILE_CHECK(PF_SAY_HELLO_TO_THREAD);
    std::string temp = "Hi, ";
    temp += name;
    thread_result = temp;
}

#define LOOPS 10000

int main()
{
    global_result.reserve(200);
    thread_result.reserve(200);

    for (int i = 0; i < LOOPS; ++i) {
        say_hello_to_global("Peter");
    }

    for (int i = 0; i < LOOPS; ++i) {
        say_hello_to_thread("Peter");
    }
}
