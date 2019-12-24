#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include <primesieve.hpp>

#define N 100'000'000
#define K 100'000

std::vector<int> primes;
std::array<int, N + 1> d;

int main()
{
    std::fill(d.begin(), d.end(), 1);
    primesieve::generate_primes(N, &primes);
    for (auto p : primes) {
        for (int n = p; n <= N; n += p) {
            int m = n / p;
            int exponent = 1;
            while (m % p == 0) {
                m /= p;
                exponent++;
            }
            d[n] *= 1 + exponent;
        }
    }
    std::vector<int>().swap(primes);

    long long total = 0;
    std::priority_queue<std::pair<int, int>> q;
    for (int n = 1; n < K; ++n) {
        q.push({ d[n], n });
    }
    for (int n = K, lower = 1; n <= N; ++n, ++lower) {
        q.push({ d[n], n });
        while (q.top().second < lower) {
            q.pop();
        }
        total += q.top().first;
    }
    std::cout << total << std::endl;
    return 0;
}
