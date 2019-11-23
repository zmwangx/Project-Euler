#include <iostream>
#include <array>

const unsigned N = 40'000'000;
std::array<unsigned, N + 1> sieve_results;
std::array<unsigned, N + 1> phi;
std::array<size_t, N + 1> lengths;

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

void calculate_totients()
{
    phi[1] = 1;
    for (unsigned i = 2; i <= N; ++i)
    {
        unsigned divisor = sieve_results[i];
        unsigned p = i / divisor;
        if (divisor % p == 0)
        {
            phi[i] = phi[divisor] * p;
        }
        else
        {
            phi[i] = phi[divisor] * (p - 1);
        }
    }
}

unsigned long long sum_prime_chains(size_t target_length)
{
    auto sum = 0ULL;
    lengths[1] = 1;
    for (unsigned i = 2; i <= N; ++i)
    {
        lengths[i] = lengths[phi[i]] + 1;
        if (sieve_results[i] == 1 && lengths[i] == target_length)
        {
            sum += i;
        }
    }
    return sum;
}

int main()
{
    sieve();
    calculate_totients();
    std::cout << sum_prime_chains(25) << std::endl;
    return 0;
}
