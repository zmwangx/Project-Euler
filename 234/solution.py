#!/usr/bin/env python3

import primesieve


def main():
    primes = primesieve.primes(999983)
    total = 0
    for k in range(len(primes) - 1):
        p = primes[k]
        q = primes[k + 1]
        pq = p * q
        for n in range(p * (p + 1), q * q, p):
            if n != pq:
                total += n
        for n in range(q * (q - 1), p * p, -q):
            if n != pq:
                total += n
    print(total)


if __name__ == "__main__":
    main()
