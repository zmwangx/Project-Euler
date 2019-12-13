#!/usr/bin/env python3

import collections

import primesieve
import sympy


def calculate_pseudofortunates(N):
    primes = primesieve.primes(int(pow(N, 0.5)))
    n_primes = len(primes)
    admissibles = []
    q = collections.deque()
    q.append((1, 0))
    while q:
        n, i = q.popleft()
        if i < n_primes:
            p = primes[i]
            i += 1
            while (n := n * p) < N:
                admissibles.append(n)
                q.append((n, i))
    admissibles.sort()
    return set(sympy.nextprime(n+1) - n for n in admissibles)


def main():
    print(sum(calculate_pseudofortunates(10 ** 9)))


if __name__ == "__main__":
    main()
