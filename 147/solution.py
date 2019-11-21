#!/usr/bin/env python3


def count_diagonal_rectangles(m, n):
    xbound = 2 * m
    ybound = 2 * n
    count = 0
    for x0 in range(0, xbound):
        for y0 in range(x0 % 2, ybound, 2):
            for a in range(1, xbound):
                x1 = x0 + a
                y1 = y0 - a
                if x1 > xbound or y1 < 0:
                    break
                for b in range(1, ybound):
                    x2 = x0 + b
                    y2 = y0 + b
                    if x2 > xbound or y2 > ybound:
                        break
                    x3 = x1 + b
                    y3 = y1 + b
                    if x3 > xbound or y3 > ybound:
                        break
                    count += 1
    return count


def count_rectangles(m, n):
    if m < n:
        m, n = n, m
    if (count := count_rectangles.cache.get((m, n))) is not None:
        return count
    upright_count = m * (m + 1) * n * (n + 1) // 4
    count = upright_count + count_diagonal_rectangles(m, n)
    count_rectangles.cache[(m, n)] = count
    return count


count_rectangles.cache = dict()


def count_rectangles_accumulated(mmax, nmax):
    total_count = 0
    for m in range(1, mmax + 1):
        for n in range(1, nmax + 1):
            count = count_rectangles(m, n)
            print(f"{m}x{n}: {count}")
            total_count += count
    return total_count


def main():
    total_count = count_rectangles_accumulated(47, 43)
    print(f"total count: {total_count}")


if __name__ == "__main__":
    main()
