/**
 * 231.cpp
 * Project Euler 231
 * Created by Zhiming Wang on 04/28/2013.
 * --------------------------------------
 * Prime factorization of factorials.
 */

#include "../lib/prime.h"

#include <iostream>
#include <fstream>
#include <string>

static inline int factorialPrimeIndex(int n, int p);

#define N 20000000
#define M 15000000

int main(int argc, const char *argv[]) {
    std::vector<int> primes;
    generatePrimes(primes, 2, N);
    long long sum = 0;
    for (auto p: primes) {
        int index =
            factorialPrimeIndex(N, p)
            - factorialPrimeIndex(M, p)
            - factorialPrimeIndex(N - M, p);
        if (index > 0) {
            sum += p;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}

// index of prime p in the factorization of n!
static inline int
factorialPrimeIndex(int n, int p) {
    int index = 0;
    while (n > 1) {
        index += n % p;
        n /= p;
    }
    return index;
}
