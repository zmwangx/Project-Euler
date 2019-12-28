#include <array>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include <arithxx.h>
#include <ulong_extras.h>

#define TARGET_COUNT 100'000
#define LIMIT 3'500'000

const long BASE = 308;
const std::array<long, 12> BASE_DIVISORS = { 1, 2, 4, 7, 11, 14, 22, 28, 44, 77, 154, 308 };

std::array<long, LIMIT> pp;
std::vector<bool> ok(LIMIT, true);

void sieve()
{
    for (long n = 2; n < LIMIT; ++n) {
        if (pp[n]) {
            continue;
        }
        for (long m = n + n; m < LIMIT; m += n) {
            pp[m] = n;
        }
    }
}

inline bool test_multiples(int i)
{
    for (auto d : BASE_DIVISORS) {
        ulong p = i * d + 1;
        if (n_is_probabprime(p) && p != 2 && p != 3 && p != 5 && p != 23 && p != 29) {
            return false;
        }
    }
    return true;
}

inline bool bernoulli_denom_is_20010(int i)
{
    if (!pp[i]) {
        return test_multiples(i);
    }
    std::vector<long> factors;
    while (pp[i]) {
        long p = pp[i];
        factors.push_back(p);
        i /= p;
    }
    factors.push_back(i);
    int n_factors = factors.size();
    std::queue<std::pair<int, long>> q;
    q.push({ 0, 1 });
    while (!q.empty()) {
        auto [index, product] = q.front();
        q.pop();
        if (index >= n_factors) {
            if (!test_multiples(product)) {
                return false;
            }
            continue;
        }
        q.push({ index + 1, product });
        q.push({ index + 1, product * factors[index] });
    }
    return true;
}

int main()
{
    sieve();
    int count = 0;
    int tests = 0;
    for (long i = 1; i <= LIMIT; ++i) {
        if (!ok[i]) {
            continue;
        }
        tests++;
        if (!bernoulli_denom_is_20010(i)) {
            for (long j = i; j < LIMIT; j += i) {
                ok[j] = false;
            }
        } else {
            long n = BASE * i;
            count++;
            if (count < 100) {
                std::cout << n << " " << i << std::endl;
            }
            if (count % 100 == 0) {
                std::cout << count << ":\t" << n
                          << "\t(curret multiplier: " << i
                          << "; inverse frequency: " << double(i) / count
                          << "; tests performed: " << tests << ")"
                          << std::endl;
            }
            if (count == TARGET_COUNT) {
                std::cout << n << std::endl;
                break;
            }
        }
    }
}
