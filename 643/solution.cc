#include <iostream>
#include <unordered_map>

#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::int128_t slong;

const slong MOD = 1'000'000'007;
std::unordered_map<slong, slong> g_cache;

slong g(slong n)
{
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    auto it = g_cache.find(n);
    if (it != g_cache.end()) {
        return it->second;
    }

    slong result = n * (n + 1) / 2 % MOD;
    slong root = sqrt(n);
    slong maxm = n / (root + 1);
    for (slong m = 2; m <= maxm; ++m) {
        result = (result - g(n / m)) % MOD;
    }
    for (slong d = 1; d <= root; ++d) {
        result = (result - (n / d - (n + d + 1) / (d + 1) + 1) * g(d)) % MOD;
    }
    result = (result + MOD) % MOD;
    g_cache[n] = result;
    return result;
}

slong f(slong n) {
    slong pow2 = 2;
    slong result = 0;
    while (pow2 < n) {
        slong m = n / pow2;
        std::cerr << "progress: calculating g(" << m << ")..." << std::endl;
        result = (result + g(m) - 1) % MOD;
        pow2 *= 2;
    }
    return result;
}

int main()
{
    std::cout << f(100'000'000'000) << std::endl;
    return 0;
}
