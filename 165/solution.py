#!/usr/bin/env python3


from fractions import Fraction
from gmpy2 import mpq


N = 5000


def get_true_intersection(segment1, segment2):
    (a1, b1), (c1, d1) = segment1
    (a2, b2), (c2, d2) = segment2
    det = (d1 - b1) * (a2 - c2) - (d2 - b2) * (a1 - c1)
    if det == 0:
        return None
    x = mpq((a1 * d1 - b1 * c1) * (a2 - c2) - (a2 * d2 - b2 * c2) * (a1 - c1), det)
    y = mpq((a2 * d2 - b2 * c2) * (d1 - b1) - (a1 * d1 - b1 * c1) * (d2 - b2), det)
    if a1 != c1:
        if (x - a1) * (x - c1) >= 0:
            return None
    else:
        if (y - b1) * (y - d1) >= 0:
            return None
    if a2 != c2:
        if (x - a2) * (x - c2) >= 0:
            return None
    else:
        if (y - b2) * (y - d2) >= 0:
            return None
    return (x, y)


def prng():
    s = 290797
    for _ in range(N * 4):
        s = s * s % 50515093
        yield s % 500


def main():
    g = prng()
    segments = [((next(g), next(g)), (next(g), next(g))) for _ in range(N)]
    true_intersections = set()
    for i in range(N):
        for j in range(i, N):
            p = get_true_intersection(segments[i], segments[j])
            if p:
                true_intersections.add(p)
    print(len(true_intersections))


if __name__ == "__main__":
    main()
