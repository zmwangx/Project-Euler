#!/usr/bin/env python3

import itertools


def winning(a, b, c):
    while a or b or c:
        if ((a & 1) + (b & 1) + (c & 1)) % 2 != 0:
            return True
        a >>= 1
        b >>= 1
        c >>= 1
    return False


def S(n):
    nimber_counts = []
    m = n
    while m:
        nimber_counts.append((m + 1) // 2)
        m //= 2
    assert sum(nimber_counts) == n
    n_nimbers = len(nimber_counts)
    winning_count = 0
    for a, b, c in itertools.product(
        range(n_nimbers), range(n_nimbers), range(n_nimbers)
    ):
        if winning(a, b, c):
            winning_count += nimber_counts[a] * nimber_counts[b] * nimber_counts[c]
    return winning_count


def main():
    result = S(123456787654321)
    print(result, result % 1234567890)


if __name__ == "__main__":
    main()
