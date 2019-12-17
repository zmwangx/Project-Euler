#!/usr/bin/env python3

import functools
import math


@functools.lru_cache(maxsize=None)
def g(n):
    if n == 1:
        return 1
    result = math.floor((n + 1) / 2) ** 2
    floorsqrtn = math.floor(math.sqrt(n))
    m = 3
    while (qnm := n // m) >= floorsqrtn + 1:
        result -= g(qnm)
        m += 2
    for d in range(1, floorsqrtn + 1):
        result -= (
            math.floor((n / d + 1) / 2) - math.ceil(((n + 1) / (d + 1) + 1) / 2) + 1
        ) * g(d)
    return result


def main():
    print(g(5 * 10 ** 8))


if __name__ == "__main__":
    main()
