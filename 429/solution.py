#!/usr/bin/env python3

import primesieve


N = 100_000_000
MODULUS = 1_000_000_009


def main():
    primes = primesieve.primes(N)
    s = 1
    for p in primes:
        vp = 0
        n = N
        while n >= p:
            n //= p
            vp += n
        s *= 1 + pow(p, 2 * vp, MODULUS)
        s %= MODULUS
    print(s)


if __name__ == "__main__":
    main()
