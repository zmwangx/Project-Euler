/**
 * 381.cpp
 * Project Euler 381
 * Created by Zhiming Wang on 04/19/2013.
 * --------------------------------------
 * Wilson's theorem; Euclidean algorithm for computation of modulus inverse.
 */

#include "../Library/prime.h"
#include "../Library/modulo.h"

#include <iostream>
#include <fstream>
#include <string>

#define MIN_PRIME 5
#define MAX_PRIME 100000000

int main(int argc, const char *argv[]) {
    std::vector<int> primes;
    generatePrimes(primes, MIN_PRIME, MAX_PRIME);
    arith_t sum = 0;
    for (auto p: primes) {
        arith_t r1 = p - 1; // remainder of (p-1)!; Wilson's theorem
        arith_t r2 = 1; // remainder of (p-2)!; r1 * inverse(-1, p)
        arith_t r3 = (r2 * inverse(-2, p)) % p; // remainder of (p-3)!
        arith_t r4 = (r3 * inverse(-3, p)) % p; // remainder of (p-4)!
        arith_t r5 = (r4 * inverse(-4, p)) % p; // remainder of (p-5)!
        sum += (r1 + r2 + r3 + r4 + r5) % p;
    }
    std::cout << sum << std::endl;
    return 0;
}
