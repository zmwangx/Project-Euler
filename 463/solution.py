#!/usr/bin/env python3

import functools


@functools.lru_cache(maxsize=None)
def f(n):
    if n == 1:
        return 1
    if n == 3:
        return 3
    if n % 2 == 0:
        return f(n // 2)
    if n % 4 == 1:
        return 2 * f((n + 1) // 2) - f((n - 1) // 4)
    else:
        return 3 * f((n - 1) // 2) - 2 * f((n - 3) // 4)


@functools.lru_cache(maxsize=None)
def s(n):
    if n <= 2:
        return sum(f(i) for i in range(1, n + 1))
    k = (n + 1) // 4
    return 6 * s(2 * k - 1) - 8 * s(k - 1) - 1 + sum(f(i) for i in range(4 * k, n + 1))


def main():
    print(s(3 ** 37) % (10 ** 9))


if __name__ == "__main__":
    main()
