#!/usr/bin/env python3

import math


def is_square(n):
    return int(math.sqrt(n)) ** 2 == n


def main():
    a = 0
    while True:
        a += 1
        a2 = a * a
        for c in range(2, a):
            c2 = c * c
            f2 = a2 - c2
            if not is_square(f2):
                continue
            # e has the same parity as f.
            parity = (f2 + 1) % 2 + 1
            for e in range(parity, c, 2):
                e2 = e * e
                d2 = a2 - e2
                if c2 <= d2 or not is_square(d2):
                    continue
                b2 = c2 - e2
                if not is_square(b2):
                    continue
                x = (a2 + b2) // 2
                y = (a2 - b2) // 2
                z = (c2 - d2) // 2
                print(f"x = {x}, y = {y}, z = {z}, x + y + z = {x + y + z}")
                return

if __name__ == "__main__":
    main()
