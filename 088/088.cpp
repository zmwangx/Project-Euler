//
//  main.cpp
//  Prbl088
//  Project Euler
//
//  Created by Zhiming Wang on 12/15/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  For every k, the minimum will never exceed 2k = 1 + ... + 1 + 2 + k. So for
//  k <= MAX_K, the number of greater-than-one elements cannot exceed
//  \floor{\log_2 (2 MAX_K)}}. Therefore we can exhaust all possible
//  combinations. Note that for a set of greater-than-one numbers b_1, ..., b_m,
//  where b_m <= ... <= b_1, the corresponding number of ones is
//
//  k - m = b_m...b_1 - (b_m + ... + b_1),
//
//  So
//
//  k = b_m...b_1 - (b_m + ... + b_1) + m.
//
//  Also, as a reminder, we use vector to model the stack for exhausting
//  b_1, ..., b_m. The vector is reversed: the top of the stack is the first
//  element of the vector when elements are complete; then poping elements will
//  move the <code>currentTop</code> iterator toward the end of vector.
//  -------------------------------------------------------------------
//  Answer: 7587457
//

#include <iostream>
#include <cmath>
#include <vector>
#include <set>

static const int MAX_K = 12000;
static const int MAX_M = std::floor(std::log(MAX_K * 2) / std::log(2));

int main() {
    std::vector<int> stack;
    for (int i = 1; i <= MAX_M + 1; ++i) {
        stack.push_back(1);
    }
    
    std::vector<int> minProductSumNumber;
    // k = 0 or 1 is meaningless.
    for (int k = 0; k <= MAX_K; ++k) {
        minProductSumNumber.push_back(2 * k);
    }
    
    int product = 1;
    int sum = 0;
    int m = 1;
    std::vector<int>::iterator stackTop = stack.begin();
    std::vector<int>::iterator currentTop = stackTop;
    while (true) {
        while (true) {
            if (*currentTop != 1) {
                product /= *currentTop;
                sum     -= *currentTop;
            }
            int value = (*currentTop) + 1;
            ++currentTop;
            int nLack = static_cast<int>(currentTop - stackTop);
            if (nLack > MAX_M) {
                // The value of m exceeds MAX_M.
                break;
            }
            int minimalProductUnderCondition =
            product * static_cast<int>(std::pow(value, nLack));
            if (minimalProductUnderCondition <= 2 * MAX_K) {
                if (nLack > m) {
                    m = nLack;
                }
                while (currentTop != stackTop) {
                    --currentTop;
                    *currentTop = value;
                    product *= value;
                    sum += value;
                }
                break; // A new possible combination is found and updated.
            }
        }
        
        if (currentTop != stackTop) {
            // The value of m has exceeded MAX_M.
            break;
        }
                
        if (product >= sum) {
            int k = product - sum + m;
            if (product < minProductSumNumber[k]) {
                minProductSumNumber[k] = product;
            }
        }
    }
    
    std::set<int> minProductSumNumberSet;
    for (int k = 2; k <= MAX_K; ++k) {
        minProductSumNumberSet.insert(minProductSumNumber[k]);
    };
    
    int sumMinProductSumNumbers = 0;
    for (std::set<int>::const_iterator i = minProductSumNumberSet.begin();
         i != minProductSumNumberSet.end();
         ++i) {
        sumMinProductSumNumbers += *i;
    }
    std::cout << sumMinProductSumNumbers << std::endl;
    
    return 0;
}