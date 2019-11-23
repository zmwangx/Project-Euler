#!/usr/bin/env python3


def caclulate_count(digits):
    two_digit_prefixes = [(i, j) for i in range(10) for j in range(10) if i + j <= 9]
    # counts[(m, (i, j))] is the number of m-digit numbers (possibly
    # with leading zeros) starting with digits i and j s.t. no three
    # consecutive digits have a sum greater than 9.
    counts = dict()
    for i, j in two_digit_prefixes:
        counts[(3, (i, j))] = 10 - i - j
    for m in range(4, digits + 1):
        for i, j in two_digit_prefixes:
            counts[m, (i, j)] = sum(counts[m - 1, (j, k)] for k in range(10 - i - j))
    return sum(counts[digits, (i, j)] for i, j in two_digit_prefixes if i != 0)


def main():
    print(caclulate_count(20))


if __name__ == "__main__":
    main()
