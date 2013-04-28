/**
 * 174.cpp
 * Project Euler 174
 * Created by Zhiming Wang on 04/28/2013.
 * --------------------------------------
 * The following comments are loaded from ../173/173.c. For this problem we
 * only need to further record each exact number of tiles.
 *
 *
 * There are two kinds of laminas:
 * (1) (2m)^2 - (2n)^2;
 * (2) (2m-1)^2 - (2n-1)^2.
 *
 *
 * For (1), given an m,
 *     (2m)^2 - (2n)^2 <= TOTAL
 * gives (in case of (2m)^2 > TOTAL)
 *     2n >= sqrt((2m)^2 - TOTAL),
 * so
 *     n >= ceil(sqrt(m^2 - TOTAL/4)).
 * Also note that n <= m-1, so there are
 *     m - (int) ceil(sqrt(m^2 - TOTAL/4))
 * possibilities in total.
 *
 *
 * For (2), given an m,
 *     (2m-1)^2 - (2n-1)^2 <= TOTAL
 * gives (in case of (2m-1)^2 > TOTAL)
 *     2n-1 >= sqrt((2m-1)^2 - TOTAL),
 * so
 *     n >= ceil(sqrt((m-1/2)^2 - TOTAL/4) + 1/2).
 * Also note that n <= m-1, so there are
 *     m - (int) ceil(sqrt((m-1/2)^2 - TOTAL/4) + 1/2)
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

#include <iostream>
#include <cmath>

#define TOTAL 1000000

#define llong long long

int main(int argc, const char *argv[]) {
    llong counter = 0;
    // (1) even
    llong maxM = (TOTAL + 4) / 8;
    for (llong m = 2; m <= maxM; m++) {
        if ((2*m)*(2*m) <= TOTAL) {
            counter += m-1;
        } else {
            counter += m - ceil(sqrt(m*m - TOTAL/4));
        }
    }
    // (2) odd
    maxM = (TOTAL + 8) / 8;
    for (llong m = 2; m <= maxM; m++) {
        if ((2*m-1)*(2*m-1) <= TOTAL) {
            counter += m-1;
        } else {
            counter += m - ceil(sqrt((m-0.5)*(m-0.5) - TOTAL/4) + 0.5);
        }
    }
    printf("%lld\n", counter);
    return 0;
}
