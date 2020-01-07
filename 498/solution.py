#!/usr/bin/env python3

p = 999999937
n1 = 10000
n0 = 630000
m1 = 1000
m0 = 63000
d = 10000
factmod = []
factinvmod = []


def calculate_factorial_mods():
    r = 1
    factmod.append(1)
    factinvmod.append(1)
    for n in range(1, max(n0, n1) + 1):
        r *= n
        r %= p
        factmod.append(r)
        factinvmod.append(pow(r, -1, p))


def binom_mod(a, b):
    if b > a:
        return 0
    return factmod[a] * factinvmod[b] * factinvmod[a - b] % p


def main():
    calculate_factorial_mods()
    result = (
        ((-1) ** m1)
        * binom_mod(n0, d)
        * binom_mod(n1, m1)
        * sum(((-1) ** k) * binom_mod(n0 - d, k) for k in range(m0 - d))
        % p
    )
    print(result, (-result) % p)


if __name__ == "__main__":
    main()
