#!/usr/bin/env python3


def length_n_count(n):
    return 15 * (16 ** (n - 1)) - 43 * (15 ** (n - 1)) + 41 * (14 ** (n - 1)) - 13 ** n


def length_up_to_n_count(n):
    return sum(length_n_count(i) for i in range(1, n + 1))


def main():
    print(f"{length_up_to_n_count(16):X}")


if __name__ == "__main__":
    main()
