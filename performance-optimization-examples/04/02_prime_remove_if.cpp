// g++ -O2 -std=c++17 02_prime_remove_if.cpp
//

#include <algorithm>  // std::remove_if
#include <chrono>     // std::chrono::duration/duration_cast/steady_clock
#include <iostream>   // std::cout
#include <numeric>    // std::iota
#include <ratio>      // std::milli
#include <vector>     // std::vector

using std::cout;
using std::iota;
using std::remove_if;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::steady_clock;

vector<int>::iterator sieve_prime(vector<int>::iterator first,
                                  vector<int>::iterator last)
{
    if (first == last) {
        return last;
    }
    int n = *first;
    ++first;
    last = remove_if(first, last, [n](int x) { return (x % n) == 0; });
    return sieve_prime(first, last);
}

vector<int> get_prime_vector(int n)
{
    vector<int> v(n - 1);         // vector size is n - 1
    iota(v.begin(), v.end(), 2);  // fill with 2..n
    auto last = sieve_prime(v.begin(), v.end());
    v.erase(last, v.end());
    return v;
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
