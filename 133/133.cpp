/**
 * 133.cpp
 * Project Euler 133
 * Created by Zhiming Wang on 04/22/2013.
 * --------------------------------------
 * Number theory.
 *
 * Clearly p = 2, 3, and 5 won't work. For prime p > 5,
 *     p | (10^{10^n} - 1) / 9,
 * if and only if
 *     10^{10^n} = 1 (mod p).
 *
 * By Fermat little theorem,
 *     10^{p-1} = 1 (mod p),
 * so suppose
 *     p-1 = 2^a 5^b c,
 * where c is not divided by 2 or 5, then the desired n exists if and only if
 *     10^{2^a 5^b} = 1 (mod p).
 */

#include "../Library/prime.h"
#include "../Library/modulo.h"

#include <iostream>
#include <string>

#define MAX_PRIME 100000

int main(int argc, const char *argv[]) {
    std::vector<int> primes;
    generatePrimes(primes, 7, MAX_PRIME); // we know that 2, 3, 5 need not be
                                          // considered
    arith_t sum = 0;
    // 2, 3, 5 are not remarkable
    sum = sum + 2 + 3 + 5;
    for (auto p: primes) {
        // extract 2's and 5's from p-1
        arith_t q = (arith_t) p - 1;
        arith_t r = 1; // holder of 2's and 5's
        while (q % 2 == 0) {
            q /= 2;
            r *= 2;
        }
        while (q % 5 == 0) {
            q /= 5;
            r *= 5;
        }
        arith_t remainder = pwrmod(10, r, p);
        if (remainder == 1) {
            // remarkable
            std::cout << p << std::endl;
        } else {
            // not remarkable
            sum += p;
        }
    }
    std::cout << "sum: " << sum << std::endl;
    return 0;
}
