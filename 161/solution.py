#!/usr/bin/env python3

import functools


M = 9
N = 12

triominoes = [
    3 + (1 << (M + 1)),
    3 + (2 << (M + 1)),
    1 + (3 << (M + 1)),
    1 + (3 << M),
    1 + (1 << (M + 1)) + (1 << (2 * M + 2)),
    7,
]

empty_line = 1 << M  # A 1 following M 0s; the 1 acts as barrier between two lines
filled_line = (1 << (M + 1)) - 1  # (M+1) 1s


@functools.lru_cache(maxsize=None)
def search(first_three_lines_mask, n_remaining_lines):
    first_empty_block = 1
    while first_empty_block & first_three_lines_mask:
        first_empty_block <<= 1
    count = 0
    for triomino in triominoes:
        mask = triomino * first_empty_block
        if mask & ~first_three_lines_mask == mask:
            new_first_three_lines_mask = first_three_lines_mask | mask
            n_filled_lines = 0
            while new_first_three_lines_mask & filled_line == filled_line:
                n_filled_lines += 1
                new_first_three_lines_mask >>= M + 1
            if new_first_three_lines_mask == 0 and n_remaining_lines == 0:
                # Completely filled.
                return 1
            new_n_remaining_lines = max(n_remaining_lines - n_filled_lines, 0)
            line_number = 3 - n_filled_lines
            for _ in range(n_remaining_lines - new_n_remaining_lines):
                new_first_three_lines_mask |= empty_line << (line_number * (M + 1))
                line_number += 1
            for _ in range(n_filled_lines - n_remaining_lines):
                new_first_three_lines_mask |= filled_line << (line_number * (M + 1))
            count += search(new_first_three_lines_mask, new_n_remaining_lines)
    return count


def main():
    three_empty_lines = (
        empty_line | (empty_line << (M + 1)) | (empty_line << (2 * M + 2))
    )
    print(search(three_empty_lines, N - 3))


if __name__ == "__main__":
    main()
