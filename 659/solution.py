#!/usr/bin/env python3

import sympy
from miller_rabin import miller_rabin


MODULUS = 10 ** 18


def sieve_and_sum(N):
    sieve = [[] for k in range(N + 1)]
    total = 0
    report_interval = 10 ** 5
    for k in range(1, N + 1):
        if k % report_interval == 0:
            print(f"progress: {k}")
        divisors = sieve[k]
        q = 4 * k * k + 1
        max_p = 0
        for p in divisors:
            while q % p == 0:
                q //= p
            if p > max_p:
                max_p = p
        if q < max_p:
            # print(k, max_p)
            total = (total + max_p) % MODULUS
            continue
        if miller_rabin(q):
            factors = [q]
        else:
            factors = sorted(sympy.factorint(q))
        # print(k, factors[-1])
        total = (total + factors[-1]) % MODULUS
        for p in factors:
            for kk in range(k + p, N + 1, p):
                sieve[kk].append(p)
    return total


def main():
    print(sieve_and_sum(10 ** 7))


if __name__ == "__main__":
    main()
