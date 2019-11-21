#!/usr/bin/env python3

import itertools


def generate_example_sequence():
    triangle = [
        [15],
        [-14, -7],
        [20, -13, -5],
        [-3, 8, 23, -26],
        [1, -4, -5, -18, 5],
        [-16, 31, 2, 9, 28, 3],
    ]
    return list(itertools.chain(*triangle)), 6


def generate_prng_sequence(n):
    size = n * (n + 1) // 2
    s = []
    t = 0
    for _ in range(size):
        t = (615949 * t + 797807) % (2 ** 20)
        s.append(t - 2 ** 19)
    return s, n


# n is the number of rows, s is the sequence with n(n+2)/2 elements.
def find_min_sum(s, n):
    # partial_sums[i] is the sum of the 0..i-1 elements.
    partial_sums = [0] * (len(s) + 1)
    for i, elem in enumerate(s):
        partial_sums[i + 1] = partial_sums[i] + elem
    print(min(partial_sums))
    min_sum = 0
    for a in range(n):
        for b in range(a + 1):
            _sum = 0
            for d in range(n - a):
                # Add the sum of elements from (a+d, b) to (a+d, b+d)
                row_start_index = (a + d) * (a + d + 1) // 2
                _sum += (
                    partial_sums[row_start_index + b + d + 1]
                    - partial_sums[row_start_index + b]
                )
                if _sum < min_sum:
                    min_sum = _sum
    return min_sum


def main():
    # print(find_min_sum(*generate_example_sequence()))
    print(find_min_sum(*generate_prng_sequence(1000)))


if __name__ == "__main__":
    main()
