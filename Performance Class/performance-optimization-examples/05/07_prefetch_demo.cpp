// Compare
//
// g++ -O2 -std=c++17 07_prefetch_demo.cpp
// g++ -O2 -std=c++17 -DSEQUENTIAL_ACCESS 07_prefetch_demo.cpp
//
// Adapted from <URL:https://stackoverflow.com/a/50280085/816999>
//

#include <chrono>    // std::chrono::...
#include <iomanip>   // std::setprecision/setw
#include <ios>       // std::left
#include <iostream>  // std::cout
#include <mutex>     // std::mutex
#include <vector>    // std::vector

const int SIZE = 1024 * 1024 * 1;
const int STEP_CNT = 1024 * 1024 * 10;

unsigned int next(unsigned int current)
{
#ifdef SEQUENTIAL_ACCESS
    return (current + 1) % SIZE;
#else
    return (current * 10001 + 328) % SIZE;
#endif
}

template <bool prefetch>
struct Worker {
    std::vector<int> mem;

    double result;
    int oracle_offset;

    void operator()()
    {
        unsigned int prefetch_index = 0;
        for (int i = 0; i < oracle_offset; i++) {
            prefetch_index = next(prefetch_index);
        }

        unsigned int index = 0;
        for (int i = 0; i < STEP_CNT; i++) {
            // prefetch memory block used in a future iteration
            if constexpr (prefetch) {
                __builtin_prefetch(mem.data() + prefetch_index, 0, 1);
            }
            // actual work:
            result += mem[index];

            // prepare next iteration
            prefetch_index = next(prefetch_index);
            index = next(mem[index]);
        }
    }

    Worker(std::vector<int>& mem_)
        : mem(mem_), result(0.0), oracle_offset(0)
    {}
};

double result;
std::mutex mtx;

template <typename Worker>
double timeit(Worker& worker)
{
    std::lock_guard guard{mtx};
    auto begin = std::chrono::high_resolution_clock::now();
    worker();
    result = worker.result;
    worker.result = 0;
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
               .count() /
           1e9;
}

int main()
{
    // set up the data in special way!
    std::vector<int> keys(SIZE);
    for (int i = 0; i < SIZE; i++) {
        keys[i] = i;
    }

    Worker<false> without_prefetch(keys);
    Worker<true> with_prefetch(keys);

    std::cout << "#preloops       time no prefetch    time prefetch     factor\n";
    std::cout << std::setprecision(9) << std::left;

    for (int i = 0; i < 20; i++) {
        // let oracle see i steps in the future:
        without_prefetch.oracle_offset = i;
        with_prefetch.oracle_offset = i;

        // calculate:
        double time_with_prefetch = timeit(with_prefetch);
        double time_no_prefetch = timeit(without_prefetch);

        std::cout << i << "\t\t" << std::setw(20) << time_no_prefetch
                  << std::setw(18) << time_with_prefetch
                  << (time_no_prefetch / time_with_prefetch) << "\n";
    }
}
