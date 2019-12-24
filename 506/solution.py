#!/usr/bin/env python3

import itertools


N = 10 ** 14
MOD = 123454321


def main():
    generator = itertools.cycle((1, 2, 3, 4, 3, 2))
    s = [0]
    total = 0
    for i in range(1, 31):
        num = 0
        dsum = 0
        while dsum < i:
            d = next(generator)
            num = 10 * num + d
            dsum += d
        total += num
        s.append(s[-1] + num % 1_000_000)
    S0 = s[15]
    S1 = s[30] - S0
    q, r = divmod(N, 15)
    a = (10 ** 6) - 1
    ainv = pow(a, -1, MOD)
    b = (pow(10, 6 * q, MOD) - 1) * ainv % MOD
    print((b * s[r + 15] + (b - q) * ainv * S1 + pow(10, 6 * q, MOD) * s[r]) % MOD)


if __name__ == "__main__":
    main()
