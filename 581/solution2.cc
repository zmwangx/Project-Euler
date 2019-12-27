// The brute force sieve approach. Didn't pan out because the largest number is
// too large.

#include <iomanip>
#include <iostream>
#include <vector>

#include <omp.h>
#include <primesieve.hpp>

typedef unsigned long long ull;

const ull CHUNK_SIZE = 1ULL << 32;
const ull NUM_CHUNKS = 1024;
const unsigned PRIMES_LIMIT = 2'147'483'647;
const ull PRINT_THRESHOLD = 1'000'000'000;

std::vector<unsigned> primes;
std::vector<unsigned> small_primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };

void print_thread_info()
{
    std::cerr << std::setfill('0')
              << "[thread "
              << std::setw(2) << omp_get_thread_num() << "/" << std::setw(2) << omp_get_num_threads()
              << "] ";
}

inline bool is_smooth(ull n)
{
    for (auto p : small_primes) {
        while (n % p == 0) {
            n /= p;
        }
    }
    return n == 1;
}

ull search(ull lower_bound, ull upper_bound)
{
    ull size = upper_bound - lower_bound + 1;
    std::vector<bool> smooth(size, true);
    for (auto p : primes) {
        if (p <= 47) {
            continue;
        }
        for (ull i = (lower_bound / p + 1) * p - lower_bound; i < size; i += p) {
            smooth[i] = false;
        }
    }
    ull sizem1 = size - 1;
    ull total = 0;
    for (ull i = 0; i < sizem1; ++i) {
        if (smooth[i] && smooth[i + 1]) {
            ull n = i + lower_bound;
            if (n >= PRIMES_LIMIT && (!is_smooth(n) || !is_smooth(n + 1))) {
                continue;
            }
            if (n > PRINT_THRESHOLD) {
                std::cerr << n << std::endl;
            }
            total += n;
        }
    }
    return total;
}

int main()
{
    primesieve::generate_primes(PRIMES_LIMIT, &primes);
    ull total = 0;
#pragma omp parallel for schedule(dynamic) num_threads(2)
    for (ull i = 0; i < NUM_CHUNKS; ++i) {
        ull lower = i * CHUNK_SIZE + 1, upper = (i + 1) * CHUNK_SIZE;
#pragma omp critical
        {
            print_thread_info();
            std::cerr << "searching " << lower << " to " << upper << "..." << std::endl;
        }
        ull subtotal = search(lower, upper);
#pragma omp critical
        {
            total += subtotal;
            print_thread_info();
            std::cerr << "finished searching " << lower << " to " << upper << "; "
                      << "subtotal " << subtotal << ", current total " << total << std::endl;
        }
    }
    std::cout << total << std::endl;
    return 0;
}
