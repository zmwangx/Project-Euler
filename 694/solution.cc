#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <utility>
#include <vector>

#include <primesieve.hpp>

typedef unsigned long long ulong;

const ulong N = 1'000'000'000'000'000'000;

ulong icbrt(ulong n)
{
    ulong root = std::cbrt(N);
    while (root * root * root <= N) {
        root++;
    }
    root--;
    while (root * root * root > N) {
        root--;
    }
    return root;
}

int main()
{
    int cuberoot = icbrt(N);
    std::vector<ulong> primes;
    primesieve::generate_primes(cuberoot, &primes);
    std::vector<std::vector<ulong>> factors(cuberoot + 1, std::vector<ulong>());
    for (auto p : primes) {
        for (ulong i = p; i <= cuberoot; i += p) {
            factors[i].push_back(p);
        }
    }
    ulong sum = N;
    for (ulong i = 2; i <= cuberoot; ++i) {
        ulong d = i * i * i;
        ulong nd = N / d;
        ulong omega = factors[i].size();
        // A deque with elements (index, product), where index is the index of
        // the next prime factor and product is the current product.
        std::deque<std::tuple<ulong, ulong>> q;
        q.push_back(std::make_tuple(0, 1));
        while (!q.empty()) {
            ulong index, product;
            std::tie(index, product) = q.front();
            q.pop_front();
            if (index == omega) {
                sum += nd / product;
                continue;
            }
            q.push_back(std::make_tuple(index + 1, product));
            ulong exponent = 0;
            ulong p = factors[i][index];
            while ((++exponent) < 3 && (product *= p) <= nd) {
                q.push_back(std::make_tuple(index + 1, product));
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
