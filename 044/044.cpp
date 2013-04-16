//
//  main.cpp
//  Prbl044
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  We have
//
//  P_k - P_j = D, P_k + P_j = S,
//
//  Where $P_k$, $P_j$, $D = P_d$, $S = P_s$ are all pentagonal numbers. In
//  order to minimize $D$ (equivalently, $d$), we perform search on $d$. Since
//  $P_{j+1} - P_j = 3j + 1$, for each $D$ the possibilities of $k$ and $j$ are
//  finite.
//  -------
//  Answer: 5482660
//

#include <iostream>
#include <cmath>

static inline long kthPentagonalNumber(long k);
static bool isPentagonalNumber(long n);

int main() {
    long d = 1;
    bool solutionIsFound = false;
    while (true) {
        long bigD = kthPentagonalNumber(d);
        long j = 1;
        while (3 * j + 1 <= bigD) {
            long pJ = kthPentagonalNumber(j);
            long pK = pJ + bigD;
            if (isPentagonalNumber(pK)) {
                long bigS = pJ + pK;
                if (isPentagonalNumber(bigS)) {
                    solutionIsFound = true;
                    
                    std::cout
                    << "D= " << bigD << ", "
                    << "P_j= " << pJ << ", "
                    << "P_k= " << pK << ", "
                    << "S= " << bigS << "."
                    << std::endl;
                    
                    break;
                }
            }
            ++j;
        }
        if (solutionIsFound) {
            break;
        }
        ++d;
    }
    return 0;
}

static long kthPentagonalNumber(long k) {
    return k * (3 * k - 1) / 2;
}

static bool isPentagonalNumber(long n) {
    long k = std::ceil(std::sqrt(static_cast<double>(2 * n) / 3));
    return (n == k * (3 * k - 1) / 2);
}