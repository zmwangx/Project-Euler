#!/usr/bin/env python3

import primesieve

# Label the horizontal strokes 0, 1, 2 top to bottom, label the vertical
# strokes 3,4,5,6 top to bottom, left to right (that is to say, 3,4 for
# left edge, 5,6 for right edge).
STROKES = {
    0: (0, 2, 3, 4, 5, 6),
    1: (5, 6),
    2: (0, 1, 2, 4, 5),
    3: (0, 1, 2, 5, 6),
    4: (1, 3, 5, 6),
    5: (0, 1, 2, 3, 6),
    6: (0, 1, 2, 3, 4, 6),
    7: (0, 3, 5, 6),
    8: (0, 1, 2, 3, 4, 5, 6),
    9: (0, 1, 2, 3, 5, 6),
}

SAVINGS = [
    [2 * len(set(STROKES[i]) & set(STROKES[j])) for j in range(10)] for i in range(10)
]

cache = {}


def calculate_root_and_saving(n):
    if n < 10:
        return n, 0
    nd = []
    while n >= 10:
        nd.append(n % 10)
        n //= 10
    nd.append(n)
    root = sum(nd)
    r = root
    rd = []
    while r >= 10:
        rd.append(r % 10)
        r //= 10
    rd.append(r)
    saving = 0
    for d1, d2 in zip(nd, rd):
        saving += SAVINGS[d1][d2]
    return root, saving


def cache_two_digits():
    for n in range(10, 100):
        root, saving = calculate_root_and_saving(n)
        if root < 10:
            cache[n] = saving
        else:
            cache[n] = saving + cache[root]


def main():
    cache_two_digits()
    total_saving = 0
    for p in primesieve.primes(1E7, 2E7):
        root, saving = calculate_root_and_saving(p)
        total_saving += saving + (cache[root] if root >= 10 else 0)
        # print(p, saving + (cache[root] if root >= 10 else 0))
    print(total_saving)


if __name__ == "__main__":
    main()
