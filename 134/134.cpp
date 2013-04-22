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

#include <iostream>
#include <fstream>
#include <string>

#define MIN 5
#define MAX 1000003 // 1000003 is a prime (first prime greater than 1,000,000)
#define MAX_P1 1000000

int main(int argc, const char *argv[]) {
    std::vector<int> primes;
    generatePrimes(primes, MIN, MAX);
    arith_t sum = 0;
    for (auto p1: primes) {
        if (p1 > MAX_P1) {
            break;
        }
    }
    return 0;
}
