#!/usr/bin/env python3

from gmpy2 import mpz


MAX_LENGTH = 100


def main():
    ten = mpz(10)
    mod_sum = 0
    for l in range(2, MAX_LENGTH + 1):
        m = ten ** l - 1
        # 11111, 22222, ..., 99999
        if l < 5:
            mod_sum += int(m // 9) * 45
        else:
            mod_sum += 99_995
        for d in range(2, 10):
            md = m * d
            for k in range(2, d + 1):
                q, r = divmod(md, 10 * k - 1)
                if r == 0:
                    print(q)
                    mod_sum += int(q % 100_000)
        mod_sum %= 100_000
    print(f"{mod_sum:05d}")


if __name__ == "__main__":
    main()
