// g++ -O2 -std=c++17 01_prime_copy_if.cpp
//

#include <algorithm>  // std::copy_if
#include <chrono>     // std::chrono::duration/duration_cast/steady_clock
#include <iostream>   // std::cout
#include <iterator>   // std::back_inserter
#include <numeric>    // std::iota
#include <ratio>      // std::milli
#include <vector>     // std::vector

using std::copy_if;
using std::cout;
using std::iota;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::steady_clock;

void sieve_prime(const vector<int>& input, vector<int>& output)
{
    if (input.empty()) {
        return;
    }
    auto first = input.begin();
    int n = *first;
    output.push_back(n);
    ++first;
    vector<int> filtered_result;
    copy_if(first, input.end(), std::back_inserter(filtered_result),
            [n](int x) { return (x % n) != 0; });
    sieve_prime(filtered_result, output);
}

vector<int> get_prime_vector(int n)
{
    vector<int> v(n - 1);         // vector size is n - 1
    iota(v.begin(), v.end(), 2);  // fill with 2..n
    vector<int> result;
    sieve_prime(v, result);
    return result;
}

int main()
{
    int max_prime = 100000;
    auto t1 = steady_clock::now();
    auto primes = get_prime_vector(max_prime);
    auto t2 = steady_clock::now();

    using milliseconds = std::chrono::duration<double, std::milli>;
    cout << "Calculating prime numbers up to " << max_prime << " takes "
         << duration_cast<milliseconds>(t2 - t1).count() << " ms\n";

    cout << "Prime numbers up to 50: ";
    for (const auto& p : primes) {
        if (p > 50) {
            break;
        }
        cout << p << ' ';
    }
    cout << '\n';
}
