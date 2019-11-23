#!/usr/bin/env python3

import itertools


def generate_rows(width):
    rows = []
    for n2 in range(width // 2 + 1):
        if (width - n2 * 2) % 3 != 0:
            continue
        n3 = (width - n2 * 2) // 3
        for combo in itertools.combinations(range(n2 + n3), n2):
            pos = 0
            row = set()
            for i in range(n2 + n3):
                pos += 2 if i in combo else 3
                row.add(pos)
            rows.append(row)
    return rows


def generate_compatibility_matrix(width, rows):
    nrows = len(rows)
    compat = [[True for _ in range(nrows)] for _ in range(nrows)]
    for pos in range(2, width - 1):
        include_indices = [i for i, row in enumerate(rows) if pos in row]
        for i in include_indices:
            for j in include_indices:
                compat[i][j] = False
    return compat


def calculate_W(width, height):
    rows = generate_rows(width)
    compat = generate_compatibility_matrix(width, rows)
    nrows = len(rows)
    counts = [[1] * nrows]
    for i in range(1, height):
        print(f"progress: calculating height {i}")
        counts.append([0] * nrows)
        for j in range(nrows):
            counts[i][j] = sum(counts[i - 1][k] for k in range(nrows) if compat[j][k])
    return sum(counts[height - 1])


def main():
    # print(calculate_W(9, 3))
    print(calculate_W(32, 10))


if __name__ == "__main__":
    main()
