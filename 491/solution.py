#!/usr/bin/env python3

import collections
import functools


DIGITS = tuple(range(10))
DIGIT_COUNTS = collections.Counter(DIGITS) + collections.Counter(DIGITS)
FACTORIAL = [1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800]


@functools.lru_cache(maxsize=None)
def multinomial(*args):
    n = sum(args)
    r = FACTORIAL[n]
    for k in args:
        r //= FACTORIAL[k]
    return r


# even_digits are the digits occupying 10^0, 10^2, ..., 10^18.
def count_arrangements(even_digits):
    even_digit_counts = collections.Counter(even_digits)
    odd_digit_counts = DIGIT_COUNTS - even_digit_counts
    even_digit_arrangements = multinomial(*sorted(even_digit_counts.values()))
    odd_digit_arrangements = multinomial(*sorted(odd_digit_counts.values()))
    # The 10^19 digit can't be 0.
    if odd_digit_counts[0] > 0:
        odd_digit_counts[0] -= 1
        odd_digit_arrangements -= multinomial(*sorted(odd_digit_counts.values()))
    return even_digit_arrangements * odd_digit_arrangements


def search(current_digits, current_sum, remaining_digit_count, target_sum, pool):
    if remaining_digit_count == 0:
        if current_sum == target_sum:
            return count_arrangements(current_digits)
        else:
            return 0
    if remaining_digit_count > len(pool) * 2:
        return 0
    d = pool[0]
    pool = pool[1:]
    result = search(
        current_digits, current_sum, remaining_digit_count, target_sum, pool
    )
    result += search(
        current_digits + [d],
        current_sum + d,
        remaining_digit_count - 1,
        target_sum,
        pool,
    )
    if remaining_digit_count > 1:
        result += search(
            current_digits + [d, d],
            current_sum + d * 2,
            remaining_digit_count - 2,
            target_sum,
            pool,
        )
    return result


def main():
    result = 0
    for even_digits_sum in (23, 34, 45, 56, 67):
        result += search([], 0, 10, even_digits_sum, DIGITS)
    print(result)


if __name__ == "__main__":
    main()
