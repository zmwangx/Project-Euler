#!/usr/bin/env python3

import math


products = []


def calculate_period():
    global products
    product = 1
    products.append(product)
    for i in range(10_000):
        for j in (1, 3, 7, 9):
            product *= 10 * i + j
            product %= 100_000
            products.append(product)


def calculate_f(n):
    modulus = 100_000
    v2_max = int(math.log2(n))
    v5_max = int(math.log(n) / math.log(5))
    factorial_v2 = sum(n // (2 ** k) for k in range(1, v2_max + 1))
    factorial_v5 = sum(n // (5 ** k) for k in range(1, v5_max + 1))
    factorial_v2_excess = factorial_v2 - factorial_v5
    result = pow(2, factorial_v2_excess, modulus)
    for v2 in range(v2_max + 1):
        for v5 in range(v5_max + 1):
            multiplier = (2 ** v2) * (5 ** v5)
            if multiplier > n:
                break
            cutoff = n // multiplier
            n_periods, tail = divmod(cutoff, modulus)
            tail_last_digit = tail % 10
            tail_index = 4 * (tail // 10)
            if tail_last_digit >= 9:
                tail_index += 4
            elif tail_last_digit >= 7:
                tail_index += 3
            elif tail_last_digit >= 3:
                tail_index += 2
            elif tail_last_digit >= 1:
                tail_index += 1
            result *= pow(products[-1], n_periods, modulus) * products[tail_index]
            result %= modulus
    return result


def main():
    calculate_period()
    print("{:05d}".format(calculate_f(1_000_000_000_000)))


if __name__ == "__main__":
    main()
