#!/usr/bin/env python3

import math
from fractions import Fraction


BOUND = 10 ** 12


def best_approx_denom(n):
    a, b, c, d = 1, 0, 0, 1
    numeric_sqrt = math.sqrt(n)
    if int(numeric_sqrt) ** 2 == n:
        return 0
    while True:
        mm = d * a - b * c
        nn = d * c * n - b * a
        ll = a * a - c * c * n
        term = math.floor((mm * numeric_sqrt + nn) / ll)
        prev_b, prev_d = b, d
        a, b, c, d = a * term + b, a, c * term + d, c
        if c > BOUND:
            if term > 1:
                for t in range(term - 1, int(term / 2), -1):
                    denom = d * t + prev_d
                    if denom <= BOUND:
                        # print(f"{n}\t{b * t + prev_b}/{denom}")
                        return denom
                if term % 2 == 0:
                    t = term // 2
                    denom = d * t + prev_d
                    if denom <= BOUND:
                        # Test which approximation is better,
                        #
                        #   r2 = (b * t + prev_b)/(d * t + prev_d)
                        #
                        # or the previous convergent r1 = b/d.
                        #
                        # r2 is better iff
                        #
                        #   (r1 - sqrt(n))^2 > (r2 - sqrt(n))^2.
                        r2 = Fraction(b * t + prev_b, denom)
                        r1 = Fraction(b, d)
                        if (r1 > r2 and (r1 + r2) ** 2 > 4 * n) or (
                            r1 < r2 and (r1 + r2) ** 2 < 4 * n
                        ):
                            # print(f"{n}\t{r2}")
                            return denom
            # print(f"{n}\t{b}/{d}")
            return d


def main():
    denom_sum = 0
    for n in range(2, 100_001):
        denom_sum += best_approx_denom(n)
    print(denom_sum)


if __name__ == "__main__":
    main()
