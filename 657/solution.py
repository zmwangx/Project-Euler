#!/usr/bin/env python3

import gmpy2
from gmpy2 import mpz


A = 10 ** 7
N = 10 ** 12
P = 1_000_000_007

fmod = []
fmodinv = []


def calculate_factorial_mod():
    r = mpz(1)
    mod = mpz(P)
    fmod.append(r)
    fmodinv.append(r)
    for i in range(1, A + 1):
        r = (r * i) % mod
        fmod.append(r)
        fmodinv.append(gmpy2.invert(r, mod))


def main():
    calculate_factorial_mod()
    count = mpz(0)
    mod = mpz(P)
    np1 = mpz(N) + 1
    for i in range(2, A):
        count += (
            ((-1) ** (A - i - 1))
            * fmod[A]
            * fmodinv[i]
            * fmodinv[A - i]
            * (pow(i, np1, mod) - i)
            * gmpy2.invert(i - 1, mod)
        )
        count %= mod
    count += ((-1) ** A) * A * N + 1
    count %= mod
    print(count)


if __name__ == "__main__":
    main()
