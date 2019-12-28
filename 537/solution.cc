#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

#include <primesieve.hpp>

typedef long long ll;

#define N 20000
#define K 20000
#define MOD 1'004'535'809

std::array<std::array<ll, K + 1>, N + 1> t;

ll search(int n, int k)
{
    ll result = t[n][k];
    // Recall that all elements of t were initialized to -1.
    if (result >= 0) {
        return result;
    }
    result = 0;
    int k1 = k / 2, k2 = (k + 1) / 2;
    for (int i = 0; i <= n; ++i) {
        (result += search(i, k1) * search(n - i, k2)) %= MOD;
    }
    t[n][k] = result;
    return result;
}

int main()
{
    std::vector<long> primes;
    primesieve::generate_n_primes(N + 1, &primes);
    std::fill(&t[0][0], &t[0][0] + sizeof(t) / sizeof(long), -1);
    for (int j = 0; j <= N; ++j) {
        t[0][j] = 1;
    }
    for (int i = 1; i <= N; ++i) {
        t[i][1] = primes[i] - primes[i - 1];
    }
    std::cout << search(N, K) << std::endl;
    return 0;
}
