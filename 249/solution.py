#!/usr/bin/env python3

import collections

import miller_rabin
import primesieve


MODULUS = 10_000_000_000_000_000


def count(n):
    primes = primesieve.primes(n)
    sum_counts = collections.defaultdict(int)
    sum_counts[0] = 1
    for i, p in enumerate(primes):
        if (i + 1) % 100 == 0:
            print(f"progress: {i+1}-th prime")
        prev_sums = sorted(sum_counts.keys(), reverse=True)
        for prev_sum in prev_sums:
            sum_counts[prev_sum + p] = (
                sum_counts[prev_sum + p] + sum_counts[prev_sum]
            ) % MODULUS
    total_count = 0
    for sum_, count in sum_counts.items():
        if miller_rabin.miller_rabin(sum_):
            total_count = (total_count + count) % MODULUS
    return total_count


def main():
    print(count(5000))


if __name__ == "__main__":
    main()
