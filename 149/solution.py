#!/usr/bin/env python3


def generate_example_matrix():
    return [[-2, 5, 3, 2], [9, -6, 5, 1], [3, 2, 7, 3], [-1, 8, -4, 8]]


def generate_prng_matrix(n):
    s = []
    for k in range(1, 56):
        s.append((100003 - 200003 * k + 300007 * (k ** 3)) % 1000000 - 500000)
    for k in range(56, n * n + 1):
        s.append((s[k - 25] + s[k - 56] + 1000000) % 1000000 - 500000)
    return [s[i * n : (i + 1) * n] for i in range(n)]


# Returns 0 if best nonempty sum is negative.
def max_subarray(arr):
    max_sum = 0
    current_sum = 0
    for el in arr:
        current_sum = max(0, current_sum + el)
        max_sum = max(max_sum, current_sum)
    return max_sum


# Expects a square matrix. Returns 0 if best nonempty sum is negative.
def matrix_max_adjacents(matrix):
    n = len(matrix)
    max_sum = 0
    # Rows
    for row in matrix:
        max_sum = max(max_sum, max_subarray(row))
    # Columns
    for j in range(n):
        max_sum = max(max_sum, max_subarray(row[j] for row in matrix))
    # Diagonals
    for k in range(-n + 1, n):
        # i - j = k
        max_sum = max(
            max_sum,
            max_subarray(matrix[i][j] for i in range(n) if 0 <= (j := i - k) < n),
        )
    for k in range(0, 2 * n - 1):
        # Anti-diagonals
        # i + j = k
        max_sum = max(
            max_sum,
            max_subarray(matrix[i][j] for i in range(n) if 0 <= (j := k - i) < n),
        )
    return max_sum


def main():
    # print(matrix_max_adjacents(generate_example_matrix()))
    print(matrix_max_adjacents(generate_prng_matrix(2000)))


if __name__ == "__main__":
    main()
