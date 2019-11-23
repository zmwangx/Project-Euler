#!/usr/bin/env python3

import math


def search_m(inv_p):
    p = 1 / inv_p
    r = 1
    while True:
        if r / (2 ** (r + 1) - 2) < p:
            break
        r += 1
    if (threshold := r * float(inv_p)).is_integer():
        s = int(threshold) + 1
    else:
        s = math.ceil(threshold)
    return s * (s + 1)


def main():
    print(search_m(12345))


if __name__ == "__main__":
    main()
