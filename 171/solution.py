#!/usr/bin/env python3

import collections
import functools
import itertools
import math


def dedupe_perm(iterable, key=None):
    counter = collections.Counter(iterable)
    total = sum(counter.values())
    key_counts = sorted(counter.items(), key=key)
    for key, count in key_counts[:-1]:
        print(key, count)


# dedupe_perm("aaaabbbcc")


def break_squares(num_digits):
    max_root = int(math.sqrt(81 * num_digits))
    results = []
    for root in range(1, max_root + 1):
        s = root * root
        q = collections.deque()
        # (current_list, remaining_sum)
        # current_list is a tuple with currently selected digits,
        # which has to be monotone decreasing.
        q.append(((), s))
        while q:
            l, remaining_sum = q.popleft()
            remaining_digits = num_digits - len(l)
            if remaining_sum == 0:
                results.append((*l, *[0 for _ in range(remaining_digits)]))
                continue
            max_digit = l[-1] - 1 if l else 9
            for d in range(min(max_digit, int(math.sqrt(remaining_sum))), 0, -1):
                d2 = d * d
                if d2 * remaining_digits < remaining_sum:
                    break
                for repeat in range(1, min(remaining_digits, remaining_sum // d2) + 1):
                    q.append(
                        ((*l, *[d for _ in range(repeat)]), remaining_sum - d2 * repeat)
                    )
    return results


@functools.lru_cache
def factorial(n):
    return factorial(n - 1) * n if n > 1 else 1


@functools.lru_cache(maxsize=None)
def multinomial(n, *args):
    assert sum(args) == n
    result = factorial(n)
    for k in args:
        result //= factorial(k)
    return result


def calculate_sum(num_digits, digit_sets):
    total = 0
    multiplier = (10 ** num_digits - 1) // 9 % 1_000_000_000
    for ds in digit_sets:
        counter = collections.Counter(ds)
        num_permutations = multinomial(num_digits, *sorted(counter.values()))
        digit_sum = (
            num_permutations * sum(d * counter[d] for d in counter) // num_digits
        )
        total += digit_sum * multiplier
        total %= 1_000_000_000
    return total


def main():
    n = 20
    digit_sets = break_squares(n)
    print(calculate_sum(n, digit_sets))


if __name__ == "__main__":
    main()
