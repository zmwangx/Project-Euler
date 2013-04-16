//
//  main.cpp
//  Prbl075
//  Project Euler
//
//  Created by Zhiming Wang on 12/11/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Every integeral-valued right triangle has an unique form $(k(m^2+n^2),
//  2kmn, k(m^2-n^2))$, where $(m, n)=1$, and $m$ and $n$ have different
//  parity. With this knowlegdge we can generate all possible perimeters, and
//  use a data structure similar to bucket sort to record the number of
//  possible divisions to every possible perimeter.
//  -----------------------------------------------
//  Answer: 161667
// 

#include <iostream>
#include <array>

static const int MAX_HALF_PERIMETER = 750000;

static inline bool areCoprime(int x, int y);
static int gcd(int x, int y);

int main() {
    std::array<int, MAX_HALF_PERIMETER + 1> numbersOfPossibleDivisions;
    for (int i = 0; i <= MAX_HALF_PERIMETER; ++i) {
        numbersOfPossibleDivisions[i] = 0;
    }
    
    for (int m = 2; m * (m + 1) <= MAX_HALF_PERIMETER; ++m) {
        for (int n = (m % 2 == 0) ? 1 : 2; n < m; n += 2) {
            if (!areCoprime(m, n)) {
                continue;
            }
            int baseCase = m * (m + n);
            if (baseCase > MAX_HALF_PERIMETER) {
                break;
            }
            for (int multiple = 1;
                 multiple * baseCase <= MAX_HALF_PERIMETER;
                 ++multiple) {
                ++numbersOfPossibleDivisions[multiple * baseCase];
            }
        }
    }
    
    int uniqueCount = 0;
    for (int halfPerimeter = 1;
         halfPerimeter <= MAX_HALF_PERIMETER;
         ++halfPerimeter) {
        if (numbersOfPossibleDivisions[halfPerimeter] == 1) {
            ++uniqueCount;
        }
    }
    std::cout << uniqueCount << std::endl;
    
    return 0;
}

static inline bool areCoprime(int x, int y) {
    return gcd(x, y) == 1;
}

static int gcd(int x, int y) {
    if (y == 0) {
        return x;
    } else {
        return gcd(y, x % y);
    }
}