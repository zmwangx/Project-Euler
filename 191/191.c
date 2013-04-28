/**
 * 191.c
 * Project Euler 191
 * Created by Zhiming Wang on 04/28/2013.
 * --------------------------------------
 * DP.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define LENGTH 30

#define ull_t unsigned long long

int main(int argc, const char *argv[]) {
    ull_t f1[LENGTH + 1]; // no late, 0 consec absent
    ull_t f2[LENGTH + 1]; // no late, 1 consec absent
    ull_t f3[LENGTH + 1]; // no late, 2 consec absent
    ull_t f4[LENGTH + 1]; // late, 0 consec absent
    ull_t f5[LENGTH + 1]; // late, 1 consec absent
    ull_t f6[LENGTH + 1]; // late, 2 consec absent

    f1[0] = 1;
    f2[0] = 0;
    f3[0] = 0;
    f4[0] = 0;
    f5[0] = 0;
    f6[0] = 0;
    for (size_t i = 0; i <= LENGTH; i++) {
        f1[i] = f1[i-1] + f2[i-1] + f3[i-1];
        f2[i] = f1[i-1];
        f3[i] = f2[i-1];
        f4[i] = f1[i-1] + f2[i-1] + f3[i-1] + f4[i-1] + f5[i-1] + f6[i-1];
        f5[i] = f4[i-1];
        f6[i] = f5[i-1];
    }

    ull_t total =
        f1[LENGTH] + f2[LENGTH] + f3[LENGTH] +
        f4[LENGTH] + f5[LENGTH] + f6[LENGTH];
    printf("%llu\n", total);
    
    return 0;
}
