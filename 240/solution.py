#!/usr/bin/env python3

import collections
import functools

import sympy


SIDES = 12
N_DICE = 20
TOP_COUNT = 10
TOP_SUM = 70

factorial = [sympy.factorial(i) for i in range(N_DICE + 1)]


def count_combos_with_prefix(prefix):
    remaining = N_DICE - len(prefix)
    count = factorial[N_DICE] // factorial[remaining]
    for multiplicity in collections.Counter(prefix).values():
        count //= factorial[multiplicity]
    return count * ((prefix[-1] - 1) ** remaining)


@functools.lru_cache(maxsize=None)
def count(num, sum_, curr_min=SIDES):
    if num > sum_:
        return 0
    if num == 1:
        return 1 if 1 <= sum_ <= curr_min else 0
    return sum(count(num - 1, sum_ - i, i) for i in range(1, curr_min + 1))


def generate_prefixes():
    q = collections.deque()
    q.append((0, ()))
    while q:
        curr_sum, prefix = q.popleft()
        if len(prefix) == TOP_COUNT:
            if curr_sum == TOP_SUM:
                yield prefix
                last = prefix[-1]
                for _ in range(N_DICE - TOP_COUNT):
                    prefix = (*prefix, last)
                    yield prefix
            continue
        for i in range(1, (prefix[-1] if prefix else SIDES) + 1):
            new_sum = curr_sum + i
            if new_sum <= TOP_SUM:
                q.append((new_sum, (*prefix, i)))


def main():
    count = 0
    for prefix in generate_prefixes():
        count += count_combos_with_prefix(prefix)
    print(count)


if __name__ == "__main__":
    main()
