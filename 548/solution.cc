#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

#include <fmpzxx.h>

#include <fmpz_factorxx.h>

typedef long long ll;

const ll N = 1E16;

const std::vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43 };

std::map<std::vector<int>, ll> cache;

// We use -1 to indicate result > N.
inline ll g(const std::vector<int>& exponents)
{
    std::vector<int> e(exponents);
    std::sort(e.begin(), e.end(), std::greater<>());
    for (int i = e.size() - 1; i >= 0 && exponents[i] == 0; --i) {
        e.pop_back();
    }
    if (e.empty()) {
        return 1;
    }
    auto it = cache.find(e);
    if (it != cache.end()) {
        return it->second;
    }
    ll result = 0;
    std::vector<std::vector<int>> divisors = { {} };
    for (auto max_exponent : e) {
        int prev_num_divisors = divisors.size();
        for (int i = 0; i < prev_num_divisors; ++i) {
            for (int exponent = 1; exponent <= max_exponent; ++exponent) {
                std::vector<int> new_divisor(divisors[i]);
                new_divisor.push_back(exponent);
                divisors.push_back(new_divisor);
            }
        }
    }
    divisors.pop_back(); // Remove self.
    for (const auto& divisor : divisors) {
        ll tmp = g(divisor);
        if (tmp == -1) {
            result = -1;
            break;
        }
        result += tmp;
        if (result > N) {
            result = -1;
            break;
        }
    }
    cache[e] = result;
    return result;
}

ll dfs(ll product, int p_index, std::vector<int>& exponents)
{
    ll sum = 0;

    ll gg = g(exponents);
    // std::cout << product << " " << gg << std::endl;
    if (gg != -1) {
        flint::fmpz_factorxx f;
        f.set_factor(slong(gg));
        std::vector<int> gg_exponents;
        for (int i = 0; i < f.size(); ++i) {
            gg_exponents.push_back(f.exp(i));
        }
        std::sort(gg_exponents.begin(), gg_exponents.end(), std::greater<>());
        if (exponents == gg_exponents) {
            std::cout << gg << std::endl;
            sum += gg;
        }
    }

    ll new_product;
    if (p_index == 0 || exponents[p_index] < exponents[p_index - 1]) {
        new_product = product * primes[p_index];
        if (new_product <= N) {
            exponents[p_index]++;
            sum += dfs(new_product, p_index, exponents);
            exponents[p_index]--;
        }
    }
    new_product = product * primes[p_index + 1];
    if (new_product <= N) {
        exponents.push_back(1);
        sum += dfs(new_product, p_index + 1, exponents);
        exponents.pop_back();
    }
    return sum;
}

int main()
{
    std::vector<int> exponents = { 1 };
    std::cout << 1 + dfs(2, 0, exponents) << std::endl;
    return 0;
}
