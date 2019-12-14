#!/usr/bin/env python3

import math
import warnings


def main():
    R = 1_000_000_000
    bound = R * R // 32 - 1
    # a <= sqrt(bound / 2), 1 + 3 + ... + (2a-1)
    a = int(math.sqrt(bound / 2))
    assert a * a <= bound / 2
    assert (a+1) * (a+1) > bound / 2
    count = a * a
    a += 1
    while (a2 := a * a) <= bound:
        if a % 1_000_000 == 0:
            print(f"progress: {a}/{int(math.sqrt(bound))}")
        b2_bound = int(math.sqrt(bound - a2))
        while b2_bound * b2_bound + a2 > bound:
            warnings.warn(f"{b2_bound}**2 + {a}**2>{bound}")
            b2_bound -= 1
        while ((b2_bound + 1) ** 2) + a2 <= bound:
            warnings.warn(f"{b2_bound}**2 +{a}**2<={bound}")
            b2_bound += 1
        count += 2 * b2_bound + 1
        a += 1
    count *= 4
    count += R * R * 3 // 2 + R // 4 - 2
    print(count)


if __name__ == "__main__":
    main()
