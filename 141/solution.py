#!/usr/bin/env python3

import math


# Search for triplets (a, b, c) where gcd(a, b) = 1 and
# a^3 b c^2 + b^2 c is perfect square.
def search(limit):
    progressives = set()
    for a in range(1, int(math.pow(limit, 1 / 3)) + 1):
        a3 = a * a * a
        for b in range(1, a):
            if math.gcd(a, b) != 1:
                continue
            b2 = b * b
            if a3 * b + b2 >= limit:
                break
            c = 1
            while (n := a3 * b * c * c + b2 * c) < limit:
                sqrt = int(math.sqrt(n))
                if sqrt * sqrt == n:
                    progressives.add(n)
                c += 1
    print(f"sum of progressives under {int(limit)}: {sum(progressives)}")


def main():
    search(1e5)
    search(1e12)


if __name__ == "__main__":
    main()
