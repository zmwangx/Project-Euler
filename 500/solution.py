#!/usr/bin/env python3

import primesieve


N = 500500
MODULUS = 500500507


def main():
    primes = primesieve.n_primes(N)
    n = 0
    prod = 1
    i = 0
    while primes[i] <= 2:
        n += 5
        prod *= pow(primes[i], 31, MODULUS)
        prod %= MODULUS
        i += 1
    while primes[i] <= 7:
        n += 4
        prod *= pow(primes[i], 15, MODULUS)
        prod %= MODULUS
        i += 1
    while primes[i] <= 47:
        n += 3
        prod *= pow(primes[i], 7, MODULUS)
        prod %= MODULUS
        i += 1
    while primes[i] <= 2713:
        n += 2
        prod *= pow(primes[i], 3, MODULUS)
        prod %= MODULUS
        i += 1
    while n < N:
        n += 1
        prod *= primes[i]
        prod %= MODULUS
        i += 1
    print(prod)


if __name__ == "__main__":
    main()
