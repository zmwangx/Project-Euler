#!/usr/bin/env python3

from fractions import Fraction


LIMIT = 35


def search():
    sums = set()
    square2root = {i * i: i for i in range(1, LIMIT + 1)}
    for b1 in range(2, LIMIT + 1):
        for a1 in range(1, b1):
            x = Fraction(a1, b1)
            if x.denominator != b1:
                continue
            xinv = 1 / x
            for b2 in range(2, b1 + 1):
                for a2 in range(1, b2):
                    y = Fraction(a2, b2)
                    if y.denominator != b2:
                        continue
                    yinv = 1 / y

                    s1 = x + y
                    if s1 < 1 and s1.denominator <= LIMIT:
                        # print(1, x, y, s1)
                        sums.add(x + y + s1)

                    s2 = x * x + y * y
                    if (
                        s2 < 1
                        and s2.numerator in square2root
                        and s2.denominator in square2root
                    ):
                        z = Fraction(
                            square2root[s2.numerator], square2root[s2.denominator]
                        )
                        # print(2, x, y, z)
                        sums.add(x + y + z)

                    sm1 = xinv + yinv
                    if sm1 > 1 and sm1.numerator <= LIMIT:
                        z = 1 / sm1
                        # print(-1, x, y, z)
                        sums.add(x + y + z)

                    sm2 = xinv * xinv + yinv * yinv
                    if (
                        sm2 > 1
                        and sm2.numerator in square2root
                        and sm2.denominator in square2root
                    ):
                        z = Fraction(
                            square2root[sm2.denominator], square2root[sm2.numerator]
                        )
                        # print(-2, x, y, z)
                        sums.add(x + y + z)
    t = sum(sums)
    print(t, t.numerator + t.denominator)


def main():
    search()


if __name__ == "__main__":
    main()
