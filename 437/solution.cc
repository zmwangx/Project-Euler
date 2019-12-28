#include <iostream>
#include <vector>

#include <ulong_extras.h>

const long LIMIT = 100'000'000;

std::vector<long> pp(LIMIT + 1, 0);
std::vector<long> primes;

void sieve()
{
    for (long n = 2; n <= LIMIT; ++n) {
        if (pp[n]) {
            continue;
        }
        primes.push_back(n);
        for (long m = n; m <= LIMIT; m += n) {
            pp[m] = n;
        }
    }
}

inline bool is_primitive_root(long x, long p)
{
    long phi = p - 1;
    long m = phi;
    long q;
    double pre = n_precompute_inverse(p);
    while ((q = pp[m])) {
        long exp = phi / q;
        if (n_powmod_ui_precomp(x, exp, p, pre) == 1) {
            return false;
        }
        while (m % q == 0) {
            m /= q;
        }
    }
    return true;
}

int main()
{
    sieve();
    // Add 5 beforehand so we can ignore the special case later.
    long long sum = 5;
    for (auto p : primes) {
        long r5 = p % 5;
        if (r5 != 1 && r5 != 4) {
            continue;
        }
        long inv2 = (p + 1) / 2;
        long sqrt5 = n_sqrtmod(5, p);
        long x1 = (1 + sqrt5) * inv2 % p;
        long x2 = (p + 1 - sqrt5) * inv2 % p;
        if (is_primitive_root(x1, p) || is_primitive_root(x2, p)) {
            sum += p;
        }
    }
    std::cout << sum << std::endl;
}
