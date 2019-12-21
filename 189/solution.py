#!/usr/bin/env python3

import functools
import itertools


@functools.lru_cache(maxsize=None)
def count(bottom_colors):
    length = len(bottom_colors)
    if length == 1:
        return 1
    total = 0
    for complement_colors in itertools.product(
        *[
            sorted(set((0, 1, 2)) - set((bottom_colors[i], bottom_colors[i + 1])))
            for i in range(length - 1)
        ]
    ):
        for sub_bottom_colors in itertools.product(
            *[[i for i in range(3) if i != color] for color in complement_colors]
        ):
            total += count(sub_bottom_colors)
    return total


def main():
    print(
        sum(
            count(bottom_colors)
            for bottom_colors in itertools.product(*([(0, 1, 2)] * 8))
        )
    )


if __name__ == "__main__":
    main()
