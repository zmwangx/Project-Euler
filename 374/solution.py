#!/usr/bin/env python3

# Exploratory implementation to validate the greedy strategy.


def div(n):
    if n == 1:
        return 1
    k = 1
    while (k + 1) * (k + 4) // 2 <= n:
        k += 1
    base = k * (k + 3) // 2
    parts = list(range(2, k + 2))
    remaining = n - base
    for i in range(k - 1, -1, -1):
        if not remaining:
            break
        parts[i] += 1
        remaining -= 1
    if remaining:
        assert remaining == 1
        parts[-1] += 1
    result = k
    for p in parts:
        result *= p
    # print(n, parts, result)
    return result


def main():
    print(sum(div(n) for n in range(1, 101)))


if __name__ == "__main__":
    main()
