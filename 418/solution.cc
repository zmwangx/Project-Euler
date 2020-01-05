#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <stack>
#include <utility>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

typedef unsigned long long ull;
typedef long double ld;
typedef boost::multiprecision::int256_t int256_t;
typedef std::map<int, int> factorization_t;

const factorization_t factorization = {
    { 2, 39 }, { 3, 19 }, { 5, 9 }, { 7, 6 }, { 11, 3 }, { 13, 3 }, { 17, 2 },
    { 19, 2 }, { 23, 1 }, { 29, 1 }, { 31, 1 }, { 37, 1 }, { 41, 1 }, { 43, 1 }
};

factorization_t operator-(const factorization_t& f1, const factorization_t& f2)
{
    factorization_t f;
    for (auto [p, e1] : f1) {
        f[p] = e1 - f2.at(p);
    }
    return f;
}

ull factor2int(const factorization_t& fact)
{
    ull result = 1;
    for (auto [p, e] : fact) {
        result *= ull(std::powl(p, e));
    }
    return result;
}

int256_t factor2int256(const factorization_t& fact)
{
    int256_t result = 1;
    for (auto [p, e] : fact) {
        result *= boost::multiprecision::pow(int256_t(p), e);
    }
    return result;
}

factorization_t factor(int256_t x)
{
    factorization_t fact;
    for (auto [p, e0] : factorization) {
        int e = 0;
        while (x % p == 0) {
            e++;
            x /= p;
        }
        fact[p] = e;
    }
    return fact;
}

ull largest_divisor_up_to(const factorization_t& fact, ull target)
{
    int nfactors = fact.size();
    std::vector<std::pair<int, int>> fact_list(fact.begin(), fact.end());
    std::stack<std::tuple<int, ull>> s;
    s.push({ 0, 1 });
    ull result = 1, diff = target - result;
    while (!s.empty()) {
        auto [i, prod] = s.top();
        s.pop();
        if (i == nfactors) {
            if (target - prod < diff) {
                result = prod;
                diff = target - result;
            }
            continue;
        }
        auto [p, e] = fact_list[i];
        i++;
        s.push({ i, prod });
        for (int j = 1; j <= e; ++j) {
            prod *= p;
            if (prod > target) {
                break;
            }
            s.push({ i, prod });
        }
    }
    return result;
}

std::vector<ull> divisors_between(const factorization_t& fact, ull lower, ull upper)
{
    int nfactors = fact.size();
    std::vector<std::pair<int, int>> fact_list(fact.begin(), fact.end());
    std::stack<std::tuple<int, ull>> s;
    s.push({ 0, 1 });
    std::vector<ull> results;
    while (!s.empty()) {
        auto [i, prod] = s.top();
        s.pop();
        if (i == nfactors) {
            if (prod >= lower) {
                results.push_back(prod);
            }
            continue;
        }
        auto [p, e] = fact_list[i];
        i++;
        s.push({ i, prod });
        for (int j = 1; j <= e; ++j) {
            prod *= p;
            if (prod > upper) {
                break;
            }
            s.push({ i, prod });
        }
    }
    return results;
}

std::tuple<ull, ull, ull> greedy()
{
    int256_t N = factor2int256(factorization);
    // // For whatever reason, boost::multiprecision::cbrt(N) results in
    // // undefined symbol error, where as sqrt works fine.
    // ull root = boost::multiprecision::cbrt(N);
    ull root = 392387855098338513;
    ull b = largest_divisor_up_to(factorization, root);
    ull a = largest_divisor_up_to(factorization - factor(b), (ull)boost::multiprecision::sqrt(N / b));
    ull c = (ull)(N / b / a);
    std::cout << a << " " << b << " " << c << std::endl;
    std::cout << std::fixed << std::setprecision(8) << (ld)a / root << " " << (ld)b / root << " " << (ld)c / root << std::endl;
    return { a, b, c };
}

int main()
{
    // auto [greedy_a, greedy_b, greedy_c] = greedy();

    // Only consider divisors between cbrt(a^4/c) and cbrt(c^4/a).
    auto divisors = divisors_between(factorization, 392383928416409353, 392391842173088784);
    std::vector<factorization_t> facts;
    for (auto d : divisors) {
        facts.push_back(factor(d));
    }
    ld min_ratio = 2;
    ull sum = 0;
    for (int i = 0; i < divisors.size(); ++i) {
        ull a = divisors[i];
        for (int j = i + 1; j < divisors.size(); ++j) {
            ull c = divisors[j];
            auto fact = factorization - facts[i] - facts[j];
            bool valid = true;
            for (auto [p, e] : fact) {
                if (e < 0) {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                continue;
            }
            ull b = factor2int(fact);
            if (b < a || b > c) {
                continue;
            }
            ld ratio = (ld)c / a;
            if (ratio < min_ratio) {
                min_ratio = ratio;
                sum = a + b + c;
                std::cout << std::fixed << std::setprecision(10) << min_ratio
                          << " " << a << " " << b << " " << c << std::endl;
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
