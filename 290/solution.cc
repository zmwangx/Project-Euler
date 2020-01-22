#include <iostream>
#include <map>
#include <utility>

typedef long long ll;

inline int digit_sum(int x)
{
    int sum = 0;
    while (x) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

std::map<std::tuple<int, int, int>, ll> cache;

// Count number m < 10^length s.t.
//
//   ds(m) = ds(137m + x) + y.
ll search(int length, int x = 0, int y = 0)
{
    auto it = cache.find({ length, x, y });
    if (it != cache.end()) {
        return it->second;
    }
    ll count = 0;
    if (length == 1) {
        for (int d = 0; d <= 9; ++d) {
            if (d == digit_sum(137 * d + x) + y) {
                count++;
            }
        }
        return count;
    }
    for (int d = 0; d <= 9; ++d) {
        int tmp = x + 137 * d;
        count += search(length - 1, tmp / 10, tmp % 10 + y - d);
    }
    cache[{ length, x, y }] = count;
    return count;
}

int main()
{
    std::cout << search(18) << std::endl;
    return 0;
}
