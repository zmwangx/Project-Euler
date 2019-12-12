#!/usr/bin/env python3

import collections
import itertools
import math


def prng():
    s = 290797
    while True:
        s = s * s % 50515093
        yield s % 2000 - 1000


def SL(points):
    points = list(set(points))
    n_points = len(points)
    slope2intercept = collections.defaultdict(set)
    for i in range(n_points):
        a, b = points[i]
        for j in range(i + 1, n_points):
            c, d = points[j]
            g = math.gcd(d - b, a - c)
            alpha = (d - b) // g
            beta = (a - c) // g
            gamma = (b * c - a * d) // g
            if alpha < 0 or alpha == 0 and beta < 0:
                alpha, beta, gamma = -alpha, -beta, -gamma
            slope2intercept[(alpha, beta)].add(gamma)
    n_lines = 0
    n_crossings = 0
    for s in slope2intercept:
        k = len(slope2intercept[s])
        n_lines += k
        if k > 1:
            n_crossings -= k * (k - 1)
    n_crossings += n_lines * (n_lines - 1)
    return n_crossings


def main():
    g = prng()
    points = [(next(g), next(g)) for _ in range(2500)]
    print(SL(points))


if __name__ == "__main__":
    main()
