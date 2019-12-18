#!/usr/bin/env python3


def main():
    p = 10 ** 8 + 7
    k = 10 ** 4 + 7
    mod = 10 ** 8
    twopm1 = pow(2, p, mod) - 1
    mult1 = ((k - 1) * twopm1 + p) % mod
    mult2 = pow(2, p-k, mod)
    mult3 = twopm1 * twopm1 % mod
    print(mult1 * mult2 * mult3 % mod)


if __name__ == "__main__":
    main()
