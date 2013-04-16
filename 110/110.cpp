//
//  main.cpp
//  Prbl110
//  Project Euler
//
//  Created by Zhiming Wang on 12/17/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  To achieve SOLUTION_NUMBER_EXPECTATION solutions, we need to find n such
//  that d(n^2) >= 2 * SOLUTION_NUMBER_EXPECTATION + 1. For the minimum n, n
//  must be in the form 2^k1 * 3^k2 * 5^k3 * ... and k1 >= k2 >= k3 >= ..., so
//  that d(n^2) = (2*k1+1) * (2*k2+1) * (2*k3+1) * ... >=
//  DIVISOR_NUMBER_EXPECTATION. So the number of prime divisors cannot exceed
//  \left\lceil log_3 DIVISOR_NUMBER_EXPECTATION \right\rceil.
//
//  Therefore, we can exhaust the possible combinations of k1, k2, k3, ... and
//  find the minimum.
//  -----------------
//  Answer: 9350130049860600
//

#include <iostream>
#include <vector>
#include <cmath>

static const int SOLUTION_NUMBER_EXPECTATION = 4000000;
static const int DIVISOR_NUMBER_EXPECTATION =
2 * SOLUTION_NUMBER_EXPECTATION + 1;
static const int MAX_NUMBER_OF_PRIME_DIVISORS =
static_cast<int>(std::ceil(std::log(DIVISOR_NUMBER_EXPECTATION)/std::log(3)));

static const std::vector<int> PRIMES =
{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
static const std::vector<double> PRIME_LOGS = {
    std::log(2),    std::log(3),    std::log(5),    std::log(7),
    std::log(11),   std::log(13),   std::log(17),   std::log(19),
    std::log(23),   std::log(29),   std::log(31),   std::log(37),
    std::log(41),   std::log(43),   std::log(47),   std::log(53),
};

static double minLogNUnderConstraint(int contributionProduct, double log,
                                     int& exponentOfTwo);
static int oddCeiling(double x);

int main() {
    // Initialization
    std::vector<int> exponents(MAX_NUMBER_OF_PRIME_DIVISORS + 1, 0);
    // exponentsPos is the indicator of the top of components stack. When the
    // exponents stack is full, the pos is 1 (we do not consider exponents[0],
    // the ideal slot left for exponent of 2, as part of the stack, since this
    // exponent is determined by other exponents.
    int kExponentsFullPos = 1;
    int exponentsPos = kExponentsFullPos;
    // (2k_t + 1) * (2k_{t+1} + ) * ...
    int contributionProduct = 1;
    // Natural logarithm of the number formed by all current stack elements.
    // When stack is full, log is the natural logarithm of 3^k2 * 5^k3 * ... and
    // adding the log of 2^k1 yields log(n).
    double log = 0;
    
    double globalMinLogN = DIVISOR_NUMBER_EXPECTATION * std::log(2);
    std::vector<int> globalMinExponents;
    
    while (true) {
        int exponentOfTwo;
        double minLogN = minLogNUnderConstraint(contributionProduct, log,
                                                exponentOfTwo);
        exponents[0] = exponentOfTwo;
        
        if (minLogN < globalMinLogN) {
            globalMinLogN = minLogN;
            globalMinExponents = exponents;
        }
        
        // Pop
        int top;
        while (true) {
            top = exponents[exponentsPos];
            contributionProduct /= (2 * top + 1);
            log -= PRIME_LOGS[exponentsPos] * top;
            ++exponentsPos;
            
            if (exponentsPos == MAX_NUMBER_OF_PRIME_DIVISORS) {
                break;
            }
            
            if (std::pow(2 * top + 3, exponentsPos - kExponentsFullPos) *
                (2 * top + 1) * contributionProduct <=
                DIVISOR_NUMBER_EXPECTATION) {
                break;
            }
        }
        
        if (exponentsPos == MAX_NUMBER_OF_PRIME_DIVISORS) {
            break;
        }
        
        int newTop = top + 1;
        while (exponentsPos > kExponentsFullPos) {
            --exponentsPos;
            exponents[exponentsPos] = newTop;
            contributionProduct *= (2 * newTop + 1);
            log += PRIME_LOGS[exponentsPos] * newTop;
        }
    }
    
    std::cout << PRIMES[0] << "^" << globalMinExponents[0];
    for (int i = 1; i < globalMinExponents.size(); ++i) {
        if (globalMinExponents[i] == 0) {
            break;
        }
        std::cout << " * " << PRIMES[i] << "^" << globalMinExponents[i];
    }
    std::cout << std::endl;
    
    return 0;
}

static double minLogNUnderConstraint(int contributionProduct, double log,
                                     int& exponentOfTwo) {
    int contributionOfTwo =
    oddCeiling(static_cast<double>(DIVISOR_NUMBER_EXPECTATION + 1) /
               contributionProduct);
    exponentOfTwo = (contributionOfTwo - 1) / 2;
    return log + PRIME_LOGS[0] * exponentOfTwo;
}

static int oddCeiling(double x) {
    int ceiling = static_cast<int>(std::ceil(x));
    if (ceiling % 2 == 1) {
        return ceiling;
    } else {
        return ceiling + 1;
    }
}