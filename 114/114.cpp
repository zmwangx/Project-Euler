//
//  main.cpp
//  Prbl114
//  Project Euler
//
//  Created by Zhiming Wang on 12/18/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Dynamic programming.
//
//  f(n) stands for the number of conbinations of n units starting with a red
//  block, where n>=3. Then considering the starting position of the second red
//  block (if exists) we have:
//
//  f(n) = (n - 2) + \sum_{k=5}^{n-2} (k-4) * f(n-k+1),
//
//  and the total number of combinations of n units is
//
//  1 + \sum_{k=3}^n f(k).
//  ----------------------
//  Answer: 16475640049
//

#include <iostream>

const long long N = 50;

int main() {
    long long f[N + 1];
    for (long long n = 3; n <= N; ++n) {
        f[n] = n - 2;
        for (long long k = 5; k <= n - 2; ++k) {
            f[n] += (k - 4) * f[n - k + 1];
        }
    }
    long long total = 1;
    for (long long k = 3; k <= N; ++k) {
        total += f[k];
    }
    std::cout << total << std::endl;
    return 0;
}