#!/usr/bin/env python3

import functools


# DP approach: m(n,k) = (winning, max_take) gives whether a starting
# state of n stones, allowing up to k stones to be taken is a winning
# state, and if so, the max number of stones that can be taken on the
# first turn.
@functools.lru_cache(maxsize=None)
def m(n, k):
    if n == 0:
        return (False, 0)
    if n <= k:
        return (True, n)
    for i in range(k, 0, -1):
        if not m(n - i, 2 * i)[0]:
            return (True, i)
    return (False, 0)


def consecutive_integers_sum(start, length):
    return (2 * start + length - 1) * length // 2


def sum_m(n):
    fibo = [1, 1]
    while True:
        f = fibo[-1] + fibo[-2]
        fibo.append(f)
        if f > n:
            break
    total = 0
    for i, f in enumerate(fibo):
        if f == 1:
            continue
        lower = f
        upper = min(fibo[i + 1], n + 1)
        losing = f
        j = i
        while True:
            # print(lower, losing, lower - losing)
            new_lower = min(losing + (fibo[j] + 1) // 2, upper)
            total += consecutive_integers_sum(lower - losing, new_lower - lower)
            if new_lower >= upper:
                break
            j -= 2
            losing += fibo[j]
            lower = new_lower
        if upper > n:
            break
    return total


def main():
    # print(sum(m(i, i - 1)[1] for i in range(2, 100)))
    print(sum_m(10 ** 18) % (10 ** 8))


if __name__ == "__main__":
    main()
