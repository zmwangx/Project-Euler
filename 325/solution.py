#!/usr/bin/env python3

import functools
import math


phi = (1 + math.sqrt(5)) / 2


@functools.lru_cache(maxsize=None)
def U(n):
    if n == 0:
        return 0
    ndphi = math.floor(n / phi)
    return n * ndphi * (ndphi + 1) // 2 - (n - 1) * n * (n + 1) // 6 + V(n) - V(ndphi)


@functools.lru_cache(maxsize=None)
def V(n):
    if n == 0:
        return 0
    ndphi = math.floor(n / phi)
    return ndphi * n * (n + 1) // 2 + n * (n + 1) * (2 * n + 1) // 6 - U(ndphi)


def S(n):
    return n * (n + 1) * (4 * n - 1) // 6 - U(n)


def main():
    print(S(10 ** 16) % (7 ** 10))


if __name__ == "__main__":
    main()
