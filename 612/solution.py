#!/usr/bin/env python3

import sympy


LENGTH = 18


def main():
    k = LENGTH
    n = [[0, 0] for i in range(11)]
    n[0][1] = 10 ** k
    for i in range(1, 11):
        n[i][1] = ((-1) ** i) * ((10 - i) ** k)
        for j in range(i):
            n[i][1] += ((-1) ** (i - 1 - j)) * sympy.binomial(i, j) * n[j][1]
        if i != 9:
            n[i][0] = ((-1) ** i) * ((10 - i) ** (k + 1) - 1) // (9 - i)
        else:
            n[i][0] = -(k + 1)
        for j in range(i):
            n[i][0] += (-1) ** (i - 1 - j) * (
                sympy.binomial(i - 1, j) * n[j][1]
                + (sympy.binomial(i, j) - sympy.binomial(i - 1, j)) * n[j][0]
            )
        # print(n[i][1], n[i][0])
    count = 0
    for i in range(1, 11):
        count += ((-1) ** (i - 1)) * (
            sympy.binomial(9, i) * sympy.binomial(n[i][1], 2)
            + (sympy.binomial(10, i) - sympy.binomial(9, i))
            * sympy.binomial(n[i][0], 2)
        )
    print(count, count % 1000267129)


if __name__ == "__main__":
    main()
