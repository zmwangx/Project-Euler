#include <iostream>
#include <vector>

typedef long long ll;

const int N = 1'000'000;
const ll MOD = 100'000'007;

std::vector<ll> factm;
std::vector<ll> factinvm;
std::vector<ll> pow2m;

inline ll invmod(ll x)
{
    ll y = MOD, s = 0, t = 1;
    while (y) {
        ll tmp;
        ll q = x / y;
        tmp = y;
        y = x % y;
        x = tmp;
        tmp = s;
        s = t - q * s;
        t = tmp;
    }
    if (t < 0) {
        t += MOD;
    }
    return t;
}

void precalc()
{
    for (ll i = 0, f = 1; i <= N; ++i, (f *= i) %= MOD) {
        factm.push_back(f);
        factinvm.push_back(invmod(f));
    }
    for (ll i = 0, p = 1; i <= N; ++i, (p *= 2) %= MOD) {
        pow2m.push_back(p);
    }
}

ll calc(int n)
{
    ll result = 0;
    for (int v = 0; v <= 2; ++v) {
        int sum = N - 1 - v;
        for (int k = sum % 2, m = (sum - 3 * k) / 2; k >= 0 && m >= 0; k += 2, m -= 3) {
            ll binom = factm[m + k] * ((factinvm[m] * factinvm[k]) % MOD) % MOD;
            result += factm[m + k + 1] * factm[m + k] % MOD * factm[k + v] % MOD
                * binom % MOD * pow2m[k] % MOD * (1 + (v == 1)) % MOD;
            result %= MOD;
        }
    }
    return result;
}

int main()
{
    precalc();
    std::cout << calc(N) << std::endl;
    return 0;
}
