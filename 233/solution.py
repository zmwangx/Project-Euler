#!/usr/bin/env python3

import bisect
import collections

import primesieve


def search_420(n):
    primes = primesieve.primes(n // ((5 ** 3) * (13 ** 2)))

    # Generate multipliers of the form 2^a_0 3^2a_1 7^2a_2 ...
    bound = n // ((5 ** 3) * (13 ** 2) * 17)
    primes_3mod4 = [p for p in primes if p % 4 == 3 and p <= bound]
    units = [2] + primes_3mod4
    n_units = len(units)
    q = collections.deque()
    q.append((1, 0))
    multipliers = [1]
    while q:
        prod, i = q.popleft()
        if i >= n_units:
            continue
        for j in range(i, n_units):
            u = units[j]
            new_prod = prod * u
            if new_prod > bound:
                break
            while new_prod <= bound:
                multipliers.append(new_prod)
                q.append((new_prod, j + 1))
                new_prod *= u
    multipliers.sort()
    multiplier_sums = [1]
    for i in range(1, len(multipliers)):
        multiplier_sums.append(multiplier_sums[i - 1] + multipliers[i])

    primes_1mod4 = [p for p in primes if p % 4 == 1]
    total = 0

    def search_with_exponents(exponents):
        nonlocal total
        prime_factor_count = len(exponents)
        q = collections.deque()
        q.append((1, 0))
        while q:
            prod, step = q.popleft()
            if step == prime_factor_count:
                max_multiplier = n // prod
                index = bisect.bisect_right(multipliers, max_multiplier)
                assert index
                total += prod * multiplier_sums[index - 1]
                continue
            exponent = exponents[step]
            step += 1
            remaining_min = 5 ** sum(exponents[step:])
            for p in primes_1mod4:
                if prod % p == 0:
                    continue
                new_prod = prod * (p ** exponent)
                if new_prod * remaining_min > n:
                    break
                q.append((new_prod, step))

    search_with_exponents((3, 2, 1))  # 7 * 5 * 3
    search_with_exponents((7, 3))  # 15 * 7
    search_with_exponents((10, 2))  # 21 * 5
    search_with_exponents((17, 1))  # 35 * 3
    search_with_exponents((52,))  # 105

    return total


def main():
    print(search_420(100_000_000_000))


if __name__ == "__main__":
    main()
