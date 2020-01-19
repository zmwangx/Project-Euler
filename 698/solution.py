#!/usr/bin/env python3

import functools
import itertools


TARGET = 111111111111222333


@functools.lru_cache(maxsize=None)
def factorial(n):
    if n == 0:
        return 1
    return n * factorial(n - 1)


def multinomial(n, *args):
    assert sum(args) == n
    result = factorial(n)
    for m in args:
        result //= factorial(m)
    return result


def count_with_prefix(prefix_config, allowed_configs):
    prefix_length, p1, p2, p3 = prefix_config
    remaining_length = allowed_configs[0][0] - prefix_length
    count = 0
    for config in allowed_configs:
        _, t1, t2, t3 = config
        if t1 < p1 or t2 < p2 or t3 < p3:
            continue
        count += multinomial(remaining_length, t1 - p1, t2 - p2, t3 - p3)
    return count


def nth(n, allowed_configs):
    length = allowed_configs[0][0]
    prefix_config = (0, 0, 0, 0)
    result = []
    for _ in range(length):
        prefix_length, p1, p2, p3 = prefix_config
        count1 = count_with_prefix((prefix_length + 1, p1 + 1, p2, p3), allowed_configs)
        if n <= count1:
            result.append("1")
            prefix_config = (prefix_length + 1, p1 + 1, p2, p3)
            continue
        count2 = count_with_prefix((prefix_length + 1, p1, p2 + 1, p3), allowed_configs)
        if n <= count1 + count2:
            n -= count1
            result.append("2")
            prefix_config = (prefix_length + 1, p1, p2 + 1, p3)
            continue
        n -= count1 + count2
        result.append("3")
        prefix_config = (prefix_length + 1, p1, p2, p3 + 1)
    return int("".join(result))


def main():
    nums = [0, 1, 2, 3, 11, 12, 13, 21, 22, 23, 31, 32, 33]
    configs = []
    for counts in itertools.product(nums, nums, nums):
        configs.append((sum(counts), *counts))
    configs.sort()
    i = 1  # Skip (0, 0, 0, 0)
    total_count = 0
    while i < len(configs):
        length = configs[i][0]
        length_configs = []
        while i < len(configs) and configs[i][0] == length:
            length_configs.append(configs[i])
            i += 1
        length_count = count_with_prefix((0, 0, 0, 0), length_configs)
        if total_count + length_count < TARGET:
            total_count += length_count
            continue
        result = nth(TARGET - total_count, length_configs)
        print(result, result % 123123123)
        break


if __name__ == "__main__":
    main()
