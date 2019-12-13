#!/usr/bin/env python3

import functools
import math


A = "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
B = "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"
BASE_LENGTH = len(A)


@functools.lru_cache(maxsize=None)
def fibo(n):
    if n <= 2:
        return 1
    else:
        return fibo(n - 1) + fibo(n - 2)


# DD(k, l) returns the l-th digit of the k-th term of FAB. l and k are
# both 1-indexed.
def DD(k, l):
    if k == 1:
        return int(A[l - 1])
    if k == 2:
        return int(B[l - 1])
    splitpos = fibo(k - 2) * BASE_LENGTH
    if l <= splitpos:
        return DD(k - 2, l)
    else:
        return DD(k - 1, l - splitpos)


def D(n):
    m = math.ceil(n / BASE_LENGTH)
    k = 1
    while fibo(k) < m:
        k += 1
    return DD(k, n)


def main():
    print(sum((10 ** n) * D((127 + 19 * n) * (7 ** n)) for n in range(18)))


if __name__ == "__main__":
    main()
