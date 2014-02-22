/**
 * 127.c
 * Project Euler Prbl 127.
 * Created by Zhiming Wang on 02/21/2014.
 * --------------------------------------
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "read-rad.h"

long gcd(long a, long b) {
    long tmp;
    if (a < b) {
        tmp = a; a = b; b = tmp;
    } // after this we have a >= b
    while (b != 0) {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main(int argc, const char *argv[]) {
    read_rad();
    
    long counter = 0;
    long sumc = 0;

    for (long c = 1; c < N; c++) {
        long cutoff = c / 2;
        long a, b, stepsize;
        // if c is even, then we can advance a at a stepsize of 2, since
        // a and b must be both odd.
        stepsize = (c % 2 == 0) ? 2 : 1;
        for (a = 1; a <= cutoff; a += stepsize) {
            b = c - a;
            if (_rad[a] * _rad[b] * _rad[c] < c && gcd(a, b) == 1) {
                printf("%ld, %ld, %ld (%ld, %ld, %ld)\n",
                       a, b, c, _rad[a], _rad[b], _rad[c]);
                counter++;
                sumc += c;
            }
        }
    }
    printf("counter: %ld\n", counter);
    printf("sumc: %ld\n", sumc);

    return 0;
}
