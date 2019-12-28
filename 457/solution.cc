#include <iostream>
#include <vector>

#include <primesieve.hpp>
#include <ulong_extras.h>

const long LIMIT = 10'000'000;

int main()
{
    std::vector<long> primes;
    primesieve::generate_primes(LIMIT, &primes);
    ulong sum = 0;
    for (auto p : primes) {
        long r = p % 13;
        if (r != 1 && r != 3 && r != 4 && r != 9 && r != 10 && r != 12) {
            continue;
        }
        ulong* roots;
        if (n_sqrtmod_primepow(&roots, 13, p, 2)) {
            // We know there are exactly two roots.
            ulong x1 = *roots, x2 = *(roots + 1);
            flint_free(roots);
            ulong p2 = p * p;
            ulong pre = n_preinvert_limb(p2);
            ulong inv2 = (p2 + 1) / 2;
            ulong r1 = n_mulmod2_preinv(3 + x1, inv2, p2, pre);
            ulong r2 = n_mulmod2_preinv(3 + x2, inv2, p2, pre);
            if (r1 < r2) {
                sum += r1;
            } else {
                sum += r2;
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
