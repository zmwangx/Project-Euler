#!/usr/bin/env python3

import numpy as np


def generate_transition_matrix(m, n):
    t = np.zeros((m * n, m * n))
    for i in range(m):
        for j in range(n):
            choices = [
                (x, y)
                for x, y in [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)]
                if 0 <= x < m and 0 <= y < n
            ]
            for x, y in choices:
                t[i * n + j][x * n + y] = 1 / len(choices)
    return t


def calculate_empty_expectation(m, n, steps):
    t = generate_transition_matrix(m, n)
    tt = np.linalg.matrix_power(t, steps)
    ss = np.ones((m * n, m * n)) - tt
    return sum(ss[:, j].prod() for j in range(m * n))


def main():
    print("{:.6f}".format(calculate_empty_expectation(30, 30, 50)))


if __name__ == "__main__":
    main()
