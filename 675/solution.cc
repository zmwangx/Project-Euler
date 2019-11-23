#include <iostream>
#include <array>
#include <map>

const unsigned N = 10'000'000;
const unsigned P = 1'000'000'087;
std::array<unsigned, N + 1> sieve_results;

void sieve()
{
    std::fill(sieve_results.begin(), sieve_results.end(), 1);
    for (unsigned i = 2; i <= N; ++i)
    {
        if (sieve_results[i] == 1)
        {
            for (unsigned multiple = 2 * i; multiple <= N; multiple += i)
            {
                sieve_results[multiple] = multiple / i;
            }
        }
    }
}

// Assumes 2 <= n <= N.
std::map<unsigned, size_t> factor(unsigned n)
{
    std::map<unsigned, size_t> factors;
    unsigned divisor;
    while ((divisor = sieve_results[n]) != 1)
    {
        factors[n / divisor]++;
        n = divisor;
    }
    factors[n]++;
    return factors;
}

// Calculates the multiplicative inverse of n mod P using the extended Euclidean
// algorithm.
unsigned modular_multiplicative_inverse(unsigned n)
{
    long long a = P;
    long long b = n;
    long long t = 0;
    long long newt = 1;
    while (a > 1)
    {
        long long q = a / b;
        long long r = a % b;
        long long temp = newt;
        newt = t - q * newt;
        t = temp;
        a = b;
        b = r;
    }
    return (t % P + P) % P;
}

unsigned calculate_F(unsigned n)
{
    unsigned long long result = 0;
    unsigned long long product = 1;
    std::map<unsigned long long, size_t> cumulated_factors;
    for (unsigned i = 2; i <= n; ++i)
    {
        auto factors = factor(i);
        for (auto it = factors.begin(); it != factors.end(); ++it)
        {
            auto p = it->first;
            auto index = it->second;
            auto cumulated_index = cumulated_factors[p];
            cumulated_factors[p] += index;
            auto old_multiplicant = 2 * cumulated_index + 1;
            auto new_multiplicant = old_multiplicant + 2 * index;
            product = (product * modular_multiplicative_inverse(old_multiplicant)) % P;
            product = product * new_multiplicant % P;
        }
        result = (result + product) % P;
    }
    return result;
}

int main()
{
    sieve();
    std::cout << calculate_F(N) << std::endl;
    return 0;
}
