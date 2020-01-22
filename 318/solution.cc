#include <cmath>
#include <iostream>

typedef long long ll;
typedef long double ld;

int main()
{
    ll sum = 0;
    for (int p = 1; p <= 1005; ++p) {
        ld sqrtp = std::sqrtl(p);
        for (int q = p + 1; q <= 2011 - p; ++q) {
            ld delta = std::sqrtl(q) - sqrtp;
            if (delta >= 1) {
                break;
            }
            ll c = std::ceill(2011 / (-2 * std::log10l(delta)));
            // std::cout << p << " " << q << " " << c << std::endl;
            sum += c;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
