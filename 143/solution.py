#!/usr/bin/env python3

import math


# Search for positive integer triplets (x, y, z) satisfying
#
#   x^2 + y^2 + xy = z^2,
#
# subject to x < y, x + y < LIMIT.
#
# Two cases:
# (1) x = (n^2 - m^2)l, y = m(2n + m)l, z = (m^2 + n^2 + mn)l.
# (2) x = (n^2 - m^2)l, y = n(2m - n)l, z = (m^2 + n^2 - mn)l, where
#     n/2 < m < n, z > 3n^2/4.
# In both cases gcd(m, n) = 1.
def search_pseudo_pythagorean_triples(LIMIT):
    triples = set()
    # Case 1.
    for n in range(2, int(math.sqrt(LIMIT))):
        for m in range(1, n):
            x0 = n * n - m * m
            y0 = m * (2 * n + m)
            if (x0_y0_sum := x0 + y0) >= LIMIT:
                break
            if x0 > y0:
                continue
            if math.gcd(m, n) != 1:
                continue
            z0 = m * m + n * n + m * n
            for l in range(1, int((LIMIT - 1) / x0_y0_sum) + 1):
                triples.add((x0 * l, y0 * l, z0 * l))
    # Case 2.
    for n in range(2, int(math.sqrt(LIMIT * 4 / 3)) + 1):
        for m in range(int(n / 2) + 1, n):
            x0 = n * n - m * m
            y0 = n * (2 * m - n)
            if (x0_y0_sum := x0 + y0) >= LIMIT:
                continue
            if x0 > y0:
                continue
            if math.gcd(m, n) != 1:
                continue
            z0 = m * m + n * n - m * n
            for l in range(1, int((LIMIT - 1) / x0_y0_sum) + 1):
                triples.add((x0 * l, y0 * l, z0 * l))
    return sorted(triples)


# Search for three-way overlap in the triples, (p, q, c), (q, r, a), (r,
# p, b), p < q < r. Triples are ordered.
def search_overlap(triples):
    bins = dict()
    for x, y, _ in triples:
        bin_ = bins.setdefault(x, set())
        bin_.add(y)
    results = []
    for p, possible_q_r in bins.items():
        for q in sorted(possible_q_r):
            for r in sorted(possible_q_r):
                if r < q:
                    continue
                if q in bins and r in bins[q]:
                    results.append((p, q, r))
    return results


def main():
    limit = 120000
    triples = search_pseudo_pythagorean_triples(limit)
    pqrs = search_overlap(triples)
    sums = set()
    for p, q, r in pqrs:
        if (pqr_sum := p + q + r) <= limit:
            sums.add(pqr_sum)
    print(f"total sum: {sum(sums)}")


if __name__ == "__main__":
    main()
