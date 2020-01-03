#!/usr/bin/env python3

import functools


@functools.lru_cache(maxsize=None)
def M(C, R):
    if R <= C - 1:
        return R + 1
    last = M(C, R - 1)
    return 2 * ((last - 2) // (C - 2)) + last + 1


def main():
    print(sum(M(C, 30) for C in range(3, 41)))


if __name__ == "__main__":
    main()
