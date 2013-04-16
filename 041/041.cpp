//
//  main.cpp
//  Prbl041
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Generate all permutations and check if prime.
//  ---------------------------------------------
//  Answer: 7652413
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "prime.h"

int main() {
    std::vector<int> primes;
    generatePrimes(primes, 1, std::floor(std::sqrt(1000000000)));
    
    long maxPandigitalPrime = 0;
    
    for (int n = 1; n <= 9; ++n) {
        // Generate permutations of 1 ... n.
        std::string perm;
        
        // Initialize <code>perm</code>. The first digit '0' is used as a
        // running status indicator. When <code>perm[0] != '0'</code>, all the
        // perms have been visited.
        for (int i = 0; i <= n; ++i) {
            perm += (i + '0');
        }
        
        while (perm[0] == '0') {
            long value = std::atoi(perm.c_str());
            if (isPrime(value)) {
                std::cout << value << std::endl;
                maxPandigitalPrime = value;
                // Notice that permutations are generated in increasing order,
                // so value must be larger than the current maxPandigitalPrime.
            }
            
            // Generate next perm.
            int pos1 = n; // last pos
            while (perm[pos1] < perm[pos1 - 1]) {
                // last digits decreasing.
                --pos1;
            }
            // When loop is ended, perm[pos1 - 1] < perm[pos1]. perm[pos1 - 1]
            // need to be increased.
            int toBeIncreasedPos = pos1 - 1;
            char toBeIncreasedDigit = perm[toBeIncreasedPos];
            
            // Look for the smallest digit larger than toBeIncreasedDigit to the
            // right.
            int pos2 = n;
            while (perm[pos2] < toBeIncreasedDigit) {
                --pos2;
            }
            // pos2 to be switched with toBeincreasedPos.
            {
                char temp;
                temp = perm[pos2];
                perm[pos2] = perm[toBeIncreasedPos];
                perm[toBeIncreasedPos] = temp;
            }
            // Reverse all digits to the right of toBeIncreasedPos.
            int pos3 = toBeIncreasedPos + 1;
            int pos4 = n;
            while (pos3 < pos4) {
                char temp;
                temp = perm[pos3];
                perm[pos3] = perm[pos4];
                perm[pos4] = temp;
                ++pos3;
                --pos4;
            }
        }
    }
    
    std::cout << "max: " << maxPandigitalPrime << std::endl;
    
    return 0;
}