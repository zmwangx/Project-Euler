#include <cmath>
#include <iostream>

#include <ulong_extras.h>

typedef long long ll;

const ll MOD = 1E9 + 7;

inline ll mulmod(ll x, ll y)
{
    return x * y % MOD;
}

inline ll invmod(int x)
{
    return n_invmod(x, MOD);
}

ll C(ll n, ll k)
{
    ll result = 1;
    if (k == 1) {
        // C(2n, n)
        for (ll i = 2 * n; i > n; --i) {
            result = mulmod(result, i);
        }
        for (ll i = 1; i <= n; ++i) {
            result = mulmod(result, invmod(i));
        }
    } else {
        for (ll i = 0, ki = 1; i < n;) {
            result = mulmod(result, mulmod(mulmod(ki, ki), k) - 1);
            i++;
            ki = mulmod(ki, k);
            result = mulmod(result, ki + 1);
            result = mulmod(result, invmod(ki - 1));
        }
    }
    return result;
}

int main()
{
    ll result = 0;
    for (int k = 1; k <= 7; ++k) {
        (result += C(std::powl(10, k) + k, k)) %= MOD;
    }
    std::cout << result << std::endl;
    return 0;
}
