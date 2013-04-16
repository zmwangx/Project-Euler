//
//  main.cpp
//  Prbl031
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Recursive backtracking.
//  -----------------------
//  Answer: 73682
//

#include <iostream>

const int NUMBER_OF_COIN_VALUES = 8;
const int COIN_VALUES[NUMBER_OF_COIN_VALUES] = {200, 100, 50, 20, 10, 5, 2, 1};

const int TARGET_VALUE = 200;

static int searchValueRepresentations(int targetValue, int maxCoin);

int main() {
    std::cout << searchValueRepresentations(TARGET_VALUE, 0) << std::endl;
    return 0;
}

/**
 * Searches all possible means of representing <code>targetValue</code> with 
 * coins no larger than <code>COIN_VALUES[maxCoin]</code> in value.
 */
static int searchValueRepresentations(int targetValue, int maxCoin) {
    if (targetValue == 0) {
        return 1;
    }
    // Check if there are no coins available.
    if (maxCoin >= NUMBER_OF_COIN_VALUES) {
        return 0;
    }
    
    int nRepresentations = 0;
    int maxCoinValue = COIN_VALUES[maxCoin];
    if (targetValue % maxCoinValue == 0) {
        ++nRepresentations;
    }
    for (int nMaxCoin = 0; nMaxCoin * maxCoinValue < targetValue; ++nMaxCoin) {
        nRepresentations += searchValueRepresentations
        (targetValue - nMaxCoin * maxCoinValue, maxCoin + 1);
    }
    return nRepresentations;
}