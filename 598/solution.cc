#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <stack>
#include <utility>
#include <vector>

typedef long long ll;

std::vector<std::pair<ll, ll>> generate_ratios(const std::vector<int>& sums)
{
    std::vector<std::pair<ll, ll>> results;
    std::stack<std::tuple<int, ll, ll>> s;
    s.push({ 0, 1, 1 });
    int length = sums.size();
    while (!s.empty()) {
        auto [index, prod1, prod2] = s.top();
        s.pop();
        if (index == length) {
            ll g = std::gcd(prod1, prod2);
            results.push_back({ prod1 / g, prod2 / g });
            continue;
        }
        int sum = sums[index];
        index++;
        for (int i = 1; i <= sum - 1; ++i) {
            s.push({ index, prod1 * i, prod2 * (sum - i) });
        }
    }
    return results;
}

int main()
{
    // Prime exponents of 100!:
    // 97, 48, 24, 16, 9, 7, 5, 5, 4, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1

    std::vector<std::pair<ll, ll>> s1;
    s1 = generate_ratios({ 99, 50, 26, 18, 11 });
    std::map<std::pair<ll, ll>, ll> s1m;
    for (const auto& [p, q] : s1) {
        s1m[{ p, q }]++;
    }
    std::vector<std::pair<ll, ll>>().swap(s1);

    std::vector<std::pair<ll, ll>> s2;
    s2 = generate_ratios({ 9, 7, 7, 6, 5, 5, 4, 4, 4, 4 });
    std::array<int, 11> c = { 1, 10, 45, 120, 210, 252, 210, 120, 45, 10, 1 }; // C(10, i)
    std::map<std::pair<ll, ll>, ll> s2m;
    for (const auto& [p, q] : s2) {
        for (int i = 0, pow1 = 1, pow2 = 1024; i <= 10; ++i, pow1 *= 2, pow2 /= 2) {
            ll pp = p * pow1;
            ll qq = q * pow2;
            ll g = std::gcd(pp, qq);
            s2m[{ pp / g, qq / g }] += c[i];
        }
    }
    std::vector<std::pair<ll, ll>>().swap(s2);

    ll total = 0;
    for (const auto& [r2, c2] : s2m) {
        auto it = s1m.find(r2);
        if (it != s1m.end()) {
            auto c1 = it->second;
            total += c1 * c2;
        }
    }
    std::cout << total / 2 << std::endl;
    return 0;
}
