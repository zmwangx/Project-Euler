#!/usr/bin/env python3

import functools


@functools.lru_cache
def fibonacci(n):
    if n == 0:
        return 1
    if n == 1:
        return 2
    return fibonacci(n - 1) + fibonacci(n - 2)


def main():
    print(fibonacci(30))


if __name__ == "__main__":
    main()
