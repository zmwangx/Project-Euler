#!/usr/bin/env python3

import math
from collections import deque
from fractions import Fraction

import primesieve


LIMIT = 80
USABLE = [True] * (LIMIT + 1)


def find_prime_factor_combos(p):
    print(f"considering prime factor {p}...")
    potential = [n for n in range(p, LIMIT + 1, p) if USABLE[n]]
    k = len(potential)
    combos = []
    current_sum = Fraction(0)
    arr = [0] * k
    for _ in range(2 ** k - 1):
        i = 0
        while arr[i] == 1:
            arr[i] = 0
            current_sum -= Fraction(1, potential[i] ** 2)
            i += 1
        arr[i] = 1
        current_sum += Fraction(1, potential[i] ** 2)
        if current_sum.denominator % p != 0 and current_sum <= 1 / 2:
            combo = tuple(potential[i] for i in range(k) if arr[i])
            combos.append(combo)
    combos = sorted(combos)
    rejected = set(potential).difference(*combos)
    for n in rejected:
        USABLE[n] = False
    if combos:
        print(f"found {len(combos)} combos")
        # for combo in combos:
        #     print(combo)
    return [set(combo) for combo in combos]


def find_fat_combos(single_factor_combos):
    print("checking compatibility...")
    # A FIFO queue for BFS. Each element is of the form
    #
    #   (depth, combo, forbidden): (int, set, set)
    #
    # where depth is the next index in single_factor_combos to look,
    # combo is the current fat combo, and forbidden is the known set of
    # numbers forbidden by the combo.
    queue = deque()
    queue.append((0, set(), set()))
    maxdepth = len(single_factor_combos)
    while queue and queue[0][0] < maxdepth:
        depth, combo, forbidden = queue.popleft()
        p, p_combos = single_factor_combos[depth]
        existing_p_multiples = set(n for n in combo if n % p == 0)
        for p_combo in p_combos:
            if existing_p_multiples <= p_combo and not (p_combo & forbidden):
                new_combo = combo.copy()
                new_forbidden = forbidden.copy()
                new_combo |= p_combo
                new_forbidden |= set(range(p, LIMIT + 1, p)) - p_combo
                queue.append((depth + 1, new_combo, new_forbidden))
    fat_combos = [combo for _, combo, _ in queue]
    print(f"found {len(fat_combos)} fat combos")
    # for fat_combo in sorted(tuple(sorted(combo)) for combo in fat_combos):
    #     print(fat_combo)
    return fat_combos


def find_result_combos(fat_combos):
    print("searching for results...")
    choices = []
    n = 2
    while n <= LIMIT:
        choices.append((n, Fraction(1, n * n)))
        n *= 2
    results = []
    for combo in fat_combos:
        inverse_square_sum = sum(Fraction(1, n * n) for n in combo)
        remaining = Fraction(1, 2) - inverse_square_sum
        for n, contrib in choices:
            if remaining == contrib:
                combo.add(n)
                results.append(combo)
                break
            if remaining < contrib:
                continue
            combo.add(n)
            remaining -= contrib
    results = sorted(tuple(sorted(combo)) for combo in results)
    for result in results:
        print(result)
    print(f"found {len(results)} results")


def main():
    primes = primesieve.primes(3, LIMIT)
    single_factor_combos = []
    for p in reversed(primes):
        combos = find_prime_factor_combos(p)
        if combos:
            single_factor_combos.insert(0, (p, [set()] + combos))
    fat_combos = find_fat_combos(single_factor_combos)
    find_result_combos(fat_combos)


if __name__ == "__main__":
    main()
