#!/usr/bin/env python3

import functools
import itertools
import math


@functools.lru_cache(maxsize=None)
def P(n):
    if n == 1:
        return 1
    if n == 2:
        return 2
    if n == 3:
        return 2
    if n % 4 <= 1:
        return 4 * P(n // 4) - 2
    else:
        return 4 * P(n // 4)


@functools.lru_cache(maxsize=None)
def S(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    if n == 2:
        return 3
    k = (n + 1) // 4
    return sum(P(i) for i in range(4 * k, n + 1)) + 16 * S(k - 1) - 4 * k + 9


def main():
    print(S(10 ** 18) % 987654321)


if __name__ == "__main__":
    main()
