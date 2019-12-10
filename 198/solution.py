#!/usr/bin/env python3

import sys

sys.setrecursionlimit(10_000)


# Given that (x0=q1/p1, y0=q2/p2) are neighbors in a Farey sequence,
# returns the number of possible Farey sequence neighbors (x, y) in the
# range [x0, y0] (that is, x0 <= x <= y <= y0) s.t. the product of their
# denominators do not exceed max_product.
def count(p1, p2, max_product):
    if p1 * p2 > max_product:
        return 0
    if p1 == 1 and p2 * (p2 + 1) > max_product:
        # We know all the elligible neighbors in this case: (0/1, 1/p2),
        # ..., (0/1, 1/max_product).
        return max_product - p2 + 1
    p = p1 + p2
    return 1 + count(p1, p, max_product) + count(p, p2, max_product)


def main():
    # Other than midpoints of neighbors in the range [0/1, 1/100], there
    # are 49 more midpoints under 1/100: (0/1, 1/51), ... (0/1, 1/99).
    print(count(1, 100, 100_000_000 // 2) + 49)


if __name__ == "__main__":
    main()
