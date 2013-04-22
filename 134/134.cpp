/**
 * 134.cpp
 * Project Euler 134
 * Created by Zhiming Wang on 04/22/2013.
 * --------------------------------------
 * Simple congruence equation problem.
 *
 * The equation is
 *     10^l x + p1 = 0 (mod p2),
 * where l is the length of p1. So we only need to solve
 *     10^l x = p2 - p1 (mod p2).
 */

#include "../lib/prime.h"
#include "../lib/modulo.h"
#include "../lib/numbers.h"

#include <iostream>
#include <fstream>
#include <string>

#define MIN 5
#define MAX 1000003 // 1000003 is a prime (first prime greater than 1,000,000)

int main(int argc, const char *argv[]) {
    std::vector<int> primes;
    generatePrimes(primes, MIN, MAX);
    arith_t sum = 0;
    for (auto it = primes.begin(); it + 1 != primes.end(); it++) {
        arith_t p1 = (arith_t)*it;
        arith_t p2 = (arith_t)*(it + 1);
        size_t len = num_length(p1);
        
        // we need
        //     10^len x = p2 - p1 (mod p2)
        // let it be
        //     a x = b (mod p2)
        arith_t a = pwr10(len); // positive
        arith_t b = p2 - p1; // positive

        // solve
        arith_t x = inverse(a, p2) * b % p2; // min positive solution

        // s = 10^len x + p1 = a x + p1 (which is a multiple of p2, as
        // constructed)
        arith_t s = a * x + p1;
        sum += s;
    }
    std::cout << sum << std::endl;
    return 0;
}
