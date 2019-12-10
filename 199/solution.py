#!/usr/bin/env python3

import math


# We omit pi from all of our area calculations (since we're only
# interested in fractional area in the end).

# Assumption: k1 <= k2 <= k3, steps >= 1
def area_covered(k1, k2, k3, steps):
    k4 = k1 + k2 + k3 + 2 * math.sqrt(k1 * k2 + k2 * k3 + k3 * k1)
    area = 1 / k4 / k4
    if steps == 1:
        return area
    steps -= 1
    if k1 == k2:
        if k2 == k3:
            # k1 = k2 = k3
            return area + 3 * area_covered(k1, k2, k4, steps)
        else:
            # k1 = k2 < k3
            return (
                area
                + area_covered(k1, k2, k4, steps)
                + 2 * area_covered(k1, k3, k4, steps)
            )
    else:
        if k2 == k3:
            # k1 < k2 = k3
            return (
                area
                + 2 * area_covered(k1, k2, k4, steps)
                + area_covered(k2, k3, k4, steps)
            )
        else:
            # k1 < k2 < k3
            return (
                area
                + area_covered(k1, k2, k4, steps)
                + area_covered(k2, k3, k4, steps)
                + area_covered(k3, k1, k4, steps)
            )


def total_area_covered(steps):
    outer_curvature = 3 - 2 * math.sqrt(3)
    return (
        3
        + 3 * area_covered(outer_curvature, 1, 1, steps)
        + area_covered(1, 1, 1, steps)
    )


def fractionalAreaNotCovered(steps):
    outer_radius = 1 / (2 * math.sqrt(3) - 3)
    total_area = outer_radius * outer_radius
    covered_area = total_area_covered(steps)
    return 1 - covered_area / total_area


def main():
    print(f"{fractionalAreaNotCovered(10):.8f}")


if __name__ == "__main__":
    main()
