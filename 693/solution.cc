#include <algorithm>
#include <iostream>
#include <vector>

typedef long long ll;
const ll N = 3'000'000;

int main()
{
    size_t maxlen = 0;
    ll maxlen_x = 0;
    for (ll x = 2; x <= N; ++x) {
        if (x % 50'000 == 0) {
            std::cerr << "progress: " << x << std::endl;
        }
        ll z = x;
        ll r = 2;
        while ((r = r * r % z) > 1) {
            z++;
        }
        if (z - x + 2 > maxlen) {
            maxlen = z - x + 2;
            maxlen_x = x;
            std::cout << x << " " << 2 << ": " << maxlen << std::endl;
        }
    }
    for (ll x = maxlen_x - 1; x > 0; --x) {
        bool found = false;
        for (ll y = 2; y <= x / 2; ++y) {
            ll z = x;
            ll r = y;
            while ((r = r * r % z) > 1) {
                z++;
            }
            if (z - x + 2 > maxlen) {
                found = true;
                maxlen = z - x + 2;
                std::cout << x << " " << y << ": " << maxlen << std::endl;
                break;
            }
        }
        if (!found) {
            break;
        }
    }
    std::cout << maxlen << std::endl;
    return 0;
}
