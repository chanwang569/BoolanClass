// g++ -O2 -std=c++17 -fopenmp 31_openmp.cpp
//

#include <chrono>    // std::chrono::duration/high_resolution_clock
#include <iostream>  // std::cout
#include <numeric>   // std::accumulate
#include <vector>    // std::vector
#include <omp.h>     // OpenMP
#include <stddef.h>  // size_t

using namespace std;

int main()
{
    vector<double> v(10000000, 0.0625);
    double result{};
    int tid{};

    {
        auto t1 = chrono::high_resolution_clock::now();
        result = accumulate(v.begin(), v.end(), 0.0);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> ms = t2 - t1;
        cout << "accumulate:    result " << result << " took " << ms.count()
             << " ms\n";
    }

    {
        auto t1 = chrono::high_resolution_clock::now();
        vector<double> partresults(omp_get_max_threads());
#pragma omp parallel private(tid)
        {
            tid = omp_get_thread_num();
#pragma omp for
            for (size_t i = 0; i < v.size(); ++i) {
                partresults[tid] += v[i];
            }
        }

        result = accumulate(partresults.begin(), partresults.end(), 0.0);

        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> ms = t2 - t1;
        cout << "OpenMP add:    result " << result << " took " << ms.count()
             << " ms\n";
    }

    {
        auto t1 = chrono::high_resolution_clock::now();
        double result = 0.0;
#pragma omp parallel for reduction (+ : result)
        for (size_t i = 0; i < v.size(); ++i) {
            result += v[i];
        }

        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> ms = t2 - t1;
        cout << "OpenMP reduce: result " << result << " took " << ms.count()
             << " ms\n";
    }
}
