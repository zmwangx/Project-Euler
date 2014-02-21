/**
 * decide-range.c
 * Project Euler Prbl 127
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

int main(int argc, const char *argv[]) {
    read_rad();
    printf("enter the threshold value c/rad(c):\n");
    long threshold;
    scanf("%ld", &threshold);
    long counter = 0;
    for (int c = 1; c <= N; c++) {
        if (_rad[c] * threshold < c) {
            counter++;
        }
    }
    printf("number of c's that passed the threshold: %ld\n", counter);
    return 0;
}
