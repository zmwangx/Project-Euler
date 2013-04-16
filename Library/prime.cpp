//
//  prime.cpp
//  ProjectEuler
//
//  Created by Zhiming Wang on 12/6/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//

// Test <code>generatePrimes</code>.
// #define __PRIME_IS_IN_DEBUGGING_PHASE_01__ 1

#include "prime.h"

#include <iostream>
#include <vector>

void generatePrimes(std::vector<int>& primes, int lowerBound, int upperBound) {
    primes.clear();
    std::vector<bool> isPrime(upperBound + 1, true);
  
    int current = 2;
    while (current <= upperBound) {
        if (isPrime[current]) {
            if (current >= lowerBound) {
                primes.push_back(current);
                
#ifdef __PRIME_IS_IN_DEBUGGING_PHASE_01__
                std::cout << current << ' ';
                if (primes.size() % 5 == 0) {
                    std::cout << std::endl;
                }
#endif
            }
            int composite = 2 * current;
            while (composite <= upperBound) {
                isPrime[composite] = false;
                composite += current;
            }
        }
        ++current;
    }
}

bool isPrime(long n) {
    if (n <= 1) {
        return false;
    }
    
    for (long i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

bool isPrime(long n, std::vector<int>& primes, int primeRange) {
    if (n <= 1) {
        return false;
    }
    
    if ((primeRange == 1) && !primes.empty()) {
        primeRange = *(primes.end() - 1);
    }
    for (std::vector<int>::const_iterator i = primes.begin();
         i != primes.end();
         ++i) {
        int prime = *i;
        if (prime * prime > n) {
            break;
        }
        if (n % prime == 0) {
            return false;
        }
    }
    if (primeRange * primeRange >= n) {
        return true;
    }
    
    // If there are still possible primes less than or equal to the square root
    // of <code>n</code> that are not covered by <code>primes</code>, then
    // brute force search comes into play.
    for (int i = primeRange + 1; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

