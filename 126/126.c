/**
 * 126.c
 * Project Euler Problem 126
 * Created by Zhiming Wang on 07/21/2013.
 * --------------------------------------
 * Formula:
 * For a cuboid of dimensions a*b*c, its k-th layer consumes:
 * 2(ab+bc+ca) + 4(k-1)(a+b+c) + (4k^2-12k+8).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define ESTIMATE 1000

static long layer(long a, long b, long c, long k);

int main(int argc, const char *argv[]) {
    long count[ESTIMATE + 1];
    memset(count, 0, sizeof(count));
    for (long a = 1; a <= ESTIMATE; a++) {
        // check if a*1*1 exceeds range
        if (layer(a, 1, 1, 1) > ESTIMATE) {
            break;
        }
        
        for (long b = 1; b <= a; b++) {
            // check if a*b*1 exceeds range
            if (layer(a, b, 1, 1) > ESTIMATE) {
                break;
            }

            for (long c = 1; c <= b; c++) {
                long k = 1;
                for (;;) {
                    long consumption = layer(a, b, c, k);
                    if (consumption > ESTIMATE) {
                        break;
                    }
                    count[consumption]++;
                    k++;
                }
            }
        }
    }
    return 0;
}

static long layer(long a, long b, long c, long k) {
    return 2 * (a*b + b*c + c*a) + 4 * (k-1) * (a+b+c) + (4*k*k - 12*k + 8);
}
