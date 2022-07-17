// g++ -O2 -std=c++17 -pthread 30_par_reduce.cpp -ltbb
//

#include <chrono>     // std::chrono::duration/high_resolution_clock
#include <execution>  // std::execution::par
#include <iostream>   // std::cout
#include <numeric>    // std::accumulate/reduce
#include <thread>     // std::thread
#include <vector>     // std::vector

using namespace std;

int main()
{
    vector<double> v(10000000, 0.0625);

    {
        auto t1 = chrono::high_resolution_clock::now();
        double result = accumulate(v.begin(), v.end(), 0.0);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> ms = t2 - t1;
        cout << "accumulate:    result " << result << " took " << ms.count()
             << " ms\n";
    }

    {
        auto t1 = chrono::high_resolution_clock::now();
        unsigned num_threads = thread::hardware_concurrency();
        size_t step = (v.size() + num_threads - 1) / num_threads;
        vector<double> partial_results(num_threads);

        auto worker = [&v, &partial_results, step](unsigned id) {
            size_t i_beg = std::min(step * id, v.size());
            size_t i_end = std::min(step * id + step, v.size());
            partial_results[id] =
                accumulate(v.begin() + i_beg, v.begin() + i_end, 0.0);
        };
        vector<thread> threads;
        for (unsigned i = 0; i < num_threads; ++i) {
            threads.emplace_back(worker, i);
        }
        for (auto& thread : threads) {
            thread.join();
        }

        double result =
            accumulate(partial_results.begin(), partial_results.end(), 0.0);

        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> ms = t2 - t1;
        cout << "MT accumulate: result " << result << " took " << ms.count()
             << " ms\n";
    }

    {
        auto t1 = chrono::high_resolution_clock::now();
        double result = reduce(execution::par, v.begin(), v.end());
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> ms = t2 - t1;
        cout << "reduce:        result " << result << " took " << ms.count()
             << " ms\n";
    }
}
