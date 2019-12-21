#!/usr/bin/env python3

import bisect
import functools
import math
import multiprocessing.pool

import sympy
import sympy.ntheory.residue_ntheory
from gmpy2 import mpz


LIMIT = 100_000_000

# Cache integer factorization.
factorint = sympy.factorint
sympy.ntheory.residue_ntheory.factorint = functools.lru_cache(maxsize=None)(factorint)
# Use mpz to speed up modular exponentiation.
sympy.ntheory.residue_ntheory.as_int = mpz


def multiplicative_order(n):
    return n, sympy.n_order(10, n)


def main():
    max2exp = int(math.log(LIMIT) / math.log(2))
    max5exp = int(math.log(LIMIT) / math.log(5))
    multipliers = sorted(
        n
        for i in range(max2exp + 1)
        for j in range(max5exp + 1)
        if 1 < (n := 2 ** i * 5 ** j) <= LIMIT
    )
    total = 0
    with multiprocessing.pool.Pool() as pool:
        for n, order in pool.imap(
            multiplicative_order, (n for n in range(3, LIMIT, 2) if n % 5 != 0), 1000,
        ):
            if n % 100_000 == 1:
                print(f"progress: {n:,}")
            i = bisect.bisect_right(multipliers, LIMIT // n)
            total += order * (i + 1)
    print(total)


if __name__ == "__main__":
    main()
