#!/usr/bin/env python3

import collections
import math

import primesieve


N = 2 ** 50


def main():
    # We should not count N itself per problem requirement, so might as
    # well subtract 1 since otherwise all calculations only involve N-1.
    n = N - 1
    primes = primesieve.primes(math.sqrt(n))
    squares = [p * p for p in primes]
    n_squares = len(squares)
    q = collections.deque()
    # (next_index, current_length, current_product)
    #
    # next_index is the index of the next acceptable square factor,
    # current_length is the current number of square factors already in,
    # current_product is the product of all current square factors.
    q.append((0, 0, 1))
    count = 0
    while q:
        next_index, current_length, current_product = q.popleft()
        quotient = n // current_product
        # Inclusion-exclusion principle
        count += pow(-1, current_length) * quotient
        for i in range(next_index, n_squares):
            s = squares[i]
            if s > quotient:
                break
            q.append((i + 1, current_length + 1, current_product * s))
    print(count)

    ## Verification: the brute force method.
    # count = 0
    # for i in range(1, N):
    #     for s in squares:
    #         if i % s == 0:
    #             break
    #     else:
    #         count += 1
    # print(count)


if __name__ == "__main__":
    main()
