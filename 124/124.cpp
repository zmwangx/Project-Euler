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

#define MAX 100000

int main(int argc, const char *argv[]) {
    return 0;
}
