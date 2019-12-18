#!/usr/bin/env python3

import sympy


# n > 1.
def lpf(n):
    return min(sympy.factorint(n))


def g(n):
    assert n >= 9
    nk = 9
    while nk <= n:
        if nk == n:
            return 3 * nk
        last_nk = nk
        nk += (lpf(2 * nk - 1) - 1) // 2
    nk = last_nk
    return 2 * nk + n


def main():
    print(g(10 ** 15))


if __name__ == "__main__":
    main()
