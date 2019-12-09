#!/usr/bin/env python3

import collections
import math


def count_triangles(n):
    k0 = n - 1
    n2 = n * n
    # (1, 1)
    ks = collections.defaultdict(int)
    ks[int(math.sqrt((n2 - 1) / 2))] = 1
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
    N = (k0 + sum(k * count for k, count in ks.items())) * 4
    return (
        N
        * (
            sum(count * (N // 2 - k - k0) * k for k, count in ks.items())
            + 3 * N * k0 // 4
            - 2 * k0 * k0
        )
        - 4 * k0 * k0 * (N // 2 - k0)
        - 4 * sum(count * k * k * (N // 2 - k) for k, count in ks.items())
    ) // 3


def main():
    print(count_triangles(105))


if __name__ == "__main__":
    main()
