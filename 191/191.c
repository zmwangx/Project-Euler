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
    
    return 0;
}
