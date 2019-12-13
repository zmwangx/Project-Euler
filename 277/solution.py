#!/usr/bin/env python3

import math

import sympy
from sympy.polys import Poly
from sympy.abc import x


def main():
    # sequence = "DdDddUUdDD"
    # lower_bound = 10 ** 6
    sequence = "UDDDUdddDDUDDddDdDddDDUDDdUUDd"
    lower_bound = 10 ** 15
    p = x
    for ch in reversed(sequence):
        if ch == "D":
            p = 3 * p
        elif ch == "U":
            p = (3 * p - 2) / 4
        elif ch == "d":
            p = (3 * p + 1) / 2
        else:
            raise NotImplementedError
    p = Poly(p)
    print(p)
    a, b = p.all_coeffs()
    n_a, d_a = sympy.fraction(a)
    n_b, d_b = sympy.fraction(b)
    assert d_a == d_b
    d = d_a
    r = (-n_b) * pow(n_a, -1, d) % d
    assert (r * n_a + n_b) % d == 0
    n_a %= d
    n_b %= d
    minimal = int(a * r + b)
    step = int(a * d)
    offset = math.ceil((lower_bound + 1 - minimal) / step)
    print(f"{minimal} + {step} * {offset} = {minimal + step * offset}")


if __name__ == "__main__":
    main()
