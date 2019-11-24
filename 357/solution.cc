#include <iostream>
#include <array>
#include <vector>
#include <cmath>

// const unsigned N = 100'000'000;
const unsigned N = 100'000'000;
std::array<unsigned, N + 2> sieve_results;

void sieve()
{
    std::fill(sieve_results.begin(), sieve_results.end(), 1);
    unsigned small_p_threshold = std::sqrt(N);
    for (unsigned i = 2; i <= N + 1; ++i)
    {
        if (sieve_results[i] == 1)
        {
            for (auto multiple = 2 * i; multiple <= N; multiple += i)
            {
                if (sieve_results[multiple] == 1)
                {
                    sieve_results[multiple] = multiple / i;
                }
            }
            if (i <= small_p_threshold)
            {
                unsigned square = i * i;
                for (auto multiple = square; multiple <= N; multiple += square)
                {
                    sieve_results[multiple] = 0;
                }
            }
        }
    }
}

// Assumes 2 <= n <= N with no duplicate prime divisor.
bool test_predicate(unsigned n)
{
    std::vector<unsigned> prime_factors;
    auto m = n;
    while (m > 1)
    {
        auto mm = sieve_results[m];
        prime_factors.push_back(m / mm);
        m = mm;
    }
    auto num_prime_factors = prime_factors.size();
    auto upper = 1U << (num_prime_factors - 1);
    for (unsigned i = 0; i < upper; ++i)
    {
        auto d = 1U;
        for (size_t j = 0; j < num_prime_factors - 1; ++j)
        {
            if ((i >> j) & 1)
            {
                d *= prime_factors[j];
            }
        }
        if (sieve_results[d + n / d] != 1)
        {
            return false;
        }
    }
    return true;
}

unsigned long long search_and_sum()
{
    auto sum = 1ULL; // Don't forget 1!
    for (unsigned i = 2; i <= N; i += 2)
    {
        if (sieve_results[i] != 0 &&
            sieve_results[i + 1] == 1 && sieve_results[i / 2 + 2] == 1 &&
            test_predicate(i))
        {
            sum += i;
        }
    }
    return sum;
}

int main()
{
    sieve();
    std::cout << search_and_sum() << std::endl;
    return 0;
}
