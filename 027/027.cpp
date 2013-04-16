//
//  main.cpp
//  Prbl027
//  Project Euler
//
//  Created by Zhiming Wang on 12/06/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Inserting $n = 0$ and we have $b$ is a prime. Inserting $n = b$ we have
//  $b^2 + a b + b$ is by no means a prime (think about when $n = 1$ and $n^2 +
//  a n + b = 1 + a + b = (b^2 + a b + b) / b$). So the maximum number is never
//  more than $b$, that is to say, never more than <code>RANGE</code> (in this
//  case, 1000).
//
//  This way we can just perform a brute search on all $a$s and prime $b$s, and
//  the complexity is never more than $O(n^3.5 / log n)$. In reality, the
//  complexity is far less than that.
//  ---------------------------------
//  Answer: -59231
//

// Test <code>isPrime</code> in prime.h.
// #define __PRBL027_IS_IN_DEBUGGING_PHASE_01__ 1
// Test if the resulting a, b, and maxNConsectives are reasonable.
// #define __PRBL027_IS_IN_DEBUGGING_PHASE_02__ 2

#include <iostream>
#include <vector>

#include "prime.h"

const int RANGE = 1000;

static int findConsecutivePrimeQuadratics(int a, int b,
                                         std::vector<int>& primes);

int main() {
    std::vector<int> primes;
    generatePrimes(primes, 1, RANGE);
    
#ifdef __PRBL027_IS_IN_DEBUGGING_PHASE_01__
    std::cout << isPrime(2)                 << std::endl;
    std::cout << isPrime(2,         primes) << std::endl;
    std::cout << isPrime(1000)              << std::endl;
    std::cout << isPrime(1000,      primes) << std::endl;
    std::cout << isPrime(100000000)         << std::endl;
    std::cout << isPrime(100000000, primes) << std::endl;
    std::cout << isPrime(99999989)          << std::endl;
    std::cout << isPrime(99999989,  primes) << std::endl;
    std::cout << isPrime(-97)               << std::endl;
    std::cout << isPrime(-97,       primes) << std::endl;
#endif
    
    int maxNConsecutives = 0;
    int productOfCoefficients;
    for (std::vector<int>::const_iterator i = primes.begin();
         i != primes.end();
         ++i) {
        int b = *i;
        for (int a = -RANGE; a <= RANGE; ++a) {
            int nConsecutives = findConsecutivePrimeQuadratics(a, b, primes);
            if (nConsecutives > maxNConsecutives) {
                maxNConsecutives = nConsecutives;
                productOfCoefficients = a * b;
#ifdef __PRBL027_IS_IN_DEBUGGING_PHASE_02__
                std::cout << a << ' ' << b << std::endl;
#endif
            }
        }
    }
    
#ifdef __PRBL027_IS_IN_DEBUGGING_PHASE_02__
    std::cout << maxNConsecutives << std::endl;
#endif
    std::cout << productOfCoefficients << std::endl;
    
    return 0;
}

/**
 * Find the number of consecutive n = 0, 1, ... such that $n^2 + a n + b$ is 
 * prime-valued.
 */
static int findConsecutivePrimeQuadratics(int a, int b,
                                          std::vector<int>& primes) {
    int n = 0;
    while (isPrime(n*n + a*n + b, primes)) {
        ++n;
    }
    return n;
}