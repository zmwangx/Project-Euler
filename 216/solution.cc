#include <array>
#include <boost/multiprecision/miller_rabin.hpp>
#include <iostream>

using namespace boost::multiprecision;

const unsigned long long LIMIT = 50'000'000;
const std::array<unsigned long long, 167> small_primes = {
    3,
    5,
    7,
    11,
    13,
    17,
    19,
    23,
    29,
    31,
    37,
    41,
    43,
    47,
    53,
    59,
    61,
    67,
    71,
    73,
    79,
    83,
    89,
    97,
    101,
    103,
    107,
    109,
    113,
    127,
    131,
    137,
    139,
    149,
    151,
    157,
    163,
    167,
    173,
    179,
    181,
    191,
    193,
    197,
    199,
    211,
    223,
    227,
    229,
    233,
    239,
    241,
    251,
    257,
    263,
    269,
    271,
    277,
    281,
    283,
    293,
    307,
    311,
    313,
    317,
    331,
    337,
    347,
    349,
    353,
    359,
    367,
    373,
    379,
    383,
    389,
    397,
    401,
    409,
    419,
    421,
    431,
    433,
    439,
    443,
    449,
    457,
    461,
    463,
    467,
    479,
    487,
    491,
    499,
    503,
    509,
    521,
    523,
    541,
    547,
    557,
    563,
    569,
    571,
    577,
    587,
    593,
    599,
    601,
    607,
    613,
    617,
    619,
    631,
    641,
    643,
    647,
    653,
    659,
    661,
    673,
    677,
    683,
    691,
    701,
    709,
    719,
    727,
    733,
    739,
    743,
    751,
    757,
    761,
    769,
    773,
    787,
    797,
    809,
    811,
    821,
    823,
    827,
    829,
    839,
    853,
    857,
    859,
    863,
    877,
    881,
    883,
    887,
    907,
    911,
    919,
    929,
    937,
    941,
    947,
    953,
    967,
    971,
    977,
    983,
    991,
    997,
};
std::array<bool, LIMIT + 1> composite;

int main()
{
    for (auto it = small_primes.begin(); it != small_primes.end(); ++it) {
        auto p = *it;
        // We want to find n s.t. n^2 = (p+1)/2 mod p.
        auto r = (p + 1) / 2;
        for (auto n = 1ULL; n < p; ++n) {
            if ((n * n) % p == r) {
                auto m = n;
                if (m * m < p) {
                    m += p;
                }
                while (m <= LIMIT) {
                    composite[m] = true;
                    m += p;
                }
            }
        }
    }
    size_t count = 0;
    for (auto n = 1ULL; n <= LIMIT; ++n) {
        if (n % 1'000'000 == 0) {
            std::cerr << "progress: " << n << std::endl;
        }
        if (!composite[n] && miller_rabin_test(2 * n * n - 1, 10)) {
            count++;
        }
    }
    std::cout << count << std::endl;
}
