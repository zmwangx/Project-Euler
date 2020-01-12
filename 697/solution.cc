#include <cmath>
#include <iomanip>
#include <iostream>

#define N 10'000'000
#define TARGET 0.25

typedef long double ld;

ld cdf(int n, ld x)
{
    ld mult1 = std::expl(n - x) * std::powl(x / n, n) / std::sqrtl(2 * M_PI * n);
    ld term = 1;
    ld mult2 = 1;
    for (int i = n; i > 1; --i) {
        term *= i / x;
        mult2 += term;
    }
    return mult1 * mult2;
}

int main()
{
    ld lo = N, hi = N * 1.1, mid;
    while (hi - lo >= 0.001) {
        // p(lo) > TARGET > p(hi)
        mid = (lo + hi) / 2;
        ld p = cdf(N - 1, mid);
        std::cout << std::fixed
                  << std::setprecision(3) << mid << "\t"
                  << std::setprecision(6) << p << std::endl;
        if (p > TARGET) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    std::cout << std::fixed << std::setprecision(2) << mid / std::logl(10) << std::endl;
}
