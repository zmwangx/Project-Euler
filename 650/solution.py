#!/usr/bin/env python3

import collections
import functools

import primesieve


N = 20000
MODULUS = 1000000007
primes = primesieve.primes(N)


class Factors(collections.defaultdict):
    def __init__(self, *args):
        super().__init__(int)
        if args:
            self.update(*args)

    def __add__(self, other):
        this = Factors(self)
        for p in other:
            this[p] += other[p]
        return this

    def __iadd__(self, other):
        for p in other:
            self[p] += other[p]

    def __sub__(self, other):
        this = Factors(self)
        for p in other:
            this[p] -= other[p]
        return this

    def __isub__(self, other):
        for p in other:
            self[p] -= other[p]

    def __mul__(self, other):
        this = Factors(self)
        for p in this:
            this[p] *= other
        return this

    def __imul__(self, other):
        for p in this:
            this[p] *= other


@functools.lru_cache
def factorize(n: int) -> Factors:
    if n == 1:
        return Factors()
    for p in primes:
        if n % p == 0:
            return factorize(n // p) + {p: 1}


@functools.lru_cache
def factorize_factorial(n: int) -> Factors:
    if n == 1:
        return Factors()
    return factorize_factorial(n - 1) + factorize(n)


@functools.lru_cache
def factorize_Bn(n: int) -> Factors:
    if n == 1:
        return Factors()
    return factorize_Bn(n - 1) + factorize(n) * n - factorize_factorial(n)


def sigma(f: Factors, mod) -> int:
    s = 1
    for p in f:
        s *= (pow(p, f[p] + 1, mod) - 1) * pow(
            p - 1, -1, mod
        )  # negative pow is a py38 feature
        s %= mod
    return s


def calculate_S(n, mod):
    s = 0
    for i in range(1, n + 1):
        if i % 1000 == 0:
            print(f"progress: {i}")
        s += sigma(factorize_Bn(i), mod)
        s %= mod
    return s


def main():
    print(calculate_S(N, MODULUS))


if __name__ == "__main__":
    main()
