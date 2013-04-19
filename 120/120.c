/**
 * 120.c
 * Project Euler 120
 * Created by Zhiming Wang on 04/18/2013.
 * --------------------------------------
 * Brute force.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MIN_A 3
#define MAX_A 1000

int main(int argc, const char *argv[]) {
    unsigned sum = 0;
    for (unsigned a = MIN_A; a <= MAX_A; a++) {
        unsigned mod = a * a;
        unsigned t1 = 1;
        unsigned t2 = 1;
        unsigned n = 0;
        unsigned maxRemainder = 0;
        while (n < mod) {
            unsigned remainder = (t1 + t2) % mod;
            if (remainder > maxRemainder) {
                maxRemainder = remainder;
            }
            t1 = (a - 1) * t1 % mod;
            t2 = (a + 1) * t2 % mod;
            n++;
        }
        sum += maxRemainder;
    }
    printf("%u\n", sum);
    return 0;
}
