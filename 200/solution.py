#!/usr/bin/env python3

import miller_rabin
import primesieve


def main():
    limit = 1_000_000_000_000
    primes = primesieve.primes(pow(limit, 1 / 2))
    squbes = set()
    for q in primes:
        q3 = pow(q, 3)
        if q3 * 4 > limit:
            break
        for p in primes:
            if p == q:
                continue
            n = p * p * q3
            if n > limit:
                break
            s = str(n)
            if "200" not in s:
                continue
                squbes.add(n)
            length = len(s)
            failed = False
            for i in range(length):
                ss = [ch for ch in s]
                d = s[i]
                if i == 0:
                    replacements = set("123456789")
                elif i == length - 1:
                    replacements = set("1379")
                else:
                    replacements = set("0123456789")
                replacements.discard(d)
                for dd in replacements:
                    ss[i] = dd
                    nn = int("".join(ss))
                    if miller_rabin.miller_rabin(nn):
                        failed = True
                        break
                if failed:
                    break
            if not failed:
                squbes.add(n)

    for i, n in enumerate(sorted(squbes)):
        print(i + 1, n)

if __name__ == "__main__":
    main()
