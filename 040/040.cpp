//
//  main.cpp
//  Prbl040
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Diven an $n$, first determine which range the $n$-th digit is in, then
//  determine its detailed position.
//  --------------------------------
//  Answer:
//

// Test the functionality of <code>nthDigit</code>.
// #define __PRBL040_IS_IN_DEBUGGING_PHASE_01__ 1

#include <iostream>
#include <cmath>
#include <string>

static int nthDigit(int n);

int main() {
    
#ifdef __PRBL040_IS_IN_DEBUGGING_PHASE_01__
    for (int i = 1; i <= 100; ++i) {
        std::cout << nthDigit(i);
    }
#endif
    
    std::cout <<
    nthDigit(1) * nthDigit(10) * nthDigit(100) * nthDigit(1000) *
    nthDigit(10000) * nthDigit(100000) * nthDigit(1000000)
    << std::endl;
    
    return 0;
}

static int nthDigit(int n) {
    int integerLength = 0;
    int totalNDigits = 0;
    int nDigits = 0;
    while (totalNDigits < n) {
        ++integerLength;
        nDigits = integerLength *
        9 * static_cast<int>(std::pow(10, integerLength - 1));
        totalNDigits += nDigits;
    }
    totalNDigits -= nDigits;
    
    int nDigitsInRange = n - totalNDigits;
    int rankInRange = static_cast<int>
    (std::ceil(static_cast<double>(nDigitsInRange) / integerLength));
    int enclosingInteger = static_cast<int>(std::pow(10, integerLength - 1)) +
                           rankInRange - 1;
    int rankInInteger = nDigitsInRange - integerLength * (rankInRange - 1);
    int digit = std::to_string(enclosingInteger)[rankInInteger - 1] - '0';
    
#ifdef __PRBL040_IS_IN_DEBUGGING_PHASE_01__
    // std::cout << "length: " << integerLength << std::endl;
    // std::cout << "remaining digits: " << nDigitsInRange << std::endl;
    // std::cout << "enclosing integer: " << enclosingInteger << std::endl;
    // std::cout << "digit: " << digit << std::endl;
#endif
    
    return digit;
}