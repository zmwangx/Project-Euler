#include <iostream>
#include <numeric>
#include <vector>

#include <primesieve.hpp>

typedef long long ll;

const int PRIME_BOUND = 1E8;
const ll N = 1E11;

inline ll powmod(ll x, ll y, ll p)
{
    int result = 1;
    x %= p;
    while (y) {
        if (y & 1) {
            result = (result * x) % p;
        }
        y >>= 1;
        x = (x * x) % p;
    }
    return result;
}

// Solve n^15 + 1 == 0 mod p.
inline std::vector<int> solve(int p)
{
    if (p == 3 || p == 5) {
        return { p - 1 };
    }
    int gcd = std::gcd(p - 1, 15);
    if (gcd == 1) {
        return { p - 1 };
    }
    int g = 2;
    while (powmod(g, (p - 1) / 3, p) == 1 || powmod(g, (p - 1) / 5, p) == 1) {
        g++;
    }
    int m = powmod(g, (p - 1) / gcd, p);
    std::vector<int> roots;
    for (ll x = p - 1, i = 0; i < gcd; x = (x * m) % p, ++i) {
        roots.push_back(x);
    }
    return roots;
}

int main()
{
    std::vector<int> primes;
    primesieve::generate_primes(PRIME_BOUND, &primes);
    ll sum = 0;
    for (auto p : primes) {
        auto roots = solve(p);
        ll count = roots.size() * (N / p);
        ll remainder = N % p;
        for (auto x : roots) {
            if (x <= remainder) {
                count++;
            }
        }
        sum += count * p;
    }
    std::cout << sum << std::endl;
    return 0;
}
