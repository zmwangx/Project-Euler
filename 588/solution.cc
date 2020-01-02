#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

typedef unsigned long long ull;

typedef std::map<ull, int> poly_t;

inline poly_t unit(unsigned order)
{
    return poly_t{ { 0, 1 }, { 1ULL << order, 1 }, { 2ULL << order, 1 }, { 3ULL << order, 1 }, { 4ULL << order, 1 } };
}

poly_t product(const poly_t& p1, const poly_t& p2)
{
    poly_t p;
    for (const auto& [e1, v1] : p1) {
        for (const auto& [e2, v2] : p2) {
            // In general: p[e1 + e2] += v1 * v2;
            p[e1 + e2]++;
        }
    }
    for (auto it = p.begin(); it != p.end();) {
        if (it->second % 2 == 0) {
            it = p.erase(it);
        } else {
            it->second = 1;
            ++it;
        }
    }
    return p;
}

poly_t units_product(const std::vector<unsigned>& orders)
{
    poly_t p = { { 0, 1 } };
    for (auto order : orders) {
        p = product(p, unit(order));
    }
    return p;
}

ull count_odd_terms_in_product(const poly_t& p1, const poly_t& p2)
{
    ull m = p1.rbegin()->first, n = p2.rbegin()->first;
    if (m < n) {
        return count_odd_terms_in_product(p2, p1);
    }
    poly_t p;
    ull result = 0;
    ull lower = 0, upper = 0;
    while (lower <= m) {
        if (upper / n % 10000 == 0) {
            std::cerr << "progress: " << upper / n << "/" << m / n << std::endl;
        }
        for (const auto& [e1, v1] : p1) {
            if (e1 < lower) {
                continue;
            }
            if (e1 > upper) {
                break;
            }
            for (const auto& [e2, v2] : p2) {
                p[e1 + e2]++;
            }
        }

        for (auto it = p.begin(); it != p.end();) {
            auto& [e, v] = *it;
            if (e > upper) {
                break;
            }
            if (v % 2 == 1) {
                result++;
            }
            it = p.erase(it);
        }

        if (lower == 0) {
            lower = 1;
        } else {
            lower += n;
        }
        upper += n;
    }
    for (const auto& [e, v] : p) {
        if (v % 2 == 1) {
            result++;
        }
    }
    return result;
}

int main()
{
    ull total = 0;
    for (ull i = 1, n = 5; i <= 18; ++i, n *= 5) {
        std::cerr << "=== calculating Q(10^" << i << ") ===" << std::endl;
        std::vector<unsigned> orders;
        ull m = n;
        unsigned order = 0;
        while (m) {
            if (m & 1) {
                orders.push_back(order);
                std::cout << order << " ";
            }
            m >>= 1;
            order++;
        }
        std::cout << std::endl;
        std::vector<unsigned> orders1(orders.begin(), orders.begin() + orders.size() / 2);
        std::vector<unsigned> orders2(orders.begin() + orders.size() / 2, orders.end());
        poly_t p1 = units_product(orders1);
        poly_t p2 = units_product(orders2);
        std::cerr << "polynomial sizes: " << p1.size() << " * " << p2.size() << " = " << p1.size() * p2.size() << std::endl;
        ull count = count_odd_terms_in_product(p1, p2);
        std::cerr << "Q(10^" << i << ") = " << count << std::endl;
        total += count;
        std::cerr << "subtotal: " << total << std::endl;
    }
    std::cerr << "=== total ===" << std::endl;
    std::cout << total << std::endl;
    return 0;
}
