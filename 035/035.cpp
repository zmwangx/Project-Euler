//
//  main.cpp
//  Prbl035
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Brute force search through the set of prime numbers.
//  ----------------------------------------------------
//  Answer: 55
// 

#include <iostream>
#include <vector>
#include <set>
#include <cmath>

#include "prime.h"

const int RANGE = 1000000;

static inline int getNDigits(int n);

int main() {
    
    std::set<int> primes;
    {
        std::vector<int> primeVec;
        generatePrimes(primeVec, 1, RANGE);
        primes.insert(primeVec.begin(), primeVec.end());
    }
    
    int nCircularPrimes = 0;
    while (!primes.empty()) {
        int prime = *(primes.begin());
        primes.erase(primes.begin());
        int nDigits = getNDigits(prime);
        int firstDigitMultiplier = static_cast<int>(std::pow(10, nDigits - 1));
        
        int rotated = prime;
        int nDistinctRotatedForms = 1;
        bool isCircularPrime = true;
        while (true) {
            // Append first digit to the end.
            int firstDigit = rotated / firstDigitMultiplier;
            rotated = (rotated % firstDigitMultiplier) * 10 + firstDigit;
            if (rotated == prime) {
                break;
            }
            
            // Look up the newly rotated result in primes.
            std::set<int>::const_iterator it = primes.find(rotated);
            if (it == primes.end()) {
                // Not prime, or already deleted (meaning that not circular
                // primes. Otherwise, prime and rotated should already been
                // counted and removed in previous iterations.
                isCircularPrime = false;
                break;
            } else {
                // Is prime. Remove from unvisited primes and continue.
                primes.erase(it);
                ++nDistinctRotatedForms;
            }
        }
        
        if (isCircularPrime) {
            // All <code>nDistinctRotatedForms</code> rotated forms are circular
            // primes.
            nCircularPrimes += nDistinctRotatedForms;
            std::cout << prime << std::endl;
        }
    }
    
    std::cout << "number: " << nCircularPrimes << std::endl;
    
    return 0;
}

static int getNDigits(int n) {
    return std::floor(std::log(n) / std::log(10)) + 1;
}