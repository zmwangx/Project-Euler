#!/usr/bin/env python3

import sympy


M = 10 ** 6


def main():
    total = 0
    for k in range(1, M + 1):
        if k % 10_000 == 0:
            print(f"progress: {k}")
        for d in sympy.divisors(k)[:-1]:
            total += (2 * M - 2 * k + 3 * d + 1) * d // 2
    print(total)


if __name__ == "__main__":
    main()
