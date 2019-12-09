#!/usr/bin/env python3

import math


def sin_deg(x):
    return math.sin(x * math.pi / 180)


def main():
    count = 0
    for b in range(1, 91):
        print(f"progress: {b}\u00B0")
        sine_ratio_plus = [sin_deg(a) / sin_deg(a + b) for a in range(180 - b)]
        sine_ratio_minus = [sin_deg(a) / sin_deg(b - a) for a in range(b)]
        nonsimilars = set()
        for a1 in range(1, 180 - b):
            for a2 in range(1, b):
                for a3 in range(1, 180 - b):
                    for a4 in range(1, a2 + 1):
                        if (
                            abs(
                                sine_ratio_plus[a1]
                                * sine_ratio_minus[a2]
                                * sine_ratio_plus[a3]
                                * sine_ratio_minus[a4]
                                - 1
                            )
                            < 1e-9
                        ):
                            angles = (
                                a1,
                                180 - b - a1,
                                a2,
                                b - a2,
                                a3,
                                180 - b - a3,
                                a4,
                                b - a4,
                            )
                            for rotation in (0, 2, 4, 6):
                                rotated = angles[rotation:] + angles[:rotation]
                                if (
                                    tuple(rotated) in nonsimilars
                                    or tuple(reversed(rotated)) in nonsimilars
                                ):
                                    break
                            else:
                                nonsimilars.add(angles)
                                count += 1
    print(count)


if __name__ == "__main__":
    main()
