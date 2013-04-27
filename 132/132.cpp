/**
 * 132.cpp
 * Project Euler 132
 * Created by Zhiming Wang on 04/27/2013.
 * --------------------------------------
 * NT library call.
 */

#include "../lib/prime.h"
#include "../lib/modulo.h"

#include <iostream>
#include <fstream>
#include <string>

#define EXPONENT 1000000000
#define NUM_PRIMES 40

#define MAX_NUM_PRIMES_TO_CHECK 100000
#define MAX_PRIME_TO_CHECK 1299709
#define MIN_PRIME_TO_CHECK 7 // 2, 3 and 5 are obviously excluded

int main(int argc, const char *argv[]) {
    std::vector<int> primes;
    generatePrimes(primes, MIN_PRIME_TO_CHECK, MAX_PRIME_TO_CHECK);
    arith_t sum = 0;
    size_t numPrimeFactors = 0;
    for (auto p: primes) {
        if (is_multiple_of_order(10, EXPONENT, p)) {
            sum += p;
            numPrimeFactors++;
            std::cout << numPrimeFactors << ": " << p << std::endl;
            if (numPrimeFactors >= NUM_PRIMES) {
                break;
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
