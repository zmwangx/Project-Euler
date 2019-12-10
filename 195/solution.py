#!/usr/bin/env python3

import math


def search(r):
    max_bc_minus_a = int(r * 2 * math.sqrt(3))
    count = 0

    x = 1
    while (3 * x - 1) // 2 <= max_bc_minus_a:
        y = 1
        while y < x:
            if y % 3 != 0 and math.gcd(x, y) == 1:
                a = (3 * x * x + y * y) // 4
                b = x * y
                c = (3 * x - y) * (x + y) // 4
                bc_minus_a = b + c - a
                if bc_minus_a > max_bc_minus_a:
                    break
                # print(x, y, a, b, c)
                count += max_bc_minus_a // bc_minus_a
            y += 2
        x += 2

    x = 1
    while 3 * x * (x + 1) <= max_bc_minus_a:
        y = 3 * x + 2
        while True:
            if y % 3 != 0 and math.gcd(x, y) == 1:
                a = (3 * x * x + y * y) // 4
                b = x * y
                c = (y - x) * (y + 3 * x) // 4
                bc_minus_a = b + c - a
                if bc_minus_a > max_bc_minus_a:
                    break
                # print(x, y, a, b, c)
                count += max_bc_minus_a // bc_minus_a
            y += 2
        x += 2

    x = 1
    while 6 * x - 2 <= max_bc_minus_a:
        y = 1 if x % 2 == 0 else 2
        while y < x:
            if y % 3 != 0 and math.gcd(x, y) == 1:
                a = 3 * x * x + y * y
                b = 4 * x * y
                c = (3 * x - y) * (x + y)
                bc_minus_a = b + c - a
                if bc_minus_a > max_bc_minus_a:
                    break
                # print(x, y, a, b, c)
                count += max_bc_minus_a // bc_minus_a
            y += 2
        x += 1

    x = 1
    while 6 * x * (2 * x + 1) <= max_bc_minus_a:
        y = 3 * x + 1
        while True:
            if y % 3 != 0 and math.gcd(x, y) == 1:
                a = 3 * x * x + y * y
                b = 4 * x * y
                c = (y - x) * (y + 3 * x)
                bc_minus_a = b + c - a
                if bc_minus_a > max_bc_minus_a:
                    break
                # print(x, y, a, b, c)
                count += max_bc_minus_a // bc_minus_a
            y += 2
        x += 1

    return count


def main():
    print(search(1053779))


if __name__ == "__main__":
    main()
