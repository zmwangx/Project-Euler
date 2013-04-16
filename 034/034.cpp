//
//  main.cpp
//  Prbl034
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Determine the maximum number of digits ($9! \dot n \geq 10^{n-1}$), then do
//  a brute force search.
//  ---------------------
//  Answer: 40730
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

const std::vector<int> DIGIT_FACTORIALS =
{1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

static bool equalsDigitFactorialSum(int n);

int main() {
    int maxNDigits;
    {
        int nDigits = 1;
        while (DIGIT_FACTORIALS[9] * nDigits >= std::pow(10, nDigits - 1)) {
            ++nDigits;
        }
        maxNDigits = nDigits - 1;
    }
    
    int maxPossibleCuriousNumber =
    static_cast<int>(std::pow(10, maxNDigits) - 1);
    int sumCuriousNumbers = 0;
    for (int n = 3; n <= maxPossibleCuriousNumber; ++n) {
        if (equalsDigitFactorialSum(n)) {
            std::cout << n << std::endl;
            sumCuriousNumbers += n;
        }
    }
    
    std::cout << sumCuriousNumbers << std::endl;
    
    return 0;
}

static bool equalsDigitFactorialSum(int n) {
    int digitFactorialSum = 0;
    std::string nString = std::to_string(n);
    for (std::string::const_iterator i = nString.begin();
         i != nString.end();
         ++i) {
        digitFactorialSum += DIGIT_FACTORIALS[*i - '0'];
    }
    return digitFactorialSum == n;
}