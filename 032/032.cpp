//
//  main.cpp
//  Prbl032
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Suppose that multiplicand and multiplier have $d_1$ and $d_2$ digits,
//  respectively. Then the number of digits $d$ in product satisfy:
//
//  d_1 + d_2 - 1 \leq d \leq d_1 + d_2.
//
//  Since $d_1 + d_2 + d = 9$, we have $d_1 + d_2 = 5$ and $d = 4$. Then we only
//  need to search through all possible combinations of multiplicand and
//  multiplier with ${d_1, d_2} = {1, 4}$ or ${2, 3}$.
//  --------------------------------------------------
//  Answer: 45228
//

#include <iostream>
#include <set>
#include <string>

static bool isPandigitalIndentity(int multiplicand, int multiplier,
                                  int product);
static void insertDigits(int n, std::set<char>& digits);

int main() {
    std::set<int> products;
    
    for (int multiplicand = 1; multiplicand <= 9; ++multiplicand) {
        for (int multiplier = 1000; multiplier <= 9999; ++multiplier) {
            int product = multiplicand * multiplier;
            if (isPandigitalIndentity(multiplicand, multiplier, product)) {
                products.insert(product);
                std::cout << multiplicand << ' ' << multiplier << ' '
                          << product << std::endl;
            }
        }
    }
    
    for (int multiplicand = 10; multiplicand <= 99; ++multiplicand) {
        for (int multiplier = 100; multiplier <= 999; ++multiplier) {
            int product = multiplicand * multiplier;
            if (isPandigitalIndentity(multiplicand, multiplier, product)) {
                products.insert(product);
                std::cout << multiplicand << ' ' << multiplier << ' '
                          << product << std::endl;
            }
        }
    }

    int productsSum = 0;
    for (std::set<int>::const_iterator i = products.begin();
         i != products.end();
         ++i) {
        productsSum += *i;
    }
    std::cout << "sum: " << productsSum << std::endl;
    
    return 0;
}

static bool isPandigitalIndentity(int multiplicand, int multiplier,
                                  int product) {
    // First, product must have exactly four digits.
    if (product > 10000) {
        return false;
    }
    
    std::set<char> digits;
    insertDigits(multiplicand,  digits);
    insertDigits(multiplier,    digits);
    insertDigits(product,       digits);
    
    bool containsZero = (digits.find('0') != digits.end());
    bool containsNineDigits = (digits.size() == 9);
    if (!containsZero && containsNineDigits) {
        return true;
    } else {
        return false;
    }
}

static void insertDigits(int n, std::set<char>& digits) {
    std::string nString = std::to_string(n);
    digits.insert(nString.begin(), nString.end());
}