#!/usr/bin/env python3

import collections
import functools

from gmpy2 import mpz


MODULUS = 10_000_000_000_000_000

factorial = [mpz(1)]


def precalc_factorios(n):
    for i in range(1, n + 1):
        factorial.append(factorial[-1] * i)


precalc_factorios(25025)


@functools.lru_cache(maxsize=None)
def binomial(n, k):
    return int(factorial[n] // factorial[k] // factorial[n - k] % MODULUS)


def calculate_remainders():
    remainders = [pow(i % 250, (i - 1) % 100 + 1, 250) for i in range(1, 501)]
    remainders = remainders * (250250 // 500) + remainders[:250]
    return collections.Counter(remainders)


def count_subsets(remainders):
    last_counts = [1] + [0] * 249
    for r, r_count in sorted(remainders.items()):
        additions = [0] * 250
        # Special treatment for 0 and 125 due to large r_count and easy
        # manual calculations.
        if r == 0:
            additions[0] = pow(2, r_count, MODULUS)
        elif r == 125:
            additions[0] = additions[125] = pow(2, r_count - 1, MODULUS)
        else:
            for k in range(r_count + 1):
                kr = r * k % 250
                additions[kr] = (additions[kr] + binomial(r_count, k)) % MODULUS
        current_counts = [0] * 250
        for last in range(250):
            for this in range(250):
                new = (last + this) % 250
                current_counts[new] = (
                    current_counts[new] + last_counts[last] * additions[this]
                ) % MODULUS
        last_counts = current_counts
    # Do not count the empty subset.
    return last_counts[0] - 1


def main():
    remainders = calculate_remainders()
    print(count_subsets(remainders))


if __name__ == "__main__":
    main()
