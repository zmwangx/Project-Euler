#!/usr/bin/env python3

import math
import itertools

import sympy.ntheory


def search():
    for perm in itertools.permutations("9876543210"):
        for splitpos in range(1, 9):
            if perm[splitpos] == "0":
                continue
            part1 = perm[:splitpos]
            n1 = int("".join(part1))
            if n1 % 3 != 0:
                continue
            part2 = perm[splitpos:]
            n2 = int("".join(part2))
            g = math.gcd(n1, n2)
            for d in sympy.ntheory.divisors(g // 3):
                a = 3 * d
                s = str(a) + str(n1 // a) + str(n2 // a)
                if len(s) == 10 and len(set(s)) == 10:
                    print(a, n1 // a, n2 // a, "".join(perm))
                    return


def main():
    search()


if __name__ == "__main__":
    main()
