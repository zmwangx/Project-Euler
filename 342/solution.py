#!/usr/bin/env python3

import collections
import math

import primesieve
import sympy.ntheory


bound = 10 ** 10

primes = []
factorizations = []
appearances = []
results = set()


def search(n, max_pindex, orphans):
    if not orphans:
        results.add(n)
        return
    max_orphan_index = max(orphans.keys())
    for i, p, _ in [(max_orphan_index, primes[max_orphan_index], 0)] + appearances[
        max_orphan_index
    ]:
        if i >= max_pindex:
            break
        if n % p == 0:
            continue
        m = n * p
        pexp = 2
        orphans_with_pm1 = orphans.copy()
        for j, _, e in factorizations[i]:
            orphans_with_pm1[j] = (orphans_with_pm1.setdefault(j, 0) + e) % 3
            if orphans_with_pm1[j] == 0:
                del orphans_with_pm1[j]
        while m < bound:
            new_orphans = orphans_with_pm1.copy()
            new_orphans[i] = (new_orphans.setdefault(i, 0) + pexp - 1) % 3
            if new_orphans[i] == 0:
                del new_orphans[i]
            search(m, max_pindex, new_orphans)
            m *= p
            pexp += 2


def main():
    global primes, factorizations, appearances
    prime_bound = int(math.sqrt(bound))
    primes = primesieve.primes(prime_bound)
    prime_index = {p: i for i, p in enumerate(primes)}
    appearances = [[] for _ in primes]
    for i, p in enumerate(primes):
        factorization = []
        for q, e in sorted(sympy.ntheory.factorint(p - 1).items(), reverse=True):
            factorization.append((prime_index[q], q, e))
            appearances[prime_index[q]].append((i, p, e))
        factorizations.append(factorization)

    for i, p in enumerate(primes):
        orphans = {j: e % 3 for j, _, e in factorizations[i] if e % 3 != 0}
        n = p * p
        while n < bound:
            search(n, i, orphans)
            n *= p * p * p

    global results
    count = len(results)
    sorted_results = sorted(results)
    s = collections.deque()
    s.append((1, -1))
    while s:
        n, i = s.pop()
        if n != 1:
            results.add(n)
        for j in range(i + 1, count):
            prod = n * sorted_results[j]
            if prod >= bound:
                break
            if math.gcd(n, sorted_results[j]) == 1:
                s.append((prod, j))
    # print(sorted(results))
    print(sum(results))


if __name__ == "__main__":
    main()
