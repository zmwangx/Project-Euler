#!/usr/bin/env python3

import math


def Fk(n, k):
    if n == 3:
        m = math.floor((math.sqrt(n) - 1) / 2)
        return m * (3 * m * m + 9 * m + 8) // 2

    m = math.floor(math.sqrt(n / max(4 * (k - 2) ** 2, (k - 2) * ((k - 4) ** 2) / 2)))
    while (2 * (k - 2) * m + 1) ** 2 > n:
        m -= 1
    while ((k - 4) ** 2) * m * ((k - 2) * m + 1) // 2 > n:
        m -= 1
    k2 = k * k
    k3 = k2 * k
    m2 = m * m
    m3 = m2 * m
    return (2 * k2 * (k - 2) * m3 + 3 * k2 * (k - 1) * m2 + (k3 + k2 + 12) * m) // 12


def sum_Fk(n):
    k_bound = math.floor(min((math.sqrt(n) + 3) / 2, pow(2 * n, 1 / 3) + 4)) + 1
    return sum(Fk(n, k) for k in range(3, k_bound, 2))


def main():
    print(sum_Fk(10 ** 12))


if __name__ == "__main__":
    main()
