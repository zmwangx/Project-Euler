/**
 * 126.c
 * Project Euler Problem 126
 * Created by Zhiming Wang on 07/21/2013.
 * --------------------------------------
 * Formula:
 * For a cuboid of dimensions a*b*c, its k-th layer consumes:
 * 2(ab+bc+ca) + 4(k-1)(a+b+c) + (4k^2-12k+8).
 *
 * Answer:
 * 18522.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define CONSUMPTION_ESTIMATE 20000
#define TARGET_COUNT 1000

static long layer(long a, long b, long c, long k);

int main(int argc, const char *argv[]) {
    long count[CONSUMPTION_ESTIMATE + 1];
    memset(count, 0, sizeof(count));
    for (long a = 1; a <= CONSUMPTION_ESTIMATE; a++) {
        // check if a*1*1 exceeds range
        if (layer(a, 1, 1, 1) > CONSUMPTION_ESTIMATE) {
            break;
        }
        
        for (long b = 1; b <= a; b++) {
            // check if a*b*1 exceeds range
            if (layer(a, b, 1, 1) > CONSUMPTION_ESTIMATE) {
                break;
            }

            for (long c = 1; c <= b; c++) {
                long k = 1;
                for (;;) {
                    long consumption = layer(a, b, c, k);
                    if (consumption > CONSUMPTION_ESTIMATE) {
                        break;
                    }
                    count[consumption]++;
                    k++;
                }
            }
        }
    }
    for (long i = 1; i <= CONSUMPTION_ESTIMATE; i++) {
        if (count[i] == TARGET_COUNT) {
            printf("%ld\n", i);
            exit(0);
        }
    }
    for (long i = 1; i <= CONSUMPTION_ESTIMATE; i++) {
        printf("%ld\t", count[i]);
        if (i % 10 == 0) {
            putchar('\n');
        }
    }
    printf("not yet!\n");
    return 0;
}

static long layer(long a, long b, long c, long k) {
    return 2 * (a*b + b*c + c*a) + 4 * (k-1) * (a+b+c) + (4*k*k - 12*k + 8);
}
