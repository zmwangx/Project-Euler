/**
 * 179.cpp
 * Project Euler 179
 * Created by Zhiming Wang on 04/27/2013.
 * --------------------------------------
 * Brute force all number of divisors.
 */

#include "../lib/prime.h"

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <iterator>
#include <algorithm>

#define MAX 10000000
#define MAX_SQRT 3162

int main(int argc, const char *argv[]) {
    std::vector<int> pvec;
    std::set<int> pset;
    generatePrimes(pvec, 2, MAX);
    std::copy(pvec.begin(), pvec.end(), std::inserter(pset, pset.end()));

    std::vector<int> pvecl; // lite vector; only up to MAX_SQRT for speed
                            // concern
    generatePrimes(pvecl, 2, MAX_SQRT);

    // compute number of divisors
    std::vector<int> d(MAX + 1); // number of divisors
    d[1] = 1;
    for (int i = 2; i < MAX; i++) {
        if (pset.count(i)) {
            // is prime
            d[i] = 2;
            continue;
        }
        // composite; find min prime divisor
        int minP = -1;
        for (auto p: pvecl) {
            if (i % p == 0) {
                minP = p;
                break;
            }
        }
        int minPIndex = 0;
        int icopy = i;
        while (icopy % minP == 0) {
            minPIndex++;
            icopy /= minP;
        }
        // the number of divisors
        d[i] = d[icopy] * (minPIndex + 1);
    }
    
    // count same neighbor pairs
    int totalNumPairs = 0;
    for (int i = 2; i < MAX - 1; i++) {
        if (d[i] == d[i+1]) {
            totalNumPairs++;
        }
    }
    std::cout << totalNumPairs << std::endl;
    
    return 0;
}
