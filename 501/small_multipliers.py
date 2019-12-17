#!/usr/bin/env python3

import primesieve


def main():
    limit = 1000
    primes = primesieve.primes(limit // 2)
    n = len(primes)
    small_multipliers = []
    for i in range(n - 1):
        p = primes[i]
        if p ** 3 <= limit:
            small_multipliers.append(p ** 3)
        for j in range(i + 1, n):
            q = primes[j]
            if p * q <= limit:
                small_multipliers.append(p * q)
    small_multipliers.sort()
    print(len(small_multipliers), small_multipliers)


if __name__ == "__main__":
    main()
