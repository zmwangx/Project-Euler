#!/usr/bin/env python3

N = 10 ** 16
MOD = 1000000007


def main():
    total = 0
    k = 0
    while True:
        k += 1
        kk = k * (k - 1) // 2
        mmax = (N - kk) // k
        if mmax <= 0:
            break
        total += mmax * (N + 1) - k * mmax * (mmax + k) // 2
    print(total, total % MOD)


if __name__ == "__main__":
    main()
