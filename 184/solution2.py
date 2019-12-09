#!/usr/bin/env python3

import collections
import math

from sympy import Poly, binomial
from sympy.abc import x as X


def count_triangles(n):
    n2 = n * n
    ks = collections.defaultdict(int)
    # (0, 1)
    ks[n - 1] = 1
    # (1, 1)
    ks[int(math.sqrt((n2 - 1) / 2))] = 1
    # First quadrant except the pi/4 radius.
    for x in range(2, n):
        x2 = x * x
        for y in range(1, x):
            x2_plus_y2 = y * y + x2
            if x2_plus_y2 >= n2:
                break
            if math.gcd(x, y) != 1:
                continue
            k = int(math.sqrt((n2 - 1) / x2_plus_y2))
            ks[k] += 2

    generating_polynomial = Poly(1, X)
    for k, count in ks.items():
        # (1 + 2 * k * X) ** (2 * count)
        #
        # We calculate up to X^3 ourselves in order to reduce
        # unnecessary computations on the symbolic engine's part.
        kk = 2 * k
        exponent = 2 * count
        generating_polynomial *= (
            1
            + exponent * kk * X
            + binomial(exponent, 2) * (kk ** 2) * (X ** 2)
            + binomial(exponent, 3) * (kk ** 3) * (X ** 3)
        )
    return generating_polynomial.nth(3) // 4


def main():
    print(count_triangles(105))


if __name__ == "__main__":
    main()
