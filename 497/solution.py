#!/usr/bin/env python3

N = 10 ** 4
MOD = 10 ** 9


def walk_expectation(k, x, y, x_before_y):
    if x_before_y:
        return (y + x - 2) * (y - x)
    else:
        return (2 * k - x - y) * (x - y)


def total_expectation(k, a, b, c, coeffs):
    return (
        coeffs[0] * walk_expectation(k, a, b, True)
        + coeffs[1] * walk_expectation(k, b, c, True)
        + coeffs[2] * walk_expectation(k, a, c, True)
        + coeffs[3] * walk_expectation(k, b, a, False)
        + coeffs[4] * walk_expectation(k, c, b, False)
        + coeffs[5] * walk_expectation(k, c, a, False)
    )


def main():
    total = 0
    n, k, a, b, c = 1, 10, 3, 6, 9
    coeffs = [0, 0, 1, 1, 0, 0]
    while n <= N:
        # if n == 2:
        #     assert total_expectation(5, 1, 3, 5, coeffs) == 60
        # if n == 3:
        #     assert total_expectation(20, 4, 9, 17, coeffs) == 2358
        total += total_expectation(k, a, b, c, coeffs)
        total %= MOD
        n += 1
        k = (k * 10) % MOD
        a = (a * 3) % MOD
        b = (b * 6) % MOD
        c = (c * 9) % MOD
        coeffs = [
            (coeffs[2] + coeffs[3] - 1) % MOD,
            (coeffs[4] + coeffs[2]) % MOD,
            (coeffs[0] + coeffs[1] + 1) % MOD,
            (coeffs[5] + coeffs[0] + 2) % MOD,
            (coeffs[1] + coeffs[5] + 1) % MOD,
            (coeffs[3] + coeffs[4] - 1) % MOD,
        ]
    print(total)


if __name__ == "__main__":
    main()
