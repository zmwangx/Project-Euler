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

#define NUM_COMPOSITE_VALUES 25

#define MAX 100000 // guessed value

int main(int argc, const char *argv[]) {
    std::vector<int> pvec;
    generatePrimes(pvec, 7, MAX);
    std::set<int> pset;
    std::copy(pvec.begin(), pvec.end(), std::inserter(pset, pset.end()));
    return 0;
}
