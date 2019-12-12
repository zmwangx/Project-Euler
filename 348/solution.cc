#include <cmath>
#include <iostream>

typedef unsigned long long ull;

inline bool is_square(ull n)
{
    ull root = std::sqrt(n);
    return n == root * root;
}

inline size_t count_cube_square_sum(ull n)
{
    size_t count = 0;
    ull cube_root = std::cbrt(n);
    for (ull i = 2; i <= cube_root; ++i) {
        if (is_square(n - i * i * i)) {
            count++;
        }
    }
    return count;
}

inline ull palin(ull n, ull multiplier, bool even)
{
    ull rev = 0;
    ull nn = n;
    while (nn) {
        rev = rev * 10 + nn % 10;
        nn /= 10;
    }
    if (even) {
        return n * multiplier + rev;
    } else {
        return n / 10 * multiplier + rev;
    }
}

int main()
{
    size_t l = 1;
    ull lower = 1, upper = 10;
    ull sum = 0, count = 0;

#define CHECK(n)                             \
    do {                                     \
        if (count_cube_square_sum(n) == 4) { \
            std::cout << n << std::endl;     \
            sum += n;                        \
            count++;                         \
            if (count == 5)                  \
                goto done;                   \
        }                                    \
    } while (0)

    while (1) {
        for (ull n = lower; n < upper; ++n) {
            CHECK(palin(n, upper, false));
        }
        for (ull n = lower; n < upper; ++n) {
            CHECK(palin(n, upper, true));
        }
        l++;
        lower = upper;
        upper *= 10;
    }

done:
    std::cout << sum << std::endl;
    return 0;
}
