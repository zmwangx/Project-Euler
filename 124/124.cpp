/**
 * 124.cpp
 * Project Euler 124
 * Created by Zhiming Wang on 04/22/2013.
 * --------------------------------------
 * Brute force.
 *
 * rad(n) = n,          if n is prime;
 *          rad(n/p),   if p^2 | n;
 *          p rad(n/p), if p | n but p^2 !| n.
 * Since we can easily pick primes with sieve, the algorithm is basically
 * O(n^{3/2}).
 */

#include "../lib/prime.h"

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>

#define MAX 100000
#define ORDER 10000

typedef struct {
    int n;
    int rad;
} rad_t;

static bool
cmp(const rad_t &a, const rad_t &b) {
    // the cmp function should be equivalent to:
    // if (a.rad == b.rad) {
    //     return (a.n < b.n);
    // } else {
    //     return (a.rad < b.rad);
    // }
    return (a.rad == b.rad) ? (a.n < b.n) : (a.rad < b.rad);
}

int main(int argc, const char *argv[]) {
    std::vector<int> pvec;
    generatePrimes(pvec, 1, MAX);
    // convert to set
    std::set<int> pset;
    for (auto p: pvec) {
        pset.insert(p);
    }
    
    std::vector<rad_t> rad(MAX + 1);
    for (int n = 0; n <= MAX; n++) {
        rad[n].n = n;
    }
    rad[0].rad = 0; // so that this meaningless placeholder still appear at 0
                    // when the whole vector gets sorted
    rad[1].rad = 1;
    for (int n = 2; n <= MAX; n++) {
        if (pset.find(n) != pset.end()) {
            // is prime
            rad[n].rad = n;
        }
        for (auto p: pvec) {
            if (n % p == 0) {
                if (n % (p * p) == 0) {
                    rad[n].rad = rad[n / p].rad;
                } else {
                    rad[n].rad = p * rad[n / p].rad;
                }
                break;
            }
        }
    }
    std::sort(rad.begin(), rad.end(), cmp);
    std::cout << rad[ORDER].n << std::endl;
    
    return 0;
}
