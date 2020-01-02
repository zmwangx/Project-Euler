#include <iostream>
#include <utility>
#include <vector>

#include <primesieve.hpp>
#include <ulong_extras.h>

#define LIMIT 300'000

std::vector<int> primes;
std::vector<int> lambda;

inline std::pair<int, int> Aq(int k, int mod)
{
    long long A = 1, q = 2;
    for (int i = 2; i <= k; ++i) {
        (A += lambda[i] * q) %= mod;
        (q *= primes[i - 1]) %= mod;
    }
    return { A, q };
}

void calculate_lamdba()
{
    lambda.push_back(0);
    lambda.push_back(1);
    for (int k = 2; k <= primes.size(); ++k) {
        if (k % 1'000 == 0) {
            std::cerr << "lambda progress: " << k << std::endl;
        }
        int p = primes[k - 1];
        auto [A, q] = Aq(k - 1, p);
        lambda.push_back((long long)(k - A + p) * n_invmod(q, p) % p);
    }
}

inline bool present_in_A(int k, int p)
{
    long long A = 1, q = 2;
    for (int i = 2; i <= k; ++i) {
        (A += lambda[i] * q) %= p;
        (q *= primes[i - 1]) %= p;
        if (A == 0) {
            return true;
        }
    }
    return false;
}

int main()
{
    primesieve::generate_primes(LIMIT, &primes);
    calculate_lamdba();
    long long sum = 0;
    for (int k = 1; k <= primes.size(); ++k) {
        if (k % 1'000 == 0) {
            std::cerr << "test progress: " << k << std::endl;
        }
        int p = primes[k - 1];
        if (present_in_A(k - 1, p)) {
            sum += p;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
