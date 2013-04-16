//
//  main.cpp
//  Prbl039
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Alogrithm:
//
//  $a = k(m^2-n^2), b = 2kmn, c = k(m^2+n^2), p = 2km(m+n), (m,n)=1.$
//
//  The equations above says all we need. We only need to enumerate $(m,n)$
//  pairs, with $1 \leq n < m \leq 31$.
//  -----------------------------------
//  Answer: 840
//

#include <iostream>
#include <vector>

const int RANGE = 1000;

static int gcd(int x, int y);

int main() {
    std::vector<int> pOccurences;
    for (int p = 0; p <= RANGE; ++p) {
        pOccurences.push_back(0);
    }
    
    for (int m = 2; m <= 31; ++m) {
        for (int n = 1; n < m; ++n) {
            if (gcd(m, n) != 1) {
                continue;
            }
            int basicP = 2 * m * (m + n);
            for (int p = basicP; p <= RANGE; p += basicP) {
                ++pOccurences[p];
            }
        }
    }
    
    int mostOccurredP;
    int maxPOccurrence = 0;
    for (int p = 0; p <= RANGE; ++p) {
        if (pOccurences[p] > maxPOccurrence) {
            maxPOccurrence = pOccurences[p];
            mostOccurredP = p;
        }
    }
    std::cout << mostOccurredP << std::endl;
    
    return 0;
}

static int gcd(int x, int y) {
    if (y == 0) {
        return x;
    } else {
        return gcd(y, x % y);
    }
}