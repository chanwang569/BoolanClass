// g++ -O2 -std=c++17 -pthread -I../common 01_measure_func_call.cpp ../common/profiler.cpp
//

#include <cctype>        // std::isspace
#include <cstddef>       // std::size_t
#include <functional>    // std::function
#include <memory>        // std::make_unique
#include "fast_mutex.h"  // nvwa::fast_mutex
#include "profiler.h"    // PROFILE_CHECK

enum profiled_functions {
    PF_COUNT_SPACE,
    PF_COUNT_SPACE_NOINLINE,
    PF_COUNT_SPACE_VIRTUAL,
    PF_COUNT_SPACE_STD_FUNCTION,
};

name_mapper name_map[] = {
    {PF_COUNT_SPACE, "count_space"},
    {PF_COUNT_SPACE_NOINLINE, "count_space_noinline"},
    {PF_COUNT_SPACE_VIRTUAL, "count_space_virtual"},
    {PF_COUNT_SPACE_STD_FUNCTION, "count_space_std_function"},
    {-1, NULL}};

class space_checker {
public:
    bool isspace(char ch)
    {
        return std::isspace(ch);
    }
};

class space_checker_noinline {
public:
    bool isspace(char ch);
};

__attribute__((noinline)) bool space_checker_noinline::isspace(char ch)
{
    return std::isspace(ch);
}

class space_checker_interface {
public:
    virtual ~space_checker_interface() = default;
    virtual bool isspace(char ch) = 0;
};

// The purpose of this class is prevent GCC devirtualization optimization
class dummy : public space_checker_interface {
public:
    bool isspace(char ch) override;
};

bool dummy::isspace(char /*ch*/)
{
    return false;
}

class space_checker_virtual : public space_checker_interface {
public:
    bool isspace(char ch) override;
};

bool space_checker_virtual::isspace(char ch)
{
    return std::isspace(ch);
}

std::size_t count_space(const char* str, space_checker& checker)
{
    PROFILE_CHECK(PF_COUNT_SPACE);
    std::size_t count = 0;
    while (*str != '\0') {
        if (checker.isspace(*str)) {
            ++count;
        }
        ++str;
    }
    return count;
}

std::size_t count_space_noinline(const char* str,
                                 space_checker_noinline& checker)
{
    PROFILE_CHECK(PF_COUNT_SPACE_NOINLINE);
    std::size_t count = 0;
    while (*str != '\0') {
        if (checker.isspace(*str)) {
            ++count;
        }
        ++str;
    }
    return count;
}

std::size_t count_space_virtual(const char* str,
                                space_checker_interface& checker)
{
    PROFILE_CHECK(PF_COUNT_SPACE_VIRTUAL);
    std::size_t count = 0;
    while (*str != '\0') {
        if (checker.isspace(*str)) {
            ++count;
        }
        ++str;
    }
    return count;
}

std::size_t count_space_std_function(const char* str,
                                     std::function<bool(char)> checker)
{
    PROFILE_CHECK(PF_COUNT_SPACE_STD_FUNCTION);
    std::size_t count = 0;
    while (*str != '\0') {
        if (checker(*str)) {
            ++count;
        }
        ++str;
    }
    return count;
}

std::size_t result;
nvwa::fast_mutex mutex;
std::unique_ptr<space_checker_interface> virt_checker =
    std::make_unique<space_checker_virtual>();

#define LOOPS 10000

int main()
{
    const char input[] = "Hello world Hello world Hello world Hello world";

    {
        space_checker checker;
        for (int i = 0; i < LOOPS; ++i) {
            nvwa::fast_mutex_autolock guard(mutex);
            result = count_space(input, checker);
        }
    }

    {
        space_checker_noinline checker;
        for (int i = 0; i < LOOPS; ++i) {
            nvwa::fast_mutex_autolock guard(mutex);
            result = count_space_noinline(input, checker);
        }
    }

    {
        for (int i = 0; i < LOOPS; ++i) {
            nvwa::fast_mutex_autolock guard(mutex);
            result = count_space_virtual(input, *virt_checker);
        }
    }

    {
        for (int i = 0; i < LOOPS; ++i) {
            nvwa::fast_mutex_autolock guard(mutex);
            result = count_space_std_function(
                input, [](char ch) { return isspace(ch); });
        }
    }
}
