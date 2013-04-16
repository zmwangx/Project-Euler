//
//  main.cpp
//  Prbl074
//  Project Euler
//
//  Created by Zhiming Wang on 12/11/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Dinamic programming. Record the length of longest non-repeating chain for
//  all the terms that have been encountered.
//  -----------------------------------------
//  Answer: 402
//

// Test the functionality of <code>chainLengthFrom</code>.
// #define __PRBL073_IS_IN_DEBUGGING_PHASE_01__ 1

#include <iostream>
#include <array>
#include <stack>
#include <set>
#include <string>

static const long RANGE = 1000000;
static const long CHAIN_LENGTH_EXPECTATION = 60;
static const long FACTORIALS[10] =
{1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

static const std::set<long> SINGLE_LOOP_ELEMENTS = {1, 2, 145, 40585};
static const std::set<long> DOUBLE_LOOP_ELEMENTS = {871, 45361, 872, 45362};
static const std::set<long> TRIPLE_LOOP_ELEMENTS = {169, 363601, 1454};

static void initialize(std::array<size_t, RANGE>& chainLength,
                       std::array<bool, RANGE>& visited);
static long chainLengthFrom(long n,
                            std::array<size_t, RANGE>& chainLength,
                            std::array<bool, RANGE>& visited);
static long digitsFactorialSum(long n);

int main() {
    std::array<size_t, RANGE>* chainLengthPtr = new std::array<size_t, RANGE>;
    std::array<size_t, RANGE>& chainLength = *chainLengthPtr;
    std::array<bool, RANGE>* visitedPtr = new std::array<bool, RANGE>;
    std::array<bool, RANGE>& visited = *visitedPtr;
    initialize(chainLength, visited);
    
#ifdef __PRBL073_IS_IN_DEBUGGING_PHASE_01__
    std::cout << chainLengthFrom(145, chainLength, visited) << std::endl;
    std::cout << chainLengthFrom(169, chainLength, visited) << std::endl;
    std::cout << chainLengthFrom(871, chainLength, visited) << std::endl;
    std::cout << chainLengthFrom(872, chainLength, visited) << std::endl;
    std::cout << chainLengthFrom(69, chainLength, visited) << std::endl;
    std::cout << chainLengthFrom(78, chainLength, visited) << std::endl;
    std::cout << chainLengthFrom(540, chainLength, visited) << std::endl;
#endif
    
    size_t maxLength = 0;
    int nExpected = 0;
    for (int n = 1; n < RANGE; ++n) {
        size_t length = chainLengthFrom(n, chainLength, visited);
        if (length > maxLength) {
            maxLength = length;
        }
        if (length == CHAIN_LENGTH_EXPECTATION) {
            ++nExpected;
        }
    }
    std::cout << "maximum chain length: " << maxLength << std::endl;
    std::cout << "number of expected length: " << nExpected << std::endl;
    
    delete chainLengthPtr;
    delete visitedPtr;
    
    return 0;
}

static void initialize(std::array<size_t, RANGE>& chainLength,
                       std::array<bool, RANGE>& visited) {
    for (std::array<size_t, RANGE>::iterator i = chainLength.begin();
         i != chainLength.end();
         ++i) {
        *i = 0;
    }
    for (std::array<bool, RANGE>::iterator i = visited.begin();
         i != visited.end();
         ++i) {
        *i = false;
    }
    
    for (std::set<long>::const_iterator i = SINGLE_LOOP_ELEMENTS.begin();
         i != SINGLE_LOOP_ELEMENTS.end();
         ++i) {
        chainLength[*i] = 1;
        visited[*i] = true;
    }
    for (std::set<long>::const_iterator i = DOUBLE_LOOP_ELEMENTS.begin();
         i != DOUBLE_LOOP_ELEMENTS.end();
         ++i) {
        chainLength[*i] = 2;
        visited[*i] = true;
    }
    for (std::set<long>::const_iterator i = TRIPLE_LOOP_ELEMENTS.begin();
         i != TRIPLE_LOOP_ELEMENTS.end();
         ++i) {
        chainLength[*i] = 3;
        visited[*i] = true;
    }
}

static long chainLengthFrom(long n,
                            std::array<size_t, RANGE>& chainLength,
                            std::array<bool, RANGE>& visited) {
    if (visited[n]) {
        return chainLength[n];
    }
    
    std::stack<long> chain;
    
    long current = n;
    chain.push(n);
    
    size_t currentChainLength;
    bool hasFoundLoop = false;
    while (true) {
        current = digitsFactorialSum(current);
        
        switch (current) {
            case 1 : case 2 : case 145 : case 40585 :
                currentChainLength = 1;
                hasFoundLoop = true;
                break;
                
            case 871 : case 45361 : case 872 : case 45362 :
                currentChainLength = 2;
                hasFoundLoop = true;
                break;
                
            case 169 : case 363601 : case 1454 :
                currentChainLength = 3;
                hasFoundLoop = true;
                break;
                
            default :
                if (current < RANGE && visited[current]) {
                    currentChainLength = chainLength[current];
                    hasFoundLoop = true;
                }
                break;
        }
        if (hasFoundLoop) {
            while (!chain.empty()) {
                long last = chain.top();
                chain.pop();
                ++currentChainLength;
                if (last < RANGE) {
                    visited[last] = true;
                    chainLength[last] = currentChainLength;
                }
            }
            return currentChainLength;
        }
        
        chain.push(current);
    }
}

static long digitsFactorialSum(long n) {
    std::string nString = std::to_string(n);
    long factorialSum = 0;
    for (std::string::const_iterator i = nString.begin();
         i != nString.end();
         ++i) {
        factorialSum += FACTORIALS[*i - '0'];
    }
    return factorialSum;
}