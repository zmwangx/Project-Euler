/**
 * 133.cpp
 * Project Euler 133
 * Created by Zhiming Wang on 04/22/2013.
 * --------------------------------------
 * Number theory.
 *
 * Clearly p = 2, 3, and 5 won't work. For prime p > 5,
 *     p | (10^{10^n} - 1) / 9,
 * if and only if
 *     10^{10^n} = 1 (mod p).
 *
 * By Fermat little theorem,
 *     10^{p-1} = 1 (mod p),
 * so suppose
 *     p-1 = 2^a 5^b c,
 * where c is not divided by 2 or 5, then the desired n exists if and only if
 *     10^{2^a 5^b} = 1 (mod p).
 */

#include "../Library/prime.h"
#include "../Library/modulo.h"

#include <iostream>
#include <string>

int main(int argc, const char *argv[]) {
    
    return 0;
}
