/**
 * 179.cpp
 * Project Euler 179
 * Created by Zhiming Wang on 04/27/2013.
 * --------------------------------------
 * Brute force all number of divisors.
 */

#include "../lib/prime.h"

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <iterator>
#include <algorithm>

#define MAX 10000000
#define MAX_SQRT 3162

int main(int argc, const char *argv[]) {
    std::vector<int> pvec;
    std::set<int> pset;
    generatePrimes(pvec, 2, MAX);
    std::copy(pvec.begin(), pvec.end(), std::inserter(pset, pset.end()));

    std::vector<int> pvecl; // lite vector; only up to MAX_SQRT for speed
                            // concern
    generatePrimes(pvecl, 2, MAX_SQRT);
    return 0;
}
