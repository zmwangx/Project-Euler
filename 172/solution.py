#!/usr/bin/env python3

import functools
import itertools
import operator


N = 18
factorios = [functools.reduce(operator.mul, range(1, i + 1), 1) for i in range(N + 1)]


# Calculates the multinomial for n and [k1, k2, ..., kr], where sum(ks) = n.
def multinomial(n, ks):
    return factorios[n] // functools.reduce(operator.mul, (factorios[k] for k in ks), 1)


def calculate_count(n):
    count = 0
    for combo in itertools.product(*[range(4) for _ in range(10)]):
        if sum(combo) != n:
            continue
        count += multinomial(n, combo)
        if combo[0] > 0:
            # Remove choices with a leading zero.
            count -= multinomial(n - 1, (combo[0] - 1, *combo[1:]))
    return count


def main():
    print(calculate_count(N))


if __name__ == "__main__":
    main()
