#!/usr/bin/env python3

import sympy.ntheory

divisors = sympy.ntheory.factor_.divisors


def main():
    n = 60
    sizes = set(s + 1 for s in divisors(2 ** n - 1))
    for d in divisors(n):
        if d != n:
            sizes -= set(s + 1 for s in divisors(2 ** d - 1))
    print(sum(sizes))


if __name__ == "__main__":
    main()
