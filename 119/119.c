/**
 * 119.c
 * Project Euler 119
 * Created by Zhiming Wang on 04/18/2013.
 * --------------------------------------
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#define MAX_POWER ULLONG_MAX // experimental, max 20 digits
#define MAX_BASE 180 // experimental

typedef unsigned long long num_t;

static inline num_t digit_sum(num_t n);

int main(int argc, const char *argv[]) {
    size_t cnt = 0; // counter
    for (num_t base = 2; base <= MAX_BASE; base++) {
        num_t pwr = base;
        while (pwr <= MAX_POWER / base) {
            pwr *= base;
            if (digit_sum(pwr) == base) {
                printf("%llu\n", pwr);
                cnt++;
            }
        }
    }
    printf("count: %zu\n", cnt);
    return 0;
}

static inline num_t
digit_sum(num_t n) {
    num_t sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
