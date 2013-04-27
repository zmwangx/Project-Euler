/**
 * 130.cpp
 * Project Euler 130
 * Created by Zhiming Wang on 04/27/2013.
 * --------------------------------------
 * NT library call.
 */

#include "../lib/prime.h"
#include "../lib/modulo.h"

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <iterator>
#include <algorithm>

#define NUM_VALUES_EXPECTED 25

#define MIN 7
#define MAX 100000 // guessed value

int main(int argc, const char *argv[]) {
    std::vector<int> pvec;
    generatePrimes(pvec, MIN, MAX);
    std::set<int> pset;
    std::copy(pvec.begin(), pvec.end(), std::inserter(pset, pset.end()));

    int sum = 0;
    size_t num = 0;
    for (int n = MIN; n < MAX; n++) {
        if (n % 2 != 0 && n % 5 != 0 && !pset.count(n)) {
            if (pwrmod(10, n-1, 9 * n) == 1) {
                sum += n;
                num++;
                std::cout << num << ": " << n << std::endl;
                if (num == NUM_VALUES_EXPECTED) {
                    break;
                }
            }
        }
    }
    std::cout << sum << std::endl;
    
    return 0;
}
