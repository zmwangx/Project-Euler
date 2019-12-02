#!/usr/bin/env python3

import collections
import math


factorial = []


def prepopulate_factorials(n):
    global factorial
    factorial.append(1)
    for i in range(1, n + 1):
        factorial.append(factorial[i - 1] * i)


prepopulate_factorials(70)


def binom(n, k):
    return factorial[n] // factorial[k] // factorial[n - k]


def multinomial(n, *ks):
    assert sum(ks) == n
    r = factorial[n]
    for k in ks:
        r //= factorial[k]
    return r


def calculate_combo_count(*ball_counts):
    color_choices = multinomial(
        7, *collections.Counter(ball_counts).values(), 7 - len(ball_counts)
    )
    ball_choices = 1
    for c in ball_counts:
        ball_choices *= binom(10, c)
    return color_choices * ball_choices


def main():
    r = 20
    total_count = 0
    total_colors = 0
    for a in range(math.ceil(r / 7), 11):
        r -= a
        for b in range(math.ceil(r / 6), min(r, a) + 1):
            if r == b:
                count = calculate_combo_count(a, b)
                total_count += count
                total_colors += 2 * count
                continue
            r -= b
            for c in range(math.ceil(r / 5), min(r, b) + 1):
                if r == c:
                    count = calculate_combo_count(a, b, c)
                    total_count += count
                    total_colors += 3 * count
                    continue
                r -= c
                for d in range(math.ceil(r / 4), min(r, c) + 1):
                    if r == d:
                        count = calculate_combo_count(a, b, c, d)
                        total_count += count
                        total_colors += 4 * count
                        continue
                    r -= d
                    for e in range(math.ceil(r / 3), min(r, d) + 1):
                        if r == e:
                            count = calculate_combo_count(a, b, c, d, e)
                            total_count += count
                            total_colors += 5 * count
                            continue
                        r -= e
                        for f in range(math.ceil(r / 2), min(r, e) + 1):
                            if r == f:
                                count = calculate_combo_count(a, b, c, d, e, f)
                                total_count += count
                                total_colors += 6 * count
                                continue
                            g = r - f
                            count = calculate_combo_count(a, b, c, d, e, f, g)
                            total_count += count
                            total_colors += 7 * count
                        r += e
                    r += d
                r += c
            r += b
        r += a
    assert total_count == binom(70, 20)
    expectation = total_colors / total_count
    print(f"{expectation:.9f}")


if __name__ == "__main__":
    main()
