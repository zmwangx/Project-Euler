#!/usr/bin/env python3

from fractions import Fraction


N = 1000
N2 = N * N
corners = (1, N, N2 - N + 1, N2)


def weight1(n):
    if n in corners:
        return 3
    row, col = divmod(n - 1, N)
    if row in (0, N - 1) or col in (0, N - 1):
        return 4
    return 5


def main():
    total1 = 3 * 4 + 4 * 4 * (N - 2) + 5 * (N - 2) * (N - 2)
    square_sum1 = sum(weight1(i * i) for i in range(1, N + 1))
    total2 = total1 - N2
    square_sum2 = square_sum1 - N
    p = (Fraction(square_sum1, total1) + Fraction(square_sum2, total2)) / 2
    print(f"{float(p):.12f}")


if __name__ == "__main__":
    main()
