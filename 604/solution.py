#!/usr/bin/env python3

import math


def precompute_totients(limit):
    pp = [0] * (limit + 1)
    tt = [0] * (limit + 1)
    tt[1] = 1
    # Sieve.
    for n in range(2, limit + 1):
        if pp[n] == 0:
            tt[n] = n - 1
            for m in range(2 * n, limit + 1, n):
                pp[m] = n
        else:
            p = pp[n]
            m = n // p
            ppow = p
            while m % p == 0:
                m //= p
                ppow *= p
            if m == 1:
                tt[n] = n * (p - 1) // p
            else:
                tt[n] = tt[ppow] * tt[m]
    return tt


def F(n):
    totient = precompute_totients(3_000_000)
    count = 2
    i = 3
    cumulative_sum = 1
    while True:
        t = totient[i]
        new_sum = cumulative_sum + i * t // 2
        if new_sum <= n:
            count += t
            cumulative_sum = new_sum
            i += 1
        else:
            count += ((n - cumulative_sum) // i) * 2
            cumulative_sum += ((n - cumulative_sum) // i) * i
            break
    remaining = n - cumulative_sum
    for j in range(i // 2, 0, -1):
        if math.gcd(j, i) == 1:
            break
    if i - j <= remaining:
        count += 1
    return count


def main():
    print(F(10 ** 18))


if __name__ == "__main__":
    main()
