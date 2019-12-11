#!/usr/bin/env python3

import math

import primesieve


BOUND = 10 ** 8


def main():
    total = 0
    primes = set(primesieve.primes(BOUND))
    for g in range(2, BOUND // 4 + 1):
        root = int(math.sqrt(g))
        if root * root == g:
            if root % 2 == 0 and root == int(math.sqrt(root)) ** 2:
                print(f"progress: {g}")
            continue
        for c0 in range(2, int(math.sqrt((BOUND - 1) / g)) + 1):
            c = g * c0 * c0 - 1
            if not c in primes:
                continue
            for a0 in range(1, c0):
                if math.gcd(a0, c0) != 1:
                    continue
                a = g * a0 * a0 - 1
                if not a in primes:
                    continue
                b = g * a0 * c0 - 1
                if not b in primes:
                    continue
                total += a + b + c
    print(total)


if __name__ == "__main__":
    main()
