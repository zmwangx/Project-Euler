//
//  main.cpp
//  Prbl092
//  Project Euler
//
//  Created by Zhiming Wang on 12/11/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Since the digit square sum of any integer below 10^k cannot exceed 81k, so
//  it suffices to determine the final status of 1, 2, ... , 81k using brute
//  force.
//  ------
//  Answer: 8581146
//

#include <iostream>
#include <string>
#include <vector>

static const unsigned RANGE = 10000000;
static const unsigned MAX_NUMBER_OF_DIGITS = 7;

static unsigned searchFinalStatus(unsigned n);
static unsigned digitSquareSum(unsigned n);

int main() {
    std::vector<unsigned> finalStatuses;
    finalStatuses.push_back(0);
    for (unsigned n = 1; n <= 81 * MAX_NUMBER_OF_DIGITS; ++n) {
        finalStatuses.push_back(searchFinalStatus(n));
    }
    
    unsigned finalStatus1Count = 0;
    unsigned finalStatus89Count = 0;
    for (unsigned n = 1; n < RANGE; ++n) {
        if (finalStatuses[digitSquareSum(n)] == 1) {
            ++finalStatus1Count;
        } else {
            ++finalStatus89Count;
        }
    }
    
    std::cout << finalStatus89Count << std::endl;
    
    return 0;
}

static unsigned searchFinalStatus(unsigned n) {
    while (n != 1 && n != 89) {
        n = digitSquareSum(n);
    }
    return n;
}

static unsigned digitSquareSum(unsigned n) {
    std::string nString = std::to_string(n);
    unsigned digitSquareSum = 0;
    for (std::string::const_iterator i = nString.begin();
         i != nString.end();
         ++i) {
        digitSquareSum += (*i - '0') * (*i - '0');
    }
    return digitSquareSum;
}