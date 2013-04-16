//
//  main.cpp
//  Prbl076
//  Project Euler
//
//  Created by Zhiming Wang on 12/11/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Dynamic programming. Denote the number of ways to write n as a sum of
//  numbers in {1, ..., k} by f[n,k] (n>=1, k>=1); and for convenience of
//  stating formula, let f[0,k] = 1 for all k>=1. Then
//
//  f[0,k] = 1, k>=1;
//  f[n,1] = 1, n>=1;
//  f[n,k] = f[n,k-1] + f[n-k,k], n>=k>=2;
//  f[n,k] = f[n,n], k>n>=1.
//
//  Note that in this notation n = n is also considered as a form of sum. When
//  generating output, n = n should be deducted.
//  --------------------------------------------
//  Answer: 190569291
//

#include <iostream>

static const int RANGE = 10;

int main() {
    long f[RANGE + 1][RANGE + 1];
    
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
        f[n][1] = 1;
    }
    
    // Main computations.
    for (int n = 1; n <= RANGE; ++n) {
        for (int k = 2; k <= n; ++k) {
            f[n][k] = f[n][k-1] + f[n-k][k];
        }
        for (int k = n + 1; k <= RANGE; ++k) {
            f[n][k] = f[n][n];
        }
    }
    
    std::cout << f[RANGE][RANGE] - 1 << std::endl;
    
    return 0;
}