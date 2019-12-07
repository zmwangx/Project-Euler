#!/usr/bin/env python3

from fractions import Fraction


def count_triangles(n):
    def in_bounds(*coords):
        return all(c[0] >= 0 and c[1] >= 0 and c[2] >= 0 for c in coords)

    count = 0
    # x = i, y = j, z = k
    for i in range(n):
        for j in range(n):
            for k in range(n):
                p1 = (n - j - k, j, k)
                p2 = (i, n - k - i, k)
                p3 = (i, j, n - i - j)
                # assert p2[0] == i and p3[0] == i
                # assert p3[1] == j and p1[1] == j
                # assert p1[2] == k and p2[2] == k
                if p1 != p2 and in_bounds(p1, p2, p3):
                    count += 1

    # x = i, y = j, x - y = k
    for i in range(n):
        for j in range(n):
            for k in range(-n + 1, n):
                p1 = (j + k, j, n - 2 * j - k)
                p2 = (i, i - k, n - 2 * i + k)
                p3 = (i, j, n - i - j)
                # assert p2[0] == i and p3[0] == i
                # assert p3[1] == j and p1[1] == j
                # assert p1[0] - p1[1] == k and p2[0] - p2[1] == k
                if p1 != p2 and in_bounds(p1, p2, p3):
                    count += 3

    # x = i, y = j, y - z = k
    for i in range(n):
        for j in range(-n + 1, n):
            for k in range(-n + 1, n):
                p1 = (n - 2 * j + k, j, j - k)
                p2 = (i, Fraction(n - i + k, 2), Fraction(n - i - k, 2))
                p3 = (i, j, n - i - j)
                # assert p2[0] == i and p3[0] == i
                # assert p3[1] == j and p1[1] == j
                # assert p1[1] - p1[2] == k and p2[1] - p2[2] == k
                if p1 != p2 and in_bounds(p1, p2, p3):
                    count += 6

    # x = i, z - x = j, x - y = k
    for i in range(n):
        for j in range(-n + 1, n):
            for k in range(-n + 1, n):
                p1 = (
                    Fraction(n - j + k, 3),
                    Fraction(n - j - 2 * k, 3),
                    Fraction(n + 2 * j + k, 3),
                )
                p2 = (i, i - k, n - 2 * i + k)
                p3 = (i, n - 2 * i - j, i + j)
                # assert p2[0] == i and p3[0] == i
                # assert p3[2] - p3[0] == j and p1[2] - p1[0] == j
                # assert p1[0] - p1[1] == k and p2[0] - p2[1] == k
                if p1 != p2 and in_bounds(p1, p2, p3):
                    count += 3

    # x = i, y - z = j, z - x = k
    for i in range(n):
        for j in range(-n + 1, n):
            for k in range(-n + 1, n):
                p1 = (
                    Fraction(n - j - 2 * k, 3),
                    Fraction(n + 2 * j + k, 3),
                    Fraction(n - j + k, 3),
                )
                p2 = (i, n - 2 * i - k, i + k)
                p3 = (i, Fraction(n - i + j, 2), Fraction(n - i - j, 2))
                # assert p2[0] == i and p3[0] == i
                # assert p3[1] - p3[2] == j and p1[1] - p1[2] == j
                # assert p1[2] - p1[0] == k and p2[2] - p2[0] == k
                if p1 != p2 and in_bounds(p1, p2, p3):
                    count += 6

    # x - y = i, y - z = j, z - x = k
    for i in range(-n + 1, n):
        for j in range(-n + 1, n):
            for k in range(-n + 1, n):
                p1 = (
                    Fraction(n - j - 2 * k, 3),
                    Fraction(n + 2 * j + k, 3),
                    Fraction(n - j + k, 3),
                )
                p2 = (
                    Fraction(n - k + i, 3),
                    Fraction(n - k - 2 * i, 3),
                    Fraction(n + 2 * k + i, 3),
                )
                p3 = (
                    Fraction(n + 2 * i + j, 3),
                    Fraction(n - i + j, 3),
                    Fraction(n - i - 2 * j, 3),
                )
                # assert p2[0] - p2[1] == i and p3[0] - p3[1] == i
                # assert p3[1] - p3[2] == j and p1[1] - p1[2] == j
                # assert p1[2] - p1[0] == k and p2[2] - p2[0] == k
                if p1 != p2 and in_bounds(p1, p2, p3):
                    count += 1

    return count


def main():
    print(count_triangles(36))


if __name__ == "__main__":
    main()
