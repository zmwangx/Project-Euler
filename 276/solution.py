#!/usr/bin/env python3

import math


def count(n):
    # We calculate the number of primitive triangles with perimeter n in
    # f.
    f = [0] * (n + 1)
    for i in range(3, n + 1):
        # https://oeis.org/A005044
        f[i] += round((i if i % 2 == 0 else (i + 3)) ** 2 / 48)
        for j in range(i * 2, n + 1, i):
            f[j] -= f[i]
    return sum(f)


def main():
    print(count(10 ** 7))


if __name__ == "__main__":
    main()
