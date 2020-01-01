#include <algorithm>
#include <cassert>
#include <iostream>

#define MAX_PERIM 55106

int main()
{
    unsigned long long count = 0;
    for (long d = 3; d <= 2 * MAX_PERIM / 3 - 1; ++d) {
        long amax = std::min(d - 2, MAX_PERIM - d - 2);
        long amin = std::max(d - MAX_PERIM / 3, 1L);
        for (long a = amin; a <= amax; ++a) {
            long bmax = std::min(a, d - 1 - a);
            long bmin = std::max((3 * d - MAX_PERIM - a + 1) / 2, 1L);
            assert(bmax >= bmin);
            if (bmin <= 1) {
                count += bmax * (bmax + 1) / 2;
            } else {
                long b0 = 3 * d - MAX_PERIM - a - 1;
                assert(b0 >= bmin);
                if (b0 >= bmax) {
                    count += (bmax - bmin + 1) * (bmax + bmin + a + MAX_PERIM + 1 - 3 * d);
                } else {
                    count += (b0 - bmin + 1) * (b0 + bmin + a + MAX_PERIM + 1 - 3 * d) + (bmax + b0 + 1) * (bmax - b0) / 2;
                }
            }
        }
    }
    for (long d = 3; d <= MAX_PERIM / 2; ++d) {
        long amax = d - 2;
        long amin = d / 3;
        for (long a = amin; a <= amax; ++a) {
            long bmax = std::min(a, d - 1 - a);
            long bmin = (d - a + 1) / 2;
            count += bmax - bmin + 1;
        }
    }
    std::cout << count / 2 << std::endl;
    return 0;
}
