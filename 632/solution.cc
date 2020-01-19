#include <iostream>
#include <vector>

typedef long long ll;

const ll SQRT = 100'000'000;
const ll N = SQRT * SQRT;
const ll MAX_K = 8;
const ll MOD = 1'000'000'007;

ll factorial[MAX_K + 1] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 };
ll binom[MAX_K + 1][MAX_K + 1];
int pp[SQRT + 1];
int factor_count[SQRT + 1];
std::vector<int> bins[MAX_K + 1];

inline ll sqr(ll x)
{
    return x * x;
}

void precalc_binom()
{
    for (int n = 0; n <= MAX_K; ++n) {
        for (int k = 0; k <= n; ++k) {
            binom[n][k] = factorial[n] / factorial[k] / factorial[n - k];
        }
    }
}

void precalc_factor_count()
{
    for (int i = 2; i <= SQRT; ++i) {
        if (pp[i]) {
            int p = pp[i];
            int j = i / p;
            if (j % p == 0 || factor_count[j] == 0) {
                // We only care about products of distinct prime factors.
                continue;
            }
            factor_count[i] = factor_count[j] + 1;
            bins[factor_count[i]].push_back(i);
        } else {
            factor_count[i] = 1;
            bins[1].push_back(i);
            for (int j = i + i; j <= SQRT; j += i) {
                pp[j] = i;
            }
        }
    }
}

int main()
{
    precalc_binom();
    precalc_factor_count();
    int max_k = 1;
    while (max_k + 1 <= MAX_K && bins[max_k + 1].size() > 0) {
        max_k++;
    }
    std::vector<ll> A(max_k + 1, 0);
    std::vector<ll> C(max_k + 1, 0);
    for (int k = 1; k <= max_k; ++k) {
        ll a = 0;
        for (auto i : bins[k]) {
            a += N / sqr(i);
        }
        A[k] = a;
    }
    C[0] = N;
    for (int k = max_k; k >= 1; --k) {
        ll c = A[k];
        for (int l = k + 1; l <= max_k; ++l) {
            c -= binom[l][k] * C[l];
        }
        C[k] = c;
        C[0] -= c;
    }
    ll product = 1;
    for (auto c : C) {
        std::cout << c << std::endl;
        (product *= (c % MOD)) %= MOD;
    }
    std::cout << product << std::endl;
    return 0;
}
