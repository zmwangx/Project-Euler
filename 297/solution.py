#!/usr/bin/env python3

import functools


@functools.lru_cache(maxsize=None)
def fibo(n):
    if n <= 2:
        return 1
    else:
        return fibo(n - 1) + fibo(n - 2)


@functools.lru_cache(maxsize=None)
def S(m):
    if m == 0:
        return 0
    if m == 1:
        return 1
    k = 2
    while fibo(k) <= m:
        k += 1
    k -= 1
    fk = fibo(k)
    return S(fk - 1) + S(m - fk) + (m - fk + 1)


def main():
    print(S(10 ** 17 - 1))


if __name__ == "__main__":
    main()
