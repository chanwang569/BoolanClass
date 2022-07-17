// g++ -O2 -std=c++17 -pthread -I../common 27_mutex_vs_shared_mutex.cpp
//

#include <iostream>         // std::cout
#include <mutex>            // std::mutex
#include <numeric>          // std::accumulate
#include <random>           // std::mt19937/uniform_int_distribution
#include <shared_mutex>     // std::shared_mutex
#include <vector>           // std::vector
#include "rdtsc.h"          // rdtsc
#include "scoped_thread.h"  // scoped_thread

using namespace std;

mutex mtx;
shared_mutex shared_mtx;
std::vector<int> v;
int result;

int counter = 0;

#define LOOPS 10000
#define THRDS 4

std::vector<int> get_initial_vec()
{
    std::vector<int> result;
    for (int i = 0; i < 10000; ++i) {
        result.push_back(i);
    }
    return result;
}

void task_with_mtx_random_lock()
{
    mt19937 engine;
    uniform_int_distribution dist(0, 99);
    for (int i = 0; i < LOOPS ; ++i) {
        if (dist(engine) >= 90) {
            lock_guard guard{mtx};
            v.push_back(v.size());
            ++counter;
        } else {
            lock_guard guard{mtx};
            result = accumulate(v.begin(), v.end(), 0);
            ++counter;
        }
    }
}

void task_with_shared_mtx_random_lock()
{
    mt19937 engine;
    uniform_int_distribution dist(0, 99);
    for (int i = 0; i < LOOPS ; ++i) {
        if (dist(engine) >= 90) {
            unique_lock guard{shared_mtx};
            v.push_back(v.size());
            ++counter;
        } else {
            shared_lock guard{shared_mtx};
            result = accumulate(v.begin(), v.end(), 0);
            ++counter;
        }
    }
}

void test(const char* fn_name, void (*fn)())
{
    counter = 0;
    auto t1 = rdtsc();
    {
        std::vector<scoped_thread> threads;
        for (int i = 0; i < THRDS; ++i) {
            threads.emplace_back(fn);
        }
    }
    auto t2 = rdtsc();
    cout << fn_name << " takes " << (t2 - t1) / LOOPS
         << " cycles in each loop\n";
    cout << "Counter: " << counter << '\n';
}

#define TEST(fn) test(#fn, fn)

int main()
{
    v = get_initial_vec();
    TEST(task_with_mtx_random_lock);
    v = get_initial_vec();
    TEST(task_with_shared_mtx_random_lock);
    for(int i = 0; i < static_cast<int>(v.size()); ++i) {
        if (i != v[i]) {
            cout << "Bad result found\n";
            break;
        }
    }
}
