#!/usr/bin/env python3

import math

import primesieve


N = 10 ** 12


def main():
    limit = int(math.sqrt(N))
    primes = primesieve.primes(limit)
    is_composite = [True] * (limit + 1)
    is_composite[1] = False
    for p in primes:
        is_composite[p] = False
    is_power = [False] * (limit + 1)
    total = 0
    for a in range(2, limit + 1):
        if is_power[a]:
            continue
        a_is_composite = is_composite[a]
        b = 2
        n = a * a
        while n <= N:
            if a_is_composite or is_composite[b]:
                total += n
            if n <= limit:
                is_power[n] = True
            b += 1
            n *= a
    print(total - 16)


if __name__ == "__main__":
    main()
