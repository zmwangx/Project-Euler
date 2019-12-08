#!/usr/bin/env python3

import functools
import math

import sympy.ntheory


@functools.lru_cache(maxsize=None)
def lcm(a, b):
    return a * b // math.gcd(a, b)


p = 1009
q = 3643
phi = (p - 1) * (q - 1)
period = lcm(p - 1, q - 1)
modp_order = [1 if a == 0 else sympy.ntheory.n_order(a, p) for a in range(p)]
modq_order = [1 if a == 0 else sympy.ntheory.n_order(a, q) for a in range(q)]


def calculate_unconcealed_counts():
    # counts[(e - 1) % period] is the unconcealed count of e.
    counts = [0 for _ in range(period)]
    # We skip m = 0 or 1 since m^e = m for all e when m = 0 or 1.
    for m in range(2, p * q - 1):
        order = lcm(modp_order[m % p], modq_order[m % q])
        if order > 1:
            for i in range(0, period, order):
                counts[i] += 1
    return counts


def main():
    counts = calculate_unconcealed_counts()
    filtered_counts = {
        i + 1: counts[i] for i in range(period) if math.gcd(i + 1, phi) == 1
    }
    min_count = min(filtered_counts.values())
    num_minimizer = 0
    sum_minimizer = 0
    for i in filtered_counts:
        if filtered_counts[i] == min_count:
            num_minimizer += 1
            sum_minimizer += i
    num_periods = phi // period
    total_sum = (
        sum_minimizer * num_periods
        + (num_periods - 1) * num_periods // 2 * period * num_minimizer
    )
    print(total_sum)


if __name__ == "__main__":
    main()
