#include <cassert>
#include <iostream>
#include <map>
#include <numeric>
#include <utility>

#include <boost/multiprecision/cpp_int.hpp>

typedef long long ll;

const ll N = 3'138'428'376'721; // 11^12
const ll MOD = 1'000'000'000;

// 10^i % 23.
const int remainders[] = { 1, 10, 8, 11, 18, 19, 6, 14, 2, 20, 16, 22, 13, 15, 12, 5, 4, 17, 9, 21, 3, 7 };
const int factorials[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };
ll c[23][24][23];

ll binom_mod(ll n, int k)
{
    // Calculate n(n-1)...(n-k+1) / k! % MOD by multiplying one term at a time,
    // with what be divided taken out.
    ll f = factorials[k];
    boost::multiprecision::int128_t res = 1;
    for (ll m = n; m >= n - k + 1; --m) {
        if (f > 1) {
            ll g = std::gcd(m, f);
            f /= g;
            (res *= m / g) %= MOD;
        } else {
            (res *= m) %= MOD;
        }
    }
    return (ll)res;
}

std::map<std::pair<ll, int>, ll> cache;

ll count_single_remainder_placements(ll places, int digit_sum)
{
    if (places == 0) {
        return digit_sum == 0 ? 1 : 0;
    }
    if (places == 1) {
        return digit_sum <= 9 ? 1 : 0;
    }
    auto it = cache.find({ places, digit_sum });
    if (it != cache.end()) {
        return it->second;
    }
    ll count;
    if (digit_sum <= 9) {
        count = binom_mod(digit_sum + places - 1, digit_sum);
    } else {
        count = 0;
        ll half = places / 2;
        for (int half_sum = 0; half_sum <= digit_sum; ++half_sum) {
            (count += count_single_remainder_placements(half, half_sum)
                    * count_single_remainder_placements(places - half, digit_sum - half_sum))
                %= MOD;
        }
    }
    cache[{ places, digit_sum }] = count;
    return count;
}

int main()
{
    c[0][0][0] = 1;
    for (int m = 1; m <= 22; ++m) {
        int rlast = remainders[m - 1] - 23;
        ll places = N / 22 + ((m - 1) < N % 22);
        c[m][0][0] = 1;
        for (int d = 1; d <= 23; ++d) {
            for (int r = 0; r < 23; ++r) {
                ll count = 0;
                for (int last_count = 0; last_count <= d; ++last_count) {
                    (count += c[m - 1][d - last_count][(r - last_count * rlast) % 23]
                            * count_single_remainder_placements(places, last_count))
                        %= MOD;
                }
                c[m][d][r] = count;
            }
        }
    }
    std::cout << c[22][23][0] << std::endl;
    return 0;
}
