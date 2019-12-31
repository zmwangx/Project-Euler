#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#include <primesieve.hpp>
#include <ulong_extras.h>

typedef unsigned long long ull;

const ull TARGET_COUNT = 1'000'000;
const ull MOD = 123'454'321;

int main()
{
    int length = 1;
    while (1) {
        std::cerr << "trying suffix length " << length << "... " << std::flush;
        ull pow2 = std::powl(2, length);
        ull limit = std::powl(3, length + 1) / 2;
        std::vector<ull> primes;
        primesieve::generate_primes(limit / (pow2 / 2), &primes);
        typedef std::pair<ull, size_t> elem_t;
        std::priority_queue<elem_t, std::vector<elem_t>, std::greater<elem_t>> q;
        q.push({ pow2, 0 });
        ull count = 0, last = 0;
        while (!q.empty()) {
            auto [n, i] = q.top();
            q.pop();
            if (n == last) {
                continue;
            }
            last = n;
            count++;
            if (count == TARGET_COUNT) {
                std::cerr << std::endl
                          << std::flush;
                ull exp = TARGET_COUNT - length;
                std::cout << n << " * " << 2 << "^" << exp << std::endl;
                ulong pre = n_preinvert_limb(MOD);
                ull result = n_mulmod2_preinv(n, n_powmod2_ui_preinv(2, exp, MOD, pre), MOD, pre);
                std::cout << result << std::endl;
                return 0;
            }
            // std::cout << n << std::endl;
            if (i == 0) {
                // 2 cannot be replaced, only appended, so we deal with this
                // special case first.
                ull m = n * 2;
                if (m <= limit) {
                    q.push({ m, 0 });
                }
                i++;
            }
            if (n % 2 == 0) {
                for (size_t j = i; j < primes.size(); ++j) {
                    ull p = primes[j];
                    ull m = n / 2 * p;
                    if (m > limit) {
                        break;
                    }
                    q.push({ m, j });
                    m = n * p;
                    if (m > limit) {
                        continue;
                    }
                    q.push({ m, j });
                }
            } else {
                for (size_t j = i; j <= primes.size(); ++j) {
                    ull p = primes[j];
                    ull m = n * p;
                    if (m > limit) {
                        break;
                    }
                    q.push({ m, j });
                }
            }
        }
        std::cerr << "count: " << count << std::endl;
        length++;
    }
    return 0;
}
