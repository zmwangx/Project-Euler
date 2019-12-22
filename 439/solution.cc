#include <iostream>
#include <unordered_map>

#include <boost/multiprecision/cpp_int.hpp>

// #define PROFILE

typedef boost::multiprecision::int128_t slong;

const slong N = 100'000'000'000; //100'000'000'000;
const slong MOD = 1'000'000'000;

std::unordered_map<slong, slong> s_cache;
#ifdef PROFILE
slong s_hit = 0;
slong s_miss = 0;
#endif

slong t(slong n)
{
    slong sum = 0;
    for (slong i = n, ii; i > 0; i = ii) {
        slong k = n / i;
        ii = n / (k + 1);
        sum = (sum + (i - ii) * k * (k + 1) / 2) % MOD;
    }
    return sum;
}

slong s(slong n)
{
    auto it = s_cache.find(n);
    if (it != s_cache.end()) {
#ifdef PROFILE
        s_hit++;
#endif
        return it->second;
    }
#ifdef PROFILE
    s_miss++;
#endif
    slong tn = t(n);
    slong sum = tn * tn % MOD;
    for (slong i = n, ii; i > 1; i = ii) {
        slong k = n / i;
        ii = n / (k + 1);
        sum = (sum - s(k) * (i * (i + 1) - ii * (ii + 1)) / 2) % MOD;
    }
    (sum += MOD) %= MOD;
    s_cache[n] = sum;
    return sum;
}

int main()
{
    std::cout << s(N) << std::endl;
#ifdef PROFILE
    std::cerr << "s: hit - " << s_hit << "\tmiss - " << s_miss << std::endl;
#endif
    return 0;
}
