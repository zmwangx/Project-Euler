#include <iostream>
#include <unordered_map>

typedef long long ll;

const ll MOD = 998'244'353;

std::unordered_map<ll, ll> Phi_cache;

inline ll S(ll n)
{
    n %= MOD;
    ll np1 = n + 1;
    if (n & 1) {
        np1 >>= 1;
    } else {
        n >>= 1;
    }
    return n * np1 % MOD;
}

ll Phi(ll n)
{
    auto it = Phi_cache.find(n);
    if (it != Phi_cache.end()) {
        return it->second;
    }
    ll result = S(n);
    for (ll i = 2, j; i <= n; i = j) {
        j = n / (n / i) + 1;
        (result -= (j - i) % MOD * Phi(n / i)) %= MOD;
    }
    (result += MOD) %= MOD;
    Phi_cache[n] = result;
    return result;
}

ll G(ll n)
{
    ll result = 0;
    for (ll i = 1, j; i <= n; i = j) {
        j = n / (n / i) + 1;
        (result += (S(j - 1) - S(i - 1)) % MOD * Phi(n / i)) %= MOD;
    }
    return result;
}

int main()
{
    std::cout << G(100'000'000'000) << std::endl;
}
