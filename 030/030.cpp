//
//  main.cpp
//  Prbl030
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  The number of digits $n$ should satisfy
//
//  9^k \times n \geq 10^{n-1},
//
//  where k is the index (5, in this case). The maximum possible $n$ is usually
//  $k$. With this we just perform a brute force search.
//  ----------------------------------------------------
//  Answer: 443839
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

const int INDEX = 5;

static long digitPowerSum(long n, const std::vector<long>& digitPowers);

int main() {
    std::vector<long> digitPowers;
    for (long digit = 0; digit <= 9; ++digit) {
        digitPowers.push_back(std::pow(digit, INDEX));
    }
    
    int maxNDigits;
    {
        int nDigits = 1;
        while (digitPowers[9] * nDigits >= std::pow(10, nDigits - 1)) {
            ++nDigits;
        }
        maxNDigits = nDigits - 1;
    }
    long maxPossibleN = static_cast<long>(std::pow(10, maxNDigits) - 1);
    
    long sum = 0;
    for (int n = 2; n <= maxPossibleN; ++n) {
        if (digitPowerSum(n, digitPowers) == n) {
            std::cout << n << std::endl;
            sum += n;
        }
    }
    std::cout << "sum: " << sum << std::endl;
}

static long digitPowerSum(long n, const std::vector<long>& digitPowers) {
    std::string string;
    string = std::to_string(n);
    long powerSum = 0;
    for (std::string::const_iterator i = string.begin();
         i != string.end();
         ++i) {
        powerSum += digitPowers[*i - '0'];
    }
    return powerSum;
}