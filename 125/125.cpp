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
#include <cmath>

#define MAX_PALIN 100000000
#define MAX_N (int(std::sqrt(MAX_PALIN / 2)) + 1)

typedef signed long long sum_t;

static bool is_palin(sum_t s);

int main(int argc, const char *argv[]) {
    // compute master square sums
    sum_t s[MAX_N + 1]; // square sums from 1
    s[0] = 0;
    for (int i = 1; i <= MAX_N; i++) {
        s[i] = s[i - 1] + i * i;
    }
    // consider all differences
    // record the palins in a set
    std::set<sum_t> palins;
    for (int i = 0; i <= MAX_N - 2; i++) {
        for (int j = i + 2; j <= MAX_N; j++) {
            sum_t diff = s[j] - s[i];
            if (diff >= MAX_PALIN) {
                continue;
            } else if (is_palin(diff)) {
                palins.insert(diff);
            }
        }
    }
    // compute sum
    sum_t totalSum = 0;
    for (auto s: palins) {
        std::cout << s << std::endl;
        totalSum += s;
    }
    std::cout << totalSum << std::endl;
    return 0;
}

static bool
is_palin(sum_t s) {
    std::string st = std::to_string(s);
    auto i = st.begin();   // normal order
    auto j = st.end() - 1; // reverse order
    for (; i < j; i++, j--) {
        if (*i != *j) {
            return false;
        }
    }
    return true;
}
