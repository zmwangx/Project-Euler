//
//  main.cpp
//  Prbl087
//  Project Euler
//
//  Created by Zhiming Wang on 12/13/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Exhaustion. Use set as data structure.
//  --------------------------------------
//  Answer: 1097343
//

#include <iostream>
#include <vector>
#include <set>
#include <cmath>

#include "prime.h"

typedef std::vector<int> Primes;

static const int RANGE = 50000000;

int main() {
    int maxSquareRoot = static_cast<int>(std::floor(std::pow(RANGE, 1.0/2)));
    int maxCubeRoot   = static_cast<int>(std::floor(std::pow(RANGE, 1.0/3)));
    int maxFourthRoot = static_cast<int>(std::floor(std::pow(RANGE, 1.0/4)));
    
    Primes squareRootPrimes;
    Primes cubeRootPrimes  ;
    Primes fourthRootPrimes;
    generatePrimes(squareRootPrimes, 1, maxSquareRoot);
    generatePrimes(cubeRootPrimes  , 1, maxCubeRoot  );
    generatePrimes(fourthRootPrimes, 1, maxFourthRoot);
    
    std::set<int> sums;
    
    for (Primes::const_iterator squareRootIt = squareRootPrimes.begin();
         squareRootIt != squareRootPrimes.end();
         ++squareRootIt) {
        for (Primes::const_iterator cubeRootIt = cubeRootPrimes.begin();
             cubeRootIt != cubeRootPrimes.end();
             ++cubeRootIt) {
            for (Primes::const_iterator fourthRootIt = fourthRootPrimes.begin();
                 fourthRootIt != fourthRootPrimes.end();
                 ++fourthRootIt) {
                int sum = static_cast<int>(std::pow(*squareRootIt, 2.0)) +
                          static_cast<int>(std::pow(*cubeRootIt, 3.0)) +
                          static_cast<int>(std::pow(*fourthRootIt, 4.0));
                if (sum < RANGE) {
                    sums.insert(sum);
                }
            }
        }
    }
    
    std::cout << sums.size() << std::endl;
    
    return 0;
}