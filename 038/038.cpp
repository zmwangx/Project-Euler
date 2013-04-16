//
//  main.cpp
//  Prbl038
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Note that the base integer $k$ cannot be more than 9999; otherwise even $k$
//  and $2k$ exceed 9 digits in total. Therefore, a brute force search is far
//  from enough.
//  ------------
//  Answer: 932718654
//

#include <iostream>
#include <set>

static std::string pandigitalWithBase(long base);

int main() {
    std::string maxPandigital;
    for (long base = 9; base < 10000; ++base) {
        std::string baseDerivative = pandigitalWithBase(base);
        if (!baseDerivative.empty()) {
            std::cout << baseDerivative << std::endl;
        }
        if (baseDerivative > maxPandigital) {
            maxPandigital = baseDerivative;
        }
    }
    std::cout << "max: " << maxPandigital << std::endl;
    return 0;
}

static std::string pandigitalWithBase(long base) {
    std::set<char> digits;
    int multiple = 1;
    int nDigits = 0;
    std::string potentialPandigital = "";
    while (nDigits < 9) {
        std::string nString = std::to_string(base * multiple);
        potentialPandigital += nString;
        digits.insert(nString.begin(), nString.end());
        nDigits += nString.length();
        
        ++multiple;
    }
    if (nDigits > 9) {
        return "";
    }
    if ((digits.size() != 9) || (digits.find('0') != digits.end())) {
        return "";
    }
    return potentialPandigital;
}