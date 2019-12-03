#!/usr/bin/env python3

import sympy


N = 9


def search():
    count = 0
    for v1 in range(N + 1):
        for v2 in range(N + 1):
            for n in range(max(v1, v2, 1), N + 1):
                remaining = (2 ** (n - v1)) * (5 ** (n - v2))

                a0 = 2 ** v1
                b0 = 5 ** v2
                count += sympy.divisor_count(remaining * (a0 + b0))

                if v1 == 0 or v2 == 0:
                    continue

                a0 = (2 ** v1) * (5 ** v2)
                b0 = 1
                count += sympy.divisor_count(remaining * (a0 + b0))
    return count


def main():
    print(search())


if __name__ == "__main__":
    main()
