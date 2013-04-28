/**
 * 173.c
 * Project Euler 173
 * Created by Zhiming Wang on 04/27/2013.
 * --------------------------------------
 * There are two kinds of laminas:
 * (1) (2m)^2 - (2n)^2;
 * (2) (2m-1)^2 - (2n-1)^2.
 *
 *
 * For (1), given an m,
 *     (2m)^2 - (2n)^2 <= TOTAL
 * gives
 *     2n >= sqrt(TOTAL - (2m)^2),
 * so
 *     n >= ceil(sqrt(TOTAL/4 - m^2)).
 * Also note that n <= m-1, so there are
 *     m - (int) ceil(sqrt(TOTAL/4 - m^2))
 * possibilities in total.
 *
 *
 * For (2), given an m,
 *     (2m-1)^2 - (2n-1)^2 <= TOTAL
 * gives
 *     2n-1 >= sqrt(TOTAL - (2m-1)^2),
 * so
 *     n >= ceil(sqrt(TOTAL/4 - (m-1/2)^2) + 1/2).
 * Also note that n <= m-1, so there are
 *     m - (int) ceil(sqrt(TOTAL/4 - (m-1/2)^2) + 1/2)
 * possibilities in total.
 *
 *
 * At last, for (1),
 *     (2m)^2 - (2m-2)^2 <= TOTAL
 * gives
 *     m <= (TOTAL+4)/8.
 * And for (2),
 *     (2m-1)^2 - (2m-3)^2 <= TOTAL
 * gives
 *     m <= (TOTAL+8)/8.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

int main(int argc, const char *argv[]) {
    return 0;
}
