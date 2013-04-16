//
//  main.cpp
//  Prbl026
//  Project Euler
//
//  Created by Zhiming Wang on 12/06/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  $1/d$ can be represented as a repeating decimal with period $n$ ($n$ is not
//  necessarilly the smallest period) if and only if
//
//  d | 10^m (10^n - 1).
//
//  So we actually need to find the largest order of 10 with regard to a prime
//  number in $[1, 1000]$, in this case.
//
//  To get the order, the most straightforwoard algorithm is brute force
//  search. This way we will end up in a $O(n^2 / \log(n)) algorithm, since the
//  number of primes is approximately $n / \log(n)$.
//  -------------------------------------------------
//  Answer: 983
//

// Test functionality of <code>generatePrimeList</code>.
// #define __PRBL025_IS_IN_DEBUGGING_PHASE_01__ 1

#include <iostream>
#include <vector>
#include <array>

const int INTEGER_RANGE = 1000;
const int BASE = 10;

static void generatePrimeList(std::vector<int>& primeList);

static int order(int p);

int main() {
    std::vector<int> primeList;
    generatePrimeList(primeList);
    
    int maximumPeriod = 0;
    int maximizer;
    for (std::vector<int>::const_iterator i = primeList.begin();
         i != primeList.end();
         ++i) {
        if ((*i == 2) || (*i == 5)) {
            continue;
        }
        int period = order(*i);
        if (period > maximumPeriod) {
            maximumPeriod = period;
            maximizer = *i;
        }
    }
    
    std::cout << maximizer << std::endl;
    
    return 0;
}

/**
 * Generates prime list in $[1, INTEGER_RANGE]$ by sieve of Eratosthenes.
 */
static void generatePrimeList(std::vector<int>& primeList) {
    std::array<bool, INTEGER_RANGE + 1> isPrime;
    for (int i = 2; i <= INTEGER_RANGE; ++i) {
        isPrime[i] = true;
    }
    
    int current = 2;
    while (current <= INTEGER_RANGE) {
        if (isPrime[current]) {
            primeList.push_back(current);
            
#ifdef __PRBL025_IS_IN_DEBUGGING_PHASE_01__
            std::cout << current << ' ';
            if (primeList.size() % 5 == 0) {
                std::cout << std::endl;
            }
#endif
            
            int composite = 2 * current;
            while (composite <= INTEGER_RANGE) {
                isPrime[composite] = false;
                composite += current;
            }
        }
        ++current;
    }
}

static int order(int p) {
    int index = 1;
    int remainder = BASE % p;
    while (remainder != 1) {
        remainder = (remainder * BASE) % p;
        ++index;
    }
    return index;
}