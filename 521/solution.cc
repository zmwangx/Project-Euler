#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>
#include <primesieve.hpp>

typedef boost::multiprecision::int128_t int128_t;

const int64_t N = 1'000'000'000'000;
const int64_t MOD = 1'000'000'000;

inline int128_t sqr(int128_t x)
{
    return x * x;
}

int main()
{
    std::vector<int> primes;
    primesieve::generate_primes(int(sqrt(N)), &primes);
    int nprimes = primes.size();

    int128_t result = 2 * (N / 2) + sqr((N + 1) / 2) - 1;
#pragma omp parallel for schedule(dynamic, 1'000) reduction(- \
                                                            : result)
    for (int64_t m = 3; m <= N / 3; m += 2) {
        for (int j = 1; j < nprimes; ++j) {
            int p = primes[j];
            int128_t n = p * m;
            if (n >= N) {
                break;
            }
            result -= n - p;
            if (m % p == 0) {
                break;
            }
        }
    }
    std::cout << result << " " << result % MOD << std::endl;

    return 0;
}
