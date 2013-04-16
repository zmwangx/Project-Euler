//
//  main.cpp
//  Prbl115
//  Project Euler
//
//  Created by Zhiming Wang on 12/18/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Dynamic programming.
//
//  f(m,n) stands for the number of conbinations of n units starting with a red
//  block, where n>=m. Then considering the starting position of the second red
//  block (if exists) we have:
//
//  f(m,n) = (n-m+1) + \sum_{k=m+2}^{n-m+1} (k-m-1) * f(m,n-k+1),
//
//  and the total number of combinations of n units, denoted by F(m,n) in the
//  problem, is simply
//
//  1 + \sum_{k=m}^n f(m,k).
//  ------------------------
//  Answer: 168
//

#include <iostream>

const int M = 50;
const int N_ESTIMATE = 1000;
const int EXPECTATION = 1000000;

int main() {
    int f[N_ESTIMATE + 1];
    
    int n = M - 1;
    int bigF = 1;
    while (bigF <= EXPECTATION) {
        ++n;
        
        f[n] = n - M + 1;
        for (int k = M + 2; k <= n - M + 1; ++k) {
            f[n] += (k - M - 1) * f[n - k + 1];
        }
        
        bigF += f[n];
    }
    
    std::cout << n << std::endl;
    
    return 0;
}