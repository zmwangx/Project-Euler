//
//  main.cpp
//  Prbl043
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Search all ppossible permutations.
//  ----------------------------------
//  Answer: 16695334890
//

#include <iostream>
#include <string>

static bool satisfiesDivisibleProperty(const std::string& nString);

int main() {
    // Smallest 0-9 pandigital number. The leftmost digit '0' is a sentinel
    // digit.
    std::string perm = "01023456789";
    long sum = 0;
    while (perm[0] == '0') {
        if (satisfiesDivisibleProperty(perm)) {
            std::cout << perm.substr(1) << std::endl;
            sum += std::atol(perm.c_str());
        }
        
        int pos1 = 10;
        while (perm[pos1 - 1] > perm[pos1]) {
            --pos1;
        }
        int toBeIncreasedPos = pos1 - 1;
        char toBeIncreasedDigit = perm[toBeIncreasedPos];
        
        int pos2 = 10;
        while (perm[pos2] <= toBeIncreasedDigit) {
            --pos2;
        }
        int toBeExchangedPos = pos2;
        {
            char temp;
            temp = perm[toBeExchangedPos];
            perm[toBeExchangedPos] = perm[toBeIncreasedPos];
            perm[toBeIncreasedPos] = temp;
        }
        
        int pos3 = 10;
        int pos4 = toBeIncreasedPos + 1;
        while (pos3 > pos4) {
            char temp;
            temp = perm[pos3];
            perm[pos3] = perm[pos4];
            perm[pos4] = temp;
            --pos3;
            ++pos4;
        }
    }
    
    std::cout << "sum: " << sum << std::endl;
    return 0;
}

static bool satisfiesDivisibleProperty(const std::string& nString) {
    bool satisfies2  = (std::atoi((nString.substr(2, 3)).c_str()) % 2 == 0);
    bool satisfies3  = (std::atoi((nString.substr(3, 3)).c_str()) % 3 == 0);
    bool satisfies5  = (std::atoi((nString.substr(4, 3)).c_str()) % 5 == 0);
    bool satisfies7  = (std::atoi((nString.substr(5, 3)).c_str()) % 7 == 0);
    bool satisfies11 = (std::atoi((nString.substr(6, 3)).c_str()) % 11 == 0);
    bool satisfies13 = (std::atoi((nString.substr(7, 3)).c_str()) % 13 == 0);
    bool satisfies17 = (std::atoi((nString.substr(8, 3)).c_str()) % 17 == 0);
    
    return (satisfies2 && satisfies3 && satisfies5 && satisfies7 &&
            satisfies11 && satisfies13 && satisfies17);
}