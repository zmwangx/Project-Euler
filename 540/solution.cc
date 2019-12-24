#include <cmath>
#include <iostream>
#include <vector>

typedef long long ll;

// const ll N = 1000000;
const ll N = 3141592653589793LL;

inline ll sqr(ll x)
{
    return x * x;
}

inline ll isqrt(ll x)
{
    return std::sqrtl(x);
}

int main()
{
    ll index_max = isqrt(N);
    if (index_max % 2 == 0) {
        index_max--;
    }
    std::vector<ll> pp(index_max + 1, 0);
    for (ll i = index_max; i >= 1; i -= 2) {
        ll count = 0;
        ll m = N / sqr(i);
        ll a_max = isqrt(m);
        for (ll a = 1; a <= a_max; a += 2) {
            count += isqrt(m - sqr(a)) / 2;
        }
        ll j_max = index_max / i;
        for (ll j = 1; j <= j_max; j += 2) {
            count -= pp[i * j];
        }
        pp[i] = count;
    }
    std::cout << pp[1] << std::endl;
    return 0;
}
