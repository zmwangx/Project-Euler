//
//  main.cpp
//  Prbl028
//  Project Euler
//
//  Created by Zhiming Wang on 12/06/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  The formula is trivial: for $(2n+1)\times(2n+1)$ spiral,
//
//  S = \frac{16n^3 + 30n^2 + 26n + 3}{3}.
//  --------------------------------------
//  Answer: 669171001
//

#include <iostream>

constexpr int SPIRAL_SIZE = 1001;
constexpr int SPIRAL_SIZE_PARAMETER = (SPIRAL_SIZE - 1) / 2;

int main() {
    int n = SPIRAL_SIZE_PARAMETER;
    int sumOfDiagonals = (16*n*n*n + 30*n*n + 26*n + 3)/3;
    std::cout << sumOfDiagonals << std::endl;
    return 0;
}