#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#define N 1'000'000'000

typedef unsigned long long ulong;

std::vector<int> pp;

void sieve()
{
    int max = std::sqrt(N);
    pp.resize(max + 1, 0);
    for (int i = 2; i <= max; ++i) {
        if (pp[i]) {
            continue;
        }
        for (int j = i * 2; j <= max; j += i) {
            pp[j] = i;
        }
    }
}

inline ulong triangle_sum(ulong x)
{
    return x * (x + 1) / 2;
}

int main()
{
    sieve();
    int max_b0 = std::sqrt(N);
    ulong sum = 0;
    for (int b0 = 2; b0 <= max_b0; b0++) {
        // delta = a0 - b0, 0 < delta < b0, a0b0 <= N.
        int max_delta = std::min(b0 - 1, N / b0 - b0);
        std::vector<bool> coprime(max_delta + 1, true);
        int tmp = b0;
        while (tmp > 1) {
            int p = pp[tmp] ? pp[tmp] : tmp;
            for (int i = p; i <= max_delta; i += p) {
                coprime[i] = false;
            }
            while (tmp % p == 0) {
                tmp /= p;
            }
        }
        for (int delta = 1; delta <= max_delta; ++delta) {
            if (coprime[delta]) {
                ulong a = (b0 + delta) * b0;
                sum += a * triangle_sum(N / a);
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
