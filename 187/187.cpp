/**
 * 187.cpp
 * Project Euler 187
 * Created by Zhiming Wang on 04/27/2013.
 * --------------------------------------
 *
 */

#include "../lib/prime.h"

#include <iostream>
#include <fstream>
#include <string>

#define MAX_COMPOSITE     99999999
#define MAX_PRIME         49999999
#define MAX_SMALLER_PRIME 9999

#define arith_t long long

int main(int argc, const char *argv[]) {
    std::vector<int> primes;
    generatePrimes(primes, 2, MAX_PRIME);
    size_t totalNum = 0;
    for (auto i = primes.begin(); i != primes.end(); ++i) {
        if (*i > MAX_SMALLER_PRIME) {
            break;
        }
        for (auto j = i; j != primes.end(); ++j) {
            if ((arith_t)*i * (arith_t)*j > (arith_t)MAX_COMPOSITE) {
                break;
            }
            totalNum++;
        }
    }
    std::cout << totalNum << std::endl;
    return 0;
}
