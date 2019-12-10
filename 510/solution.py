#!/usr/bin/env python3

import math


def sum_triples(N):
    total = 0
    max_b = int(pow(N, 1 / 4))
    for b in range(1, max_b + 1):
        for a in range(1, b + 1):
            rb = (a + b) * (a + b) * b * b
            if rb > N:
                break
            if math.gcd(a, b) > 1:
                continue
            r_sum = (a * a + a * b + b * b) ** 2
            max_multiplier = N // rb
            total += r_sum * max_multiplier * (max_multiplier + 1) // 2
    return total


def main():
    print(sum_triples(1_000_000_000))


if __name__ == "__main__":
    main()
