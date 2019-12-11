#!/usr/bin/env python3

from miller_rabin import miller_rabin


BOUND = 10 ** 12
MODULUS = 2 ** 32


def main():
    hammings = []
    p2 = 1
    while p2 <= BOUND:
        p3 = 1
        while p2 * p3 <= BOUND:
            p23 = p2 * p3
            p5 = 1
            while p23 * p5 <= BOUND:
                n = p23 * p5
                hammings.append(n)
                p5 *= 5
            p3 *= 3
        p2 *= 2
    hammings.sort()
    hamming_primes = []
    for h in hammings:
        p = h + 1
        if p not in (2, 3, 5) and miller_rabin(p):
            hamming_primes.append(p)
    hamming_prime_products = [1]
    for p in hamming_primes:
        new_products = []
        for n in hamming_prime_products:
            prod = n * p
            if prod > BOUND:
                break
            new_products.append(prod)
        hamming_prime_products.extend(new_products)
        hamming_prime_products.sort()
    total = 0
    for n1 in hammings:
        for n2 in hamming_prime_products:
            prod = n1 * n2
            if prod > BOUND:
                break
            total = (total + prod) % MODULUS
    print(total)


if __name__ == "__main__":
    main()
