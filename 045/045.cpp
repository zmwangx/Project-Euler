//
//  main.cpp
//  Prbl045
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  n(n+1) = m(3m-1) = 2k(2k-1)
//
//  implies
//
//  n = 2k-1,
//  (12k-3)^2 - 3(6m-1)^2 = 6.
//
//  We know that the solutions for pseudo-Pell equation $x^2 - 3y^2 = 6$ satisfy
//  $x+y\sqrt(3) = (3+\sqrt(3))(2+\sqrt(3))^k$. The task left is to try
//  different solutions and find the ones satisfy the form $x = 12k-3, y =
//  6m-1$.

#include <iostream>

int main() {
    long x = 3, y = 1;
    long nSolutions = 0;
    while (nSolutions < 3) {
        long nextX = 2 * x + 3 * y;
        long nextY = x + 2 * y;
        x = nextX;
        y = nextY;
        if ( ((x +3) % 12 == 0) && ((y + 1) % 6 == 0) ) {
            long k = (x + 3) / 12;
            long m = (y + 1) / 6;
            long n = 2 * k - 1;
            
            std::cout
            << 'T' << n << '='
            << 'P' << m << '='
            << 'H' << k << '='
            << n * (n + 1) / 2
            << std::endl;
            
            ++nSolutions;
        }
    }
    return 0;
}