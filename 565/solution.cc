#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

#include <primesieve.hpp>
#include <ulong_extras.h>

typedef long long ll;

const ll D = 2017;
const ll LIMIT = 100'000'000'000; //100'000'000'000;

inline ll triangular_num(ll n)
{
    return n * (n + 1) / 2;
}

int main()
{
    ll root2 = std::sqrtl(LIMIT);
    ll root3 = std::cbrtl(LIMIT);
    std::vector<ll> small_primes;
    primesieve::generate_primes(root2, &small_primes);
    std::vector<std::pair<ll, ll>> components;
    components.reserve(ll(LIMIT / std::logl(LIMIT) / D * 1.1));
    for (ll p : small_primes) {
        ll r = p % D;
        if (r == 1) {
            continue;
        }

        if (r == D - 1) {
            components.push_back({ p, p });
            if (p <= root3) {
                components.push_back({ p * p * p, p });
            }
            continue;
        }

        ll p3 = p * p * p;
        if (p3 % D == 1) {
            components.push_back({ p * p, p });
            continue;
        }

        if (p >= root3) {
            continue;
        }

        ll p4 = p * p * p * p;
        if (p4 % D == 1) {
            components.push_back({ p3, p });
            continue;
        }
    }
    ll n = (root2 / D + 1) * D;
    if (n % 2 == 1) {
        n += D;
    }
    while (n <= LIMIT) {
        if (n_is_probabprime(n - 1)) {
            components.push_back({ n - 1, n - 1 });
        }
        n += D * 2;
    }
    std::sort(components.begin(), components.end());
    // for (auto [p, m] : components) {
    //     std::cout << p << " " << m << std::endl;
    // }
    // std::cout << components.size() << std::endl;
    ll sum = 0;
    for (auto [m, p] : components) {
        sum += m * triangular_num(LIMIT / m) - m * p * triangular_num(LIMIT / m / p);
    }
    for (size_t i = 0; i < components.size(); ++i) {
        auto [m1, p1] = components[i];
        if (m1 >= root2) {
            break;
        }
        for (size_t j = i + 1; j < components.size(); ++j) {
            auto [m2, p2] = components[j];
            if (p1 == p2) {
                continue;
            }
            ll m = m1 * m2;
            if (m > LIMIT) {
                break;
            }
            assert(p1 * m > LIMIT);
            assert(p2 * m > LIMIT);
            sum -= m * triangular_num(LIMIT / m);
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
