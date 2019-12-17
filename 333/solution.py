#!/usr/bin/env python3

import collections

import primesieve


LIMIT = 1000000

pow2 = [2 ** i for i in range(30)]
pow3 = [3 ** i for i in range(20)]


def main():
    count = [0] * LIMIT
    q = collections.deque()
    for i in range(1, len(pow2)):
        if pow2[i] > LIMIT:
            break
        q.append(((i, 0), pow2[i]))
    while q:
        (e2, e3), s = q.popleft()
        final_e3 = e3 + 1
        while (ss := s + pow3[final_e3]) < LIMIT:
            count[ss] += 1
            final_e3 += 1
        for next_e2 in range(1, e2):
            next_e3 = e3 + 1
            while (ss := s + pow2[next_e2] * pow3[next_e3]) < LIMIT:
                q.append(((next_e2, next_e3), ss))
                next_e3 += 1
    print(5 + sum(p for p in primesieve.primes(LIMIT - 1) if count[p] == 1))


if __name__ == "__main__":
    main()
