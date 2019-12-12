#!/usr/bin/env python3

import collections
import functools
import sys

import primesieve
import sympy


sys.setrecursionlimit(50000)
N = 24
MODULUS = 10 ** 9


def method1(n):
    primes = primesieve.primes(n)
    primes_set = set(primes)
    n_primes = len(primes)
    q = collections.deque()
    q.append((0, 0, 1))
    # aggregate_count = 0
    total = 0
    while q:
        min_index, psum, pprod = q.popleft()
        rsum = n - psum
        if rsum in primes_set:
            # aggregate_count += 1
            total = (total + rsum * pprod) % MODULUS
        half_rsum = rsum // 2
        i = min_index
        while i < n_primes and (p := primes[i]) <= half_rsum:
            new_psum = psum
            new_pprod = pprod
            for count in range(1, rsum // p - 1):
                new_psum += p
                new_pprod = (new_pprod * p) % MODULUS
                q.append((i + 1, new_psum, new_pprod))
            if rsum % p == 0:
                # rsum = (rsum // p - 2) * p + 2p, with 2p remaining.
                # aggregate_count += 1
                total = (total + new_pprod * p * p) % MODULUS
            else:
                # rsum = (rsum // p - 2) * p + r, where p < r < 2p.
                new_psum += p
                new_pprod = (new_pprod * p) % MODULUS
                q.append((i + 1, new_psum, new_pprod))
            i += 1
    return total


def method2(n):
    primes = primesieve.primes(n)
    n_primes = len(primes)
    S = [1]
    for k in range(1, n + 1):
        s = 0
        q = collections.deque()
        q.append((0, k, 1, -1))
        while q:
            min_index, rsum, pprod, sign = q.popleft()
            if min_index > 0:
                s = (s + sign * pprod * S[rsum]) % MODULUS
            for i in range(min_index, n_primes):
                p = primes[i]
                if p > rsum:
                    break
                q.append((i + 1, rsum - p, (pprod * p) % MODULUS, -sign))
        S.append(s)
    return S


def method3(n):
    primes = primesieve.primes(n)

    # S[k, i] is the sum of numbers whose prime factor sum is k and
    # whose prime factors are among the primes[0], primes[1], ...,
    # primes[i].
    @functools.lru_cache(maxsize=None)
    def S(k, i):
        if k == 0:
            return 1
        if i < 0:
            return 0
        p = primes[i]
        if k < p:
            return S(k, i - 1)
        else:
            return (S(k, i - 1) + p * S(k - p, i)) % MODULUS

    return [S(k, sympy.primepi(k) - 1) for k in range(n + 1)]


# Non-recursive version of method3; pretty damn unreadable, but way
# faster.
def method3_non_recursive(n):
    primes = primesieve.primes(n)
    SS = [[1]]
    S = [1]
    for k in range(1, n + 1):
        if k % 5_000 == 0:
            print(f"progress: {k}")
        SSk = []
        pi = sympy.primepi(k)
        for i in range(pi):
            p = primes[i]
            SSkmp = SS[k - p]
            SSk.append(
                (
                    (SSk[i - 1] if i > 0 else 0)
                    + p * (SSkmp[i] if i < len(SSkmp) else (SSkmp[-1] if SSkmp else 0))
                )
                % MODULUS
            )
        SS.append(SSk)
        S.append(SSk[pi - 1] if pi >= 1 else 0)
    return S


@functools.lru_cache
def fibo(n):
    if n < 3:
        return 1
    else:
        return fibo(n - 1) + fibo(n - 2)


def main():
    # assert method1(144) == method2(144)[-1] == method3(144)[-1]
    # assert method3(144) == method3_non_recursive(144)
    ns = [fibo(i) for i in range(2, N + 1)]
    S = method3_non_recursive(ns[-1])
    print([S[n] for n in ns])
    print(sum(S[n] for n in ns) % MODULUS)


if __name__ == "__main__":
    main()
