#include <iomanip>
#include <iostream>

typedef long long ll;
typedef long double ld;

const ll N = 10'000'000'000LL;

inline ld sqr(ld x)
{
    return x * x;
}

int main()
{
    ld bn = 0;
    ll size, height;
    for (size = height = 1; size <= N; size += 1LL << height, ++height) {
        bn += height << (height - 1);
    }
    size >>= 1;
    bn += height * (N - size);
    bn /= N;

    ld rn = 1, rnm1 = 1, sn = 0, snm1 = 0;
    for (ll n = 2; n <= N; ++n) {
        ld n2 = sqr(n);
        ld nm12 = sqr(n - 1);
        rn = (1 + (2 * n - 2) / n2) * rnm1 - (2 / nm12 - 2 / n2) * snm1;
        sn = snm1 + (n - 1) * rnm1;
        rnm1 = rn;
        snm1 = sn;
    }

    std::cout << std::fixed << std::setprecision(11) << bn << " " << rn << " " << rn - bn << std::endl;
}
