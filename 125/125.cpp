/**
 * 125.cpp
 * Project Euler 125
 * Created by Zhiming Wang on 04/22/2013.
 * --------------------------------------
 * We record sums s[n] = \sum{k=1}^n k^2 (0 <= n < 10^4 since (10^4)^2 = 10^8),
 * and then compute all s[j] - s[i] (j - i >= 2). The number of iterations is
 * at most of order 10^8.
 *
 * To pick out the palins, we use std::set to track all palins we have got thus
 * far.
 *
 * Pratically we only need n <= sqrt(MAX/2) + 1 since a single square is not
 * considered the sum of consecutive squares
 */

#include <set>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, const char *argv[]) {
    return 0;
}
