#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

#include <primesieve.hpp>

const unsigned long long N = 10'000'000'000;

int main()
{
    unsigned long long root = std::sqrt(N);

    std::vector<unsigned long long> small_primes;
    primesieve::generate_primes(root, &small_primes);

    // // This commented out method costs more memory and runs slower due to the
    // // huge sort.
    //
    // std::vector<unsigned long long> small_non_smooth; for (auto p :
    // small_primes) {auto p2 = p * p; for (auto n = p; n <= p2; n += p)
    // {small_non_smooth.push_back(n);
    //     }
    // }
    // std::sort(small_non_smooth.begin(), small_non_smooth.end()); size_t
    // small_non_smooth_count = std::unique(small_non_smooth.begin(),
    // small_non_smooth.end()) - small_non_smooth.begin();

    std::vector<bool> non_smooth(N + 1, false);
    for (auto p : small_primes) {
        auto p2 = p * p;
        for (auto n = p; n <= p2; n += p) {
            non_smooth[n] = true;
        }
    }
    size_t small_non_smooth_count = std::count(non_smooth.begin(), non_smooth.end(), true);
    std::cout << "p <= " << root << ": " << small_non_smooth_count << std::endl;

    std::vector<unsigned long long> large_primes;
    primesieve::generate_primes(root + 1, N, &large_primes);
    auto large_non_smooth_count = 0ULL;
    for (auto p : large_primes) {
        large_non_smooth_count += N / p;
    }
    std::cout << "p > " << root << ": " << large_non_smooth_count << std::endl;

    std::cout << N - small_non_smooth_count - large_non_smooth_count << std::endl;
    return 0;
}
