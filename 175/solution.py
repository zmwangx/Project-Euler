#!/usr/bin/env python3

from fractions import Fraction


def min_n_for(ratio):
    if ratio.denominator == 1:
        return [(1, 1), (0, int(ratio) - 1)]
    elif ratio < 1:
        # r = f(2k+1) / f(2k) = f(k) / (f(k) + f(k-1))
        # f(k) / f(k-1) = r/(1-r)
        k = min_n_for(ratio / (1 - ratio))
        last_digit, repeat = k[-1]
        if last_digit == 0:
            k.append((1, 1))
        else:
            k[-1] = (1, repeat + 1)
        return k
    else:
        # r = f(2k) / f(2k-1) = (f(k) + f(k-1)) / f(k-1)
        # f(k) / f(k-1) = r-1
        # f(k') / f(k'-1) = r - r' where n = 2^r' k'.
        k = min_n_for(ratio % 1)
        last_digit, repeat = k[-1]
        if last_digit == 0:
            k[-1] = (0, repeat + int(ratio))
        else:
            k.append((0, int(ratio)))
        return k


def main():
    n = min_n_for(Fraction(123456789, 987654321))
    print(",".join(str(repeat) for _, repeat in n))


if __name__ == "__main__":
    main()
