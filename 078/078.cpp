//
//  main.cpp
//  Prbl078
//
//  Created by Zhiming Wang on 12/11/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Dynamic programming. Denote the number of ways to write n as a sum of 
//  numbers in {1, ..., k} by f[n,k] (n>=1, k>=1); and for convenience of
//  stating formula, let f[0,k] = 1 for all k>=1, and let f[n,0] = 0 for all
//  n>=1. Then
//
//  f[0,k] = 1, k>=1;
//  f[n,0] = 0, n>=1;
//  f[n,k] = f[n,k-1] + f[n-k,k], n>=k>=1;
//  f[n,k] = f[n,n], k>n>=1.
//
//  ------------------------
//  Answer:
//


#include <iostream>

static const unsigned RANGE = 60000u;
static const unsigned EXPECTATION = 1000000;

int main() {
    // Allocate memory for two-dimensional array f.
    unsigned** f = new unsigned*[RANGE + 1];

    f[0] = new unsigned[1];
    f[0][0] = 1;
    
    // Main computations.
    for (unsigned n = 1; n <= RANGE; ++n) {
        if (n % 2 == 0) {
            unsigned value = f[n/2][n/2];
            delete [] f[n/2];
            f[n/2] = new unsigned[1];
            f[n/2][0] = value;
        }
        f[n] = new unsigned[n + 1];
        f[n][0] = 0;
        for (unsigned k = 1; k <= n; ++k) {
            if (n-k > k) {
                f[n][k] = (f[n][k-1] + f[n-k][k]) % EXPECTATION;
            } else {
                f[n][k] = (f[n][k-1] + f[n-k][0]) % EXPECTATION;
            }
        }
        if (f[n][n] == 0) {
            std::cout << n << std::endl;
            break;
        }
    }
        
    // Deallocate f.
    for (unsigned n = 0; n <= RANGE; ++n) {
        delete [] f[n];
    }
    delete [] f;
    
    return 0;
}