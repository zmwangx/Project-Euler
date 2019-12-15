#!/usr/bin/env python3

import math

import sympy


# Exploratory.
def place_first_n_guests(n):
    placed_guests = set()
    a = 1
    floor = 1
    while a <= n:
        if a in placed_guests:
            a += 1
            continue
        floor_guests = [a]
        b = math.ceil(math.sqrt(2 * a + 1))
        x = a
        while (y := b * b - x) <= n:
            floor_guests.append(y)
            placed_guests.add(y)
            x, b = y, b + 1
        print(f"{floor}: {floor_guests}")
        a += 1
        floor += 1


def P(f, r):
    l = f // 2
    if f == 1:
        a = 1
    elif f % 2 == 0:
        a = 2 * l * l
    else:
        a = 2 * l * l + 2 * l
    # Use sympy here because double precision doesn't cut it.
    b = int(sympy.ceiling(sympy.sqrt(2 * a + 1)))
    k = (r - 1) // 2
    if r % 2 == 0:
        return -a + b * b + 2 * k * b + k * (2 * k + 1)
    else:
        return a + 2 * k * b + k * (2 * k - 1)


def main():
    # place_first_n_guests(1000)
    assert P(10, 20) == 440
    assert P(25, 75) == 4863
    assert P(99, 100) == 19454
    N = 71328803586048
    total = 0
    for f in sympy.divisors(N):
        r = N // f
        total += P(f, r)
    print(total % 100_000_000)


if __name__ == "__main__":
    main()
