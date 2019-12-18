#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>

typedef long long ll;

const int N = 12;
const int TARGET_COUNT = 10;

int main()
{
    std::array<ll, N> base_N;
    // Note that contrary to convention, base_N[i] stores the most significant
    // digit here to make reverse construction easier.
    base_N[0] = 1;
    base_N[1] = 0;
    for (int i = 2; i < N; ++i) {
        base_N[i] = i;
    }
    int count = 0;
    long long sum = 0;
    do {
        ll n = 0;
        for (auto d : base_N) {
            n = n * N + d;
        }
        bool failed = false;
        for (int base = N - 1; base >= 3; base--) {
            int mask = (1 << base) - 1;
            ll m = n;
            while (m > 0) {
                mask &= ~(1 << (m % base));
                m /= base;
            }
            if (mask) {
                failed = true;
                break;
            }
        }
        if (!failed) {
            count++;
            sum += n;
            std::cout << n << std::endl;
            if (count == TARGET_COUNT) {
                break;
            }
        }
    } while (std::next_permutation(base_N.begin(), base_N.end()));
    std::cout << sum << std::endl;
}
