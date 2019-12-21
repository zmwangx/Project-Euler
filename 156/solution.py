#!/usr/bin/env python3


def f(n, d):
    m = n
    suffix = 0
    p10 = 1
    count = 0
    while m > 0:
        dk = m % 10
        m //= 10
        count += p10 * m
        if dk > d:
            count += p10
        elif dk == d:
            count += suffix + 1
        suffix += p10 * dk
        p10 *= 10
    return count


# Search in [m * s, (m+1) * s) where s is a power of 10.
def search(d, m, s):
    if s == 1:
        if f(m, d) == m:
            return [m]
        else:
            return []
    min_n = m * s
    max_n = min_n + s - 1
    min_f = f(min_n, d)
    if min_f > max_n:
        return []
    max_f = f(max_n, d)
    if max_f < min_n:
        return []
    m *= 10
    s //= 10
    results = []
    for dd in range(10):
        results.extend(search(d, m + dd, s))
    return results


def s(d):
    results = []
    for k in range(0, 12):
        s = 10 ** k
        for m in range(1, 10):
            results.extend(search(d, m, s))
    # print(d, results)
    return sum(results)


def main():
    print(sum(s(d) for d in range(1, 10)))


if __name__ == "__main__":
    main()
