#!/usr/bin/env python3


def H(n):
    m, r = divmod(n, 3)
    if r == 0:
        return 3 * m * (m + 1) * (m + 2) * (m - 1) // 8 + m * (m + 1) // 2
    elif r == 1:
        return m * (m + 1) * (m + 2) * (3 * m + 1) // 8
    else:
        return m * (m + 1) * (m + 2) * (3 * m + 5) // 8


def S(N):
    M, r = divmod(N - 2, 3)
    s = (
        3 * M * (M + 1) * (M + 2) * (M + 3) * (3 * M + 2) // 40
        + M * (M + 1) * (M + 2) // 6
    )
    if r == 0:
        return s
    elif r == 1:
        return s + H(N)
    else:
        return s + H(N - 1) + H(N)


def main():
    print(S(12345))


if __name__ == "__main__":
    main()
