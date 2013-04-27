/**
 * 205.c
 * Project Euler 205
 * Created by Zhiming Wang on 04/27/2013.
 * --------------------------------------
 * Brute force counting.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_SUM 36
#define NUM_BASE4 9
#define MAX_BASE4 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4 * 4
#define NUM_BASE6 6
#define MAX_BASE6 6 * 6 * 6 * 6 * 6 * 6

int main(int argc, const char *argv[]) {
    size_t base4SumNum[MAX_SUM + 1] = {0};
    size_t base6SumNum[MAX_SUM + 1] = {0};
    
    // base 4 numbers
    for (int n = 0; n < MAX_BASE4; n++) {
        size_t sum = 0;
        for (int i = 0; i < NUM_BASE4; i++) {
            sum += n % 4;
            n /= 4;
        }
        base4SumNum[sum]++;
    }
    // base 6 numbers
    for (int n = 0; n < MAX_BASE6; n++) {
        size_t sum = 0;
        for (int i = 0; i < NUM_BASE6; i++) {
            sum += n % 6;
            n /= 6;
        }
        base6SumNum[sum]++;
    }
    
    return 0;
}
