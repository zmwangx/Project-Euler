#!/usr/bin/env python3

import primesieve


possible_extensions = [
    # Center
    ((-1, -1), (-1, 1)),
    ((-1, -1), (1, 0)),
    ((-1, 0), (1, -1)),
    ((-1, 0), (1, 1)),
    ((-1, 1), (1, 0)),
    ((1, -1), (1, 1)),
    # Off center
    # (-1, -1)
    ((-1, -1), (-2, -2)),
    ((-1, -1), (-2, -1)),
    ((-1, -1), (-2, 0)),
    ((-1, -1), (0, -2)),
    # (-1, 0)
    ((-1, 0), (-2, -1)),
    ((-1, 0), (-2, 0)),
    ((-1, 0), (-2, 1)),
    # (-1, 1)
    ((-1, 1), (-2, 0)),
    ((-1, 1), (-2, 1)),
    ((-1, 1), (-2, 2)),
    ((-1, 1), (0, 2)),
    # (1, -1)
    ((1, -1), (0, -2)),
    ((1, -1), (2, -2)),
    ((1, -1), (2, -1)),
    ((1, -1), (2, 0)),
    # (1, 0)
    ((1, 0), (2, -1)),
    ((1, 0), (2, 0)),
    ((1, 0), (2, 1)),
    # (1, 1)
    ((1, 1), (0, 2)),
    ((1, 1), (2, 0)),
    ((1, 1), (2, 1)),
    ((1, 1), (2, 2)),
]


def search_row(n):
    # (n+k)-th row: (n+k-1)(n+k)/2 + 1 to (n+k+1)(n+k)/2
    # (n-2)-th to (n+2)-th row: (n-2)(n-3)/2 + 1 to (n+2)(n+3)/2
    primes = primesieve.primes((n - 2) * (n - 3) // 2 + 1, (n + 2) * (n + 3) // 2)

    rows = {row_num: [False for _ in range(row_num)] for row_num in range(n - 2, n + 3)}
    row_starts = {}

    row_start = (n - 2) * (n - 3) // 2 + 1
    row_num = n - 2
    row_starts[row_num] = row_start

    nth_row_prime_coords = []
    for p in primes:
        if p >= row_start + row_num:
            row_start = row_start + row_num
            row_num += 1
            row_starts[row_num] = row_start
        rows[row_num][p - row_start] = True
        if row_num == n:
            nth_row_prime_coords.append(p - row_start)

    elligible_primes = []
    x = n
    for y in nth_row_prime_coords:
        p = row_starts[x] + y
        for (dx1, dy1), (dx2, dy2) in possible_extensions:
            x1 = x + dx1
            y1 = y + dy1
            x2 = x + dx2
            y2 = y + dy2
            if not (0 <= y1 < x1 and 0 <= y2 < x2):
                continue
            if rows[x1][y1] and rows[x2][y2]:
                elligible_primes.append(p)
                break

    return elligible_primes


def main():
    print(sum(search_row(5678027)) + sum(search_row(7208785)))


if __name__ == "__main__":
    main()
