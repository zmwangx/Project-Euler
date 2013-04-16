//
//  main.cpp
//  Prbl145
//  Project Euler
//
//  Created by Zhiming Wang on 01/13/13.
//  Copyright (c) 2013 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Exhaustion.
//  -----------
//  Answer:
//

#include <string>
#include <algorithm>
#include <iostream>

static const long RANGE = 1000000000;

static long reverse(long n);
bool containEvenDigit(long n);

int main() {
    int nReversibles = 0;
    for (long i = 1; i < RANGE; ++i) {
        if (i % 10 == 0) {
            continue;
        }
        if (!containEvenDigit(i + reverse(i))) {
            ++nReversibles;
        }
    }
    std::cout << nReversibles;
    return 0;
}

long reverse(long n) {
    std::string str = std::to_string(n);
    std::reverse(str.begin(), str.end());
    return std::atol(str.c_str());
}

bool containEvenDigit(long n) {
    while (n > 0) {
        if (n % 2 == 0) {
            return true;
        }
        n /= 10;
    }
    return false;
}