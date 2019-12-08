#!/usr/bin/env python3

import functools


@functools.lru_cache(maxsize=None)
def f(l, d, a, b):
    assert a <= d <= b
    if l == 1:
        return 1 if a == b else 0
    if a == b:
        # l > 1.
        return 0
    if b - a + 1 > l:
        return 0
    if b - a + 1 == l:
        return 1 if d in (a, b) else 0
    if d == a:
        return f(l - 1, a + 1, a, b) + f(l - 1, a + 1, a + 1, b)
    elif d == b:
        return f(l - 1, b - 1, a, b) + f(l - 1, b - 1, a, b - 1)
    else:
        return f(l - 1, d + 1, a, b) + f(l - 1, d - 1, a, b)


def main():
    count = 0
    for l in range(41):
        for d in range(1, 10):
            count += f(l, d, 0, 9)
    print(count)


if __name__ == "__main__":
    main()
