// g++ -O2 -std=c++17 -pthread -I../common 05_traverse_by_row_vs_column.cpp
//

#include <iostream>  // std::cout/endl
#include <mutex>     // std::mutex
#include <utility>   // std::swap
#include <stddef.h>  // size_t
#include "rdtsc.h"   // rdtsc

constexpr int LOOPS = 1000;
double result;
std::mutex mutex;

template <size_t N>
double sum_by_rows(double (&a)[N][N])
{
    size_t r;
    size_t c;
    double result = 0.0;
    for (r = 1; r < N; ++r) {
        for (c = 0; c < N; ++c) {
            result += a[r][c];
        }
    }
    return result;
}

template <size_t N>
double sum_by_columns(double (&a)[N][N])
{
    size_t r;
    size_t c;
    double result = 0.0;
    for (c = 0; c < N; ++c) {
        for (r = 1; r < N; ++r) {
            result += a[r][c];
        }
    }
    return result;
}

template <size_t N>
void test1()
{
    alignas(64) double matrix[N][N];
    auto t1 = rdtsc();
    for (int i = 0; i < LOOPS; ++i) {
        std::lock_guard<std::mutex> guard{mutex};
        result = sum_by_rows(matrix);
    }
    auto t2 = rdtsc();
    std::cout << N << " (" << sizeof matrix / 1024 << " KB): "
              << (t2 - t1) * 1.0 / ((N - 1) * (N - 1) * LOOPS) << std::endl;
}

template <size_t N>
void test2()
{
    alignas(64) double matrix[N][N];
    auto t1 = rdtsc();
    for (int i = 0; i < LOOPS; ++i) {
        std::lock_guard<std::mutex> guard{mutex};
        result = sum_by_columns(matrix);
    }
    auto t2 = rdtsc();
    std::cout << N << " (" << sizeof matrix / 1024 << " KB): "
              << (t2 - t1) * 1.0 / ((N - 1) * (N - 1) * LOOPS) << std::endl;
}

int main()
{
    test1<64>();
    test1<128>();
    test1<256>();
    test1<512>();
    test1<512>();

    test2<64>();
    test2<128>();
    test2<256>();
    test2<512>();
}
