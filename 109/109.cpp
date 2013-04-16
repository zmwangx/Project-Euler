//
//  main.cpp
//  Prbl109
//  Project Euler
//
//  Created by Zhiming Wang on 12/18/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Exhaustion.
//  -----------
//  Answer: 38182
//

#include <iostream>
#include <vector>

static const int UPPER_BOUND = 100;

int main() {
    std::vector<int> landings;
    // Push in doubles.
    for (int i = 1; i <= 20; ++i) {
        landings.push_back(2 * i);
    }
    landings.push_back(2 * 25);
    // Push in singles.
    for (int i = 1; i <= 20; ++i) {
        landings.push_back(i);
    }
    landings.push_back(25);
    // Push in trebles.
    for (int i = 1; i <= 20; ++i) {
        landings.push_back(3 * i);
    }
    
    int nCheckOuts = 0;
    for (int i = 0; i < 21; ++i) {
        int sum = landings[i];
        if (sum < UPPER_BOUND) {
            ++nCheckOuts;
        }
        for (int j = 0; j < 62; ++j) {
            sum += landings[j];
            if (sum < UPPER_BOUND) {
                ++nCheckOuts;
            }
            for (int k = j; k < 62; ++k) {
                sum += landings[k];
                if (sum < UPPER_BOUND) {
                    ++nCheckOuts;
                }
                sum -= landings[k];
            }
            sum -= landings[j];
        }
    }
    std::cout << nCheckOuts << std::endl;
    
    return 0;
}