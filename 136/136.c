/**
 * 136.c
 * Project Euler Prbl 136
 * Created by Zhiming Wang on 02/22/2014.
 * --------------------------------------
 * (4d - x) x = n < N = 50000000, where 0 < d < x.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define N 50000000

int count[N] = {0};

int main(int argc, const char *argv[]) {
    long d;
    long prod;
    for (long x = 1; x < N; x++) {
        d = x / 4 + 1;
        while ((d < x) && (prod = (4 * d - x) * x) < N) {
            count[prod]++;
            d++;
        }
    }
    long nUnique = 0;
    for (long n = 1; n < N; n++) {
        if (count[n] == 1) {
            nUnique++;
        }
    }
    printf("%ld\n", nUnique);
    return 0;
}
