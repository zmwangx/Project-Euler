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
#include <map>

#define TOTAL 1000000

#define llong long long

int main(int argc, const char *argv[]) {
    std::map<llong, int> numTilesRecord;
    llong maxM;
    llong minN;
    llong maxN;
    // (1) even
    maxM = (TOTAL + 4) / 8;
    for (llong m = 2; m <= maxM; ++m) {
        if ((2*m)*(2*m) <= TOTAL) {
            minN = 1;
        } else {
            minN = std::ceil(std::sqrt(m*m - TOTAL/4));
        }
        maxN = m - 1;
        for (llong n = minN; n <= maxN; ++n) {
            ++numTilesRecord[(2*m)*(2*m) - (2*n)*(2*n)];
        }
    }
    // (2) odd
    maxM = (TOTAL + 8) / 8;
    for (llong m = 2; m <= maxM; ++m) {
        if ((2*m-1)*(2*m-1) <= TOTAL) {
            minN = 1;
        } else {
            minN = std::ceil(std::sqrt((m-0.5)*(m-0.5) - TOTAL/4) + 0.5);
        }
        maxN = m - 1;
        for (llong n = minN; n <= maxN; ++n) {
            ++numTilesRecord[(2*m-1)*(2*m-1) - (2*n-1)*(2*n-1)];
        }
    }
    // count types
    std::map<int, int> typesRecord;
    for (auto entry: numTilesRecord) {
        // entry.first:  number of tiles
        // entry.second: number of possible laminae
        typesRecord[entry.second]++;
    }
    int sum = 0;
    for (int n = 1; n <= 10; n++) {
        sum += typesRecord[n];
    }
    std::cout << sum << std::endl;
    return 0;
}
