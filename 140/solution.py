#!/usr/bin/env python3

import itertools


# Generate a solution group from the fundamental solution (x0, y0).
#
# (x + y\sqrt{5})(9 + 4\sqrt{5}) = (9x + 20y) + (4x + 9y)\sqrt{5}.
def solution_group(x0, y0):
    x = x0
    y = y0
    while True:
        yield (x, y)
        xx = 9 * x + 20 * y
        yy = 4 * x + 9 * y
        x = xx
        y = yy


def head(it, n):
    return list(itertools.islice(it, n))


def main():
    solutions = sorted(
        itertools.chain(
            *[
                head(solution_group(x0, y0), 60)
                for x0, y0 in [(7, 1), (8, 2), (13, 5), (17, 7), (32, 14), (43, 19)]
            ]
        )
    )
    golden_nuggets = [(x - 7) // 5 for x, _ in solutions if x > 7 and (x - 7) % 5 == 0][
        :30
    ]
    for i, g in enumerate(golden_nuggets):
        print(f"#{i+1}: {g}")
    print(f"sum: {sum(golden_nuggets)}")


if __name__ == "__main__":
    main()
