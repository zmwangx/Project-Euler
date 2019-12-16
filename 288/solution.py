#!/usr/bin/env python3

import itertools


def prng(p):
    s = 290797
    while True:
        yield s % p
        s = s * s % 50515093


def main():
    # p = 3
    # q = 10000
    # m = 20
    p = 61
    q = 10 ** 7
    m = 10
    T = list(itertools.islice(prng(p), q + 1))
    result = (
        sum(T[n] * ((p ** n) - 1) // (p - 1) for n in range(1, m))
        + ((p ** m) - 1) // (p - 1) * sum(T[n] for n in range(m, q + 1))
    ) % (p ** m)
    print(result)


if __name__ == "__main__":
    main()
