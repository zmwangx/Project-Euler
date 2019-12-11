#!/usr/bin/env python3

import functools
import math


def lcm(a, b):
    return a * b // math.gcd(a, b)


@functools.lru_cache(maxsize=None)
def lcm_up_to(n):
    return 1 if n == 1 else lcm(lcm_up_to(n - 1), n)


def P(s, N):
    # divisor | n - 1
    divisor = lcm_up_to(s)
    if divisor % (s + 1) == 0:
        return 0
    period = lcm_up_to(s + 1)
    per_period = period // divisor - 1
    q, r = divmod(N - 1, period)
    return per_period * q + (r - 1) // divisor


def main():
    print(sum(P(i, 4 ** i) for i in range(1, 32)))


if __name__ == "__main__":
    main()
