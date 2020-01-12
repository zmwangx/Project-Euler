#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

#define N 1803

typedef long double ld;

inline ld sqr(ld x)
{
    return x * x;
}

inline ld max_cover(int a, int b, int c)
{
    ld s = (a + b + c) / 2.0;
    ld r = std::sqrtl((s - a) * (s - b) * (s - c) / s);
    ld sa = std::sqrtl((s - a) * b * c / s);
    ld ra = (sa - r) / (sa + r) * r;
    ld sb = std::sqrtl((s - b) * c * a / s);
    ld rb = (sb - r) / (sb + r) * r;
    ld rap = sqr(ra) / r;
    ld rapp = r * ra / sqr(std::sqrtl(r) + std::sqrtl(ra));
    return sqr(r) + sqr(ra) + sqr(std::max({ rb, rap, rapp }));
}

int main()
{
    int count = 0;
    ld sum = 0;
    for (int a = 1; a <= N / 2; ++a) {
        for (int b = a; b <= N - a; ++b) {
            for (int c = b; c < a + b; ++c) {
                count++;
                sum += max_cover(a, b, c);
            }
        }
    }
    sum *= M_PI;
    std::cout << std::fixed << std::setprecision(5) << sum / count << std::endl;
    return 0;
}
