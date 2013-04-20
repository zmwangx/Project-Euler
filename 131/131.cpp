/**
 * 131.cpp
 * Project Euler 131
 * Created by Zhiming Wang on 04/20/2013.
 * --------------------------------------
 * n^3 + p n^2 = m^3
 * -->
 * n^2 (n + p) = m^3
 * -->
 * n^2 = m1^6
 * n + p = m2^3
 * -->
 * m1^3 + p = m2^3
 * -->
 * p = (m2 - m1)(m2^2 + m2 m1 + m1^2)
 * -->
 * m2 = m1 + 1
 * p = 3 m1 (m1 + 1) + 1
 */

#include "../Library/prime.h"

#include <iostream>
#include <fstream>
#include <string>

#define MAX 1000000

int main(int argc, const char *argv[]) {
    size_t num = 0;
    int p;
    for (int m1 = 1; (p = 3 * m1 * (m1 + 1) + 1) < MAX; m1++) {
        if (isPrime(p)) {
            num++;
        }
    }
    std::cout << num << std::endl;
    return 0;
}
