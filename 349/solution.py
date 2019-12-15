#!/usr/bin/env python3


def display_pattern():
    directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
    blacks = set()
    pos = (0, 0)
    direction = 0
    for step in range(10 ** 6):
        if pos in blacks:
            blacks.remove(pos)
            direction = (direction + 1) % 4
        else:
            blacks.add(pos)
            direction = (direction - 1) % 4
        dx, dy = directions[direction]
        x, y = pos
        pos = (x + dx, y + dy)
    print(f"#black: {len(blacks)}")
    minx = min(x for x, _ in blacks)
    maxx = max(x for x, _ in blacks)
    miny = min(y for _, y in blacks)
    maxy = max(y for _, y in blacks)
    for i in range(max(minx, -100), min(maxx, 101)):
        print(f"{i:4d}    ", end="")
        for j in range(max(miny, -100), min(maxy, 101)):
            print("*" if (i, j) in blacks else " ", end="")
        print()


def find_period():
    directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
    blacks = set()
    pos = (0, 0)
    direction = 0
    black_deltas = []
    step = 0
    pow2 = 1024
    while True:
        if pos in blacks:
            blacks.remove(pos)
            black_deltas.append(-1)
            direction = (direction + 1) % 4
        else:
            blacks.add(pos)
            black_deltas.append(1)
            direction = (direction - 1) % 4
        dx, dy = directions[direction]
        x, y = pos
        pos = (x + dx, y + dy)
        step += 1
        if step == pow2:
            # Try to extract period with Z algorithm.
            # https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/
            # Note that we search the array in reverse in order to
            # eliminate the effect of junk terms in the beginning.
            n, l, r, k = len(black_deltas), 0, 0, 0
            nm1 = n - 1
            z = [0] * n
            for i in range(1, n):
                if i > r:
                    l, r = i, i
                    while (
                        r < n and black_deltas[nm1 - (r - l)] == black_deltas[nm1 - r]
                    ):
                        r += 1
                    z[i] = r - l
                    r -= 1
                else:
                    k = i - l
                    if z[k] < r - i + 1:
                        z[i] = z[k]
                    else:
                        l = i
                        while (
                            r < n
                            and black_deltas[nm1 - (r - l)] == black_deltas[nm1 - r]
                        ):
                            r += 1
                        z[i] = r - l
                        r -= 1
                if z[i] >= 4 * i:  # We see at least 5 periods.
                    return (
                        i,
                        black_deltas[n - z[i] : n - z[i] + i],
                        n - z[i],
                        black_deltas[: n - z[i]],
                    )
            pow2 *= 2


def main():
    # display_pattern()
    period_length, period, junk_length, junk = find_period()
    N = 10 ** 18
    if N <= junk_length:
        print(sum(junk[:N]))
    else:
        junk_total = sum(junk)
        period_total = sum(period)
        q, r = divmod(N - junk_length, period_length)
        print(junk_total + q * period_total + sum(period[:r]))


if __name__ == "__main__":
    main()
