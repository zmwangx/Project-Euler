#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

typedef long long ll;

const int limit = 1'000'000;

inline int sqr(int x)
{
    return x * x;
}

int main()
{
    int root = std::sqrt(limit);
    std::vector<std::vector<int>> sides(limit + 1);
    for (int a = 2; a <= root; ++a) {
        for (int b = a % 2 + 1; b < a; b += 2) {
            if (std::gcd(a, b) > 1) {
                continue;
            }
            int r = sqr(a) + sqr(b);
            if (r >= limit) {
                break;
            }
            int s = sqr(a) - sqr(b);
            int t = 2 * a * b;
            for (int rr = r, ss = s, tt = t; rr < limit; rr += r, ss += s, tt += t) {
                sides[ss].push_back(tt);
                sides[tt].push_back(ss);
            }
        }
    }
    int count = 0;
    for (int w = 1; w < limit; ++w) {
        auto& s = sides[w];
        if (s.size() <= 1) {
            continue;
        }
        for (ll u : s) {
            for (ll v : s) {
                if (u < v && u * v % (u + v) == 0) {
                    // ll x = std::sqrt(sqr(u) + sqr(w));
                    // ll y = std::sqrt(sqr(v) + sqr(w));
                    // ll h = u * v / (u + v);
                    // std::cout << x << " " << y << " " << h << " " << w << std::endl;
                    count++;
                }
            }
        }
    }
    std::cout << count << std::endl;
    return 0;
}
