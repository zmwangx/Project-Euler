#!/usr/bin/env python3

import functools
import operator


factorios = [functools.reduce(operator.mul, range(1, i + 1), 1) for i in range(27)]


def calculate_p(n):
    count = 0
    f = factorios
    for m in range(1, n):
        for a in range(1, 27):
            for b in range(1, a):
                for k in range(m):
                    for l in range(n - m):
                        if (
                            m - k - 1 < 0
                            or b - m + k < 0
                            or n - m - 1 - l < 0
                            or 27 - a - n + m + l < 0
                            or a - b - 1 - k - l < 0
                        ):
                            continue
                        count += (
                            f[b - 1]
                            * f[26 - a]
                            * f[a - b - 1]
                            // f[m - k - 1]
                            // f[b - m + k]
                            // f[n - m - 1 - l]
                            // f[27 - a - n + m + l]
                            // f[k]
                            // f[l]
                            // f[a - b - 1 - k - l]
                        )
    return count


def main():
    max_p = 0
    for i in range(27):
        if (p := calculate_p(i)) > max_p:
            max_p = p
    print(max_p)

if __name__ == "__main__":
    main()
