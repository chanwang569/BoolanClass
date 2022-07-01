// g++ -O2 -std=c++17 -I../common 13_measure_exception.cpp
//

#include <array>     // std::array
#include <iostream>  // std::cout
#include <random>    // std::mt19937/uniform_int_distribution
#include <assert.h>  // assert
#include <stddef.h>  // size_t
#include "rdtsc.h"   // rdtsc

constexpr size_t items = 100000;
constexpr size_t loops = 1000;

std::array<int, items> a;

void init_array(std::array<int, items>& arr)
{
    std::mt19937 e;
    std::uniform_int_distribution<int> dist{1, 10000};
    for (int& n : arr) {
        n = dist(e);
    }
    size_t bad_position =
        std::uniform_int_distribution<size_t>{items - 10, items - 1}(e);
    arr[bad_position] = -1;
}

struct invalid_value {};

int check_errcode(int n, int check_value)
{
    if (n == check_value) {
        return 1;
    } else {
        return 0;
    }
}

void check_throw(int n, int check_value)
{
    if (n == check_value) {
        throw invalid_value();
    }
}

void parse_test_errcode(std::array<int, items>& arr, int check_value)
{
    auto t1 = rdtsc();
    size_t i = 0;
    for (; i < arr.size(); ++i) {
        if (check_errcode(arr[i], check_value)) {
            break;
        }
    }
    auto t2 = rdtsc();
    if (i == arr.size()) {
        std::cout << "No errors encountered\n";
    } else {
        std::cout << "Error encountered at position " << i << '\n';
    }
    std::cout << (t2 - t1) << " cycled elapsed\n\n";
}

void parse_test_exception(std::array<int, items>& arr, int check_value)
{
    auto t1 = rdtsc();
    size_t i = 0;
    try {
        for (; i < arr.size(); ++i) {
            check_throw(arr[i], check_value);
        }
    }
    catch (const invalid_value&) {
    }
    auto t2 = rdtsc();
    if (i == arr.size()) {
        std::cout << "No errors encountered\n";
    } else {
        std::cout << "Exception encountered at position " << i << '\n';
    }
    std::cout << (t2 - t1) << " cycled elapsed\n\n";
}

volatile int some_value = -1;
int result;

void measure_error_check_overhead()
{
    result = 0;
    auto t1 = rdtsc();
    for (size_t i = 0; i < loops; ++i) {
        if (check_errcode(some_value, -1)) {
            ++result;
        }
    }
    auto t2 = rdtsc();
    assert(result == loops);
    std::cout << "Error check cost is "
              << static_cast<double>(t2 - t1) / loops << " cycles\n";
}

void measure_try_overhead()
{
    result = 0;
    auto t1 = rdtsc();
    for (size_t i = 0; i < loops; ++i) {
        try {
            check_throw(some_value, 0);
        }
        catch (const invalid_value&) {
            ++result;
        }
    }
    auto t2 = rdtsc();
    assert(result == 0);
    std::cout << "Try/catch cost is "
              << static_cast<double>(t2 - t1) / loops << " cycles\n";
}

void measure_exception_overhead()
{
    result = 0;
    auto t1 = rdtsc();
    for (size_t i = 0; i < loops; ++i) {
        try {
            check_throw(some_value, -1);
        }
        catch (const invalid_value&) {
            ++result;
        }
    }
    auto t2 = rdtsc();
    assert(result == loops);
    std::cout << "Throwing cost is "
              << static_cast<double>(t2 - t1) / loops << " cycles\n";
}

int main()
{
    init_array(a);

    parse_test_errcode(a, 0);
    parse_test_errcode(a, -1);
    parse_test_exception(a, 0);
    parse_test_exception(a, -1);

    measure_error_check_overhead();
    measure_try_overhead();
    measure_exception_overhead();
}
