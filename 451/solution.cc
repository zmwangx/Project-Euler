#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

#include <primesieve.hpp>

typedef long long ll;

const ll N = 20000000; //20'000'000;

std::vector<ll> primes;
std::array<std::vector<ll>, N + 1> factors;

void factor_all()
{
    for (auto p : primes) {
        for (ll n = p; n <= N; n += p) {
            ll ppow = p;
            while (n % ppow == 0) {
                ppow *= p;
            }
            factors[n].push_back(ppow / p);
        }
    }
    for (ll n = 2; n <= N; ++n) {
        std::sort(factors[n].begin(), factors[n].end(), std::greater<int>());
    }
}

inline ll calculate_l(ll n)
{
    auto f = factors[n];
    if (f.size() == 1) {
        if (n % 2 == 0 && n >= 8) {
            return n / 2 + 1;
        } else {
            return 1;
        }
    }

    ll pk1 = f[0], pk2 = f[1];
    ll modulus, r;

    // Find square root of 1 modulo M = (pk1 * pk2) or (pk1 * pk2 / 2) using
    // Chinese Remainder Theorem. In general there should be 4 solutions, \pm 1
    // and \pm r (r \ne 1), where r \equiv 1 pk1 (or pk1 / 2) and r \equiv -1
    // pk2 (or pk2 / 2), except when n is 2 or 4 times an odd prime, in which
    // case the only solutions mod 2pk1 are \pm 1.
    if (pk2 > 2) {
        if (pk1 % 2 == 0) {
            pk1 /= 2;
        }
        if (pk2 % 2 == 0) {
            pk2 /= 2;
        }
        modulus = pk1 * pk2;
        if (pk1 == 2 || pk2 == 2) {
            r = 1;
        } else {
            for (r = pk1 + 1; r < modulus; r += pk1) {
                if (r % pk2 == pk2 - 1) {
                    break;
                }
            }
            assert(r < modulus);
        }
    } else {
        // 2p^v for odd p.
        modulus = pk1 * 2;
        r = 1;
    }

    if (f.size() == 2) {
        if (r > 1) {
            return std::max(n - modulus + r, n - r);
        } else {
            return n - modulus + r;
        }
    }

    ll max_root = 1;

#define ROOT_TEST(rr)           \
    do {                        \
        if (rr <= max_root) {   \
            continue;           \
        }                       \
        if (rr * rr % n == 1) { \
            max_root = rr;      \
        }                       \
    } while (0)

    // Search m \equiv 1 (mod M).
    for (ll rr = modulus + 1; rr < n; rr += modulus) {
        ROOT_TEST(rr);
    }
    // Search m \equiv 1 (mod M).
    for (ll rr = modulus - 1; rr < n - 1; rr += modulus) {
        ROOT_TEST(rr);
    }
    if (r == 1) {
        return max_root;
    }

    // Search m \equiv r (mod M).
    for (ll rr = r; rr < n; rr += modulus) {
        ROOT_TEST(rr);
    }
    // Search m \equiv -r (mod M).
    for (ll rr = modulus - r; rr < n; rr += modulus) {
        ROOT_TEST(rr);
    }

    return max_root;
}

int main()
{
    primesieve::generate_primes(N, &primes);
    factor_all();
    ll sum = 0;
    for (ll i = 3; i <= N; ++i) {
        sum += calculate_l(i);
    }
    std::cout << sum << std::endl;
    // std::cout << calculate_l(1000) << std::endl;
    return 0;
}
