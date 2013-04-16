//
//  main.cpp
//  Prbl077
//
//  Created by Zhiming Wang on 12/11/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Dynamic programming. Denote the number of ways to write n as a sum of prime
//  numbers in {1, ..., k} by f[n,k] (n>=1, k>=1); and for convenience of
//  stating formula, let f[0,k] = 1 for all k>=1, and let f[n,0] = 0 for all
//  n>=1. Then
//
//  f[0,k] = 1, k>=1;
//  f[n,0] = 0, n>=1;
//  f[n,k] = f[n,k-1] + f[n-k,k], if k is prime;
//           f[n,k-1], otherwise;
//           n>=k>=1;
//  f[n,k] = f[n,n], k>n>=1.
//
//  Note that in this notation n = n is also considered as a form of sum if n
//  is prime.
//  ---------
//  Answer: 71
//

#include <iostream>
#include <vector>

#include "prime.h"

const int RANGE = 1000;
const int EXPECTATION = 5000;

int main() {
    // Allocate memory for two-dimensional array f.
    int** f = new int*[RANGE + 1];
    for (int n = 0; n <= RANGE; ++n) {
        f[n] = new int[RANGE + 1];
    }
    
    // Initialize.
    for (int n = 0; n <= RANGE; ++n) {
        for (int k = 0; k <= RANGE; ++k) {
            f[n][k] = 0;
        }
    }
    for (int k = 1; k <= RANGE; ++k) {
        f[0][k] = 1;
    }
    for (int n = 1; n <= RANGE; ++n) {
        f[n][0] = 0;
    }
    
    // Generate prime list.
    bool isPrime[RANGE + 1];
    {
        std::vector<int> primes;
        generatePrimes(primes, 1, RANGE);
        for (int i = 0; i <= RANGE; ++i) {
            isPrime[i] = false;
        }
        for (std::vector<int>::const_iterator primeIt = primes.begin();
             primeIt != primes.end();
             ++primeIt) {
            isPrime[*primeIt] = true;
        }
    }
    
    // Main computations.
    for (int n = 1; n <= RANGE; ++n) {
        for (int k = 1; k <= n; ++k) {
            if (isPrime[k]) {
                // Since we did not actually compute f[n-k,k] when 1<=n-k<k, it
                // is important to check if k falls into this range.
                if (n - k == 0) {
                    f[n][k] = f[n][k-1] + 1;
                } else if (n-k >= k) {
                    f[n][k] = f[n][k-1] + f[n-k][k];
                } else {
                    f[n][k] = f[n][k-1] + f[n-k][n-k];
                }
            } else {
                // k is not a prime.
                f[n][k] = f[n][k-1];
            }
        }
        if (f[n][n-1] > EXPECTATION) {
            std::cout << n << std::endl;
            break;
        }
    }
    
    // Deallocate memory.
    for (int n = 0; n <= RANGE; ++n) {
        delete [] f[n];
    }
    delete [] f;
    
    return 0;
}