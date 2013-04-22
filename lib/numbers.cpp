/**
 * numbers.cpp
 * Project Euler shared libraries
 * Created by Zhiming Wang on 04/22/2013.
 * --------------------------------------
 * Implementation of numbers.h.
 */

#include "numbers.h"

#include <cmath>

/**
 * Length of positive integer.
 */
extern size_t
num_length(arith_t n) {
    return std::floor(std::log(n) / std::log(10.0)) + 1;
}

/**
 * Power of 10: 10^k.
 */
extern arith_t
pwr10(size_t k) {
    arith_t pwr = 1;
    for (size_t i = 0; i < k; i++) {
        pwr *= 10;
    }
    return pwr;
}
