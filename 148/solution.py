#!/usr/bin/env python3


import functools
import math
import operator


def count_nondivisible_by_7(rows):
    row = 1
    buf = [1] * math.ceil(math.log(rows) / math.log(7))
    count = 0
    while row <= rows:
        if row % 1E7 == 0:
            print(f'progress: row #{row}')
        count += functools.reduce(operator.mul, buf, 1)
        buf[0] += 1
        i = 0
        while buf[i] > 7:
            buf[i] -= 7
            i += 1
            buf[i] += 1
        row += 1
    return count


def main():
    print(count_nondivisible_by_7(1E9))


if __name__ == "__main__":
    main()
