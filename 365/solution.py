#!/usr/bin/env python3

import functools
import sys

import primesieve


N = 10 ** 18
K = 10 ** 9
PRIME_RANGE = (1000, 5000)

sys.setrecursionlimit(PRIME_RANGE[1] * 2)


def binom_nk_mod(p):
    def factorial_vp(n):
        vp = 0
        while n >= p:
            n //= p
            vp += n
        return vp

    # Calculates n!/p^vp(n!) mod p.
    @functools.lru_cache(maxsize=None)
    def factorial_modp(n):
        if n in (0, 1):
            return 1
        if n == p - 1:
            return -1
        if n < p:
            return n * factorial_modp(n - 1) % p
        # Break n! into n!/(p^k k!) and p^k k! (i.e., p * 2p * ... * kp)
        # where k = floor(n/p). Use Wilson's formula plus recursion.
        q, r = divmod(n, p)
        return (1 if q % 2 == 0 else -1) * factorial_modp(r) * factorial_modp(q) % p

    vp = factorial_vp(N) - factorial_vp(K) - factorial_vp(N - K)
    if vp > 0:
        return 0
    return (
        factorial_modp(N)
        * pow(factorial_modp(K), -1, p)
        * pow(factorial_modp(N - K), -1, p)
        % p
    )


def chinese_remainder(p1r1, p2r2, p3r3):
    p1, r1 = p1r1
    p2, r2 = p2r2
    p3, r3 = p3r3
    s = 0
    if r1 != 0:
        p2p3 = p2 * p3
        s += r1 * p2p3 * pow(p2p3, -1, p1)
    if r2 != 0:
        p3p1 = p3 * p1
        s += r2 * p3p1 * pow(p3p1, -1, p2)
    if r3 != 0:
        p1p2 = p1 * p2
        s += r3 * p1p2 * pow(p1p2, -1, p3)
    return s % (p1 * p2 * p3)


def main():
    primes = primesieve.primes(PRIME_RANGE[0] + 1, PRIME_RANGE[1] - 1)
    n_primes = len(primes)
    p_remainders = [(p, binom_nk_mod(p)) for p in primes]
    total = 0
    for i in range(n_primes):
        print(f"p: {primes[i]} ({i+1}/{n_primes})")
        for j in range(i + 1, n_primes):
            for k in range(j + 1, n_primes):
                total += chinese_remainder(
                    p_remainders[i], p_remainders[j], p_remainders[k]
                )
    print(total)


if __name__ == "__main__":
    main()
