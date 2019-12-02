#!/usr/bin/env python3

import math


N = 1e12


def main():
    pool = set()
    for k in range(2, int(math.log2(N)) + 1):
        max_x = int(pow(N, 1 / k))
        if (max_x ** (k + 1) - 1) // (max_x - 1) >= N:
            max_x -= 1
        for x in range(2, max_x + 1):
            pool.add((x ** (k + 1) - 1) // (x - 1))
    print(sum(pool) + 1)


if __name__ == "__main__":
    main()
