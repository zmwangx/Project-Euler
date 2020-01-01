#!/usr/bin/env python3

import miller_rabin


LIMIT = 5 * 10 ** 15


def main():
    n = 1
    count = 0
    while (p := n * n + (n + 1) * (n + 1)) < LIMIT:
        if n % 1_000_000 == 0:
            print(f"progress: {n:,}")
        if miller_rabin.miller_rabin(p):
            count += 1
        n += 1
    print(count)


if __name__ == "__main__":
    main()
