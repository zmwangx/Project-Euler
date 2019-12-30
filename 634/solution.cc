#include <cmath>
#include <iostream>
#include <vector>

#include <primesieve.hpp>

typedef unsigned long long ull;

const ull N = 9'000'000'000'000'000'000;

int main()
{
    const ull sextic_root = std::pow(N, 1.0 / 6);
    const ull a_max = std::sqrtl(N);
    const ull b_max = std::cbrtl(N);
    std::vector<ull> primes;
    primesieve::generate_primes(sextic_root, &primes);
    std::vector<bool> squarefree(b_max + 1, true);
    for (auto p : primes) {
        ull p2 = p * p;
        for (ull n = p2; n <= b_max; n += p2) {
            squarefree[n] = false;
        }
    }
    std::vector<bool> cubefree(a_max + 1, true);
    for (auto p : primes) {
        ull p3 = p * p * p;
        for (ull n = p3; n <= a_max; n += p3) {
            cubefree[n] = false;
        }
    }
    ull count = 0;
    for (ull b = 1; b <= b_max; ++b) {
        if (squarefree[b]) {
            count += ull(std::sqrtl(N / (b * b * b))) - 1;
        }
        ull b3 = b * b * b;
        ull a_max = std::sqrtl(N / b3);
        for (ull a = 2; a <= a_max; ++a) {
        }
    }
    for (ull a = 2; a <= a_max; ++a) {
        if (cubefree[a]) {
            count--;
        }
    }
    count -= primes.size();
    std::cout << count << std::endl;
}
