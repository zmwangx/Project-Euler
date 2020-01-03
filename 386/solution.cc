#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

#define N 100'000'000

typedef std::map<int, int> factorization_t;
typedef std::vector<int> exponents_t;

std::array<int, N + 1> p;
std::map<exponents_t, int> cache;

void sieve()
{
    for (int i = 2; i <= N; ++i) {
        if (p[i]) {
            continue;
        }
        for (int j = 2 * i; j <= N; j += i) {
            p[j] = i;
        }
    }
}

int count_divisors(const exponents_t& exponents, int target_degree, int current_degree, int current_index)
{
    if (current_index == exponents.size()) {
        return current_degree == target_degree ? 1 : 0;
    }
    int current_exponent = exponents[current_index];
    current_index++;
    int count = 0;
    for (int e = 0; e <= current_exponent && current_degree + e <= target_degree; ++e) {
        count += count_divisors(exponents, target_degree, current_degree + e, current_index);
    }
    return count;
}

int max_antichain_length(exponents_t& exponents)
{
    std::sort(exponents.begin(), exponents.end());
    auto it = cache.find(exponents);
    if (it != cache.end()) {
        return it->second;
    }
    int total_degree = std::accumulate(exponents.begin(), exponents.end(), 0);
    int degree = total_degree / 2;
    int count = count_divisors(exponents, degree, 0, 0);
    cache[exponents] = count;
    return count;
}

int main()
{
    sieve();
    long long sum = 1;
    for (int i = 2; i <= N; ++i) {
        if (i % 1'000'000 == 0) {
            std::cerr << "progress: " << i << std::endl;
        }
        if (!p[i]) {
            sum++;
        } else {
            factorization_t fact;
            exponents_t exponents;
            int j = i;
            while (p[j]) {
                fact[p[j]]++;
                j /= p[j];
            }
            fact[j]++;
            for (auto [p, e] : fact) {
                exponents.push_back(e);
            }
            sum += max_antichain_length(exponents);
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
