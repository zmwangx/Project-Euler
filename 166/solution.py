#!/usr/bin/env python3


def main():
    total_count = 0
    for s in range(19):
        count = 0
        for m11 in range(10):
            for m12 in range(min(10, s + 1 - m11)):
                for m21 in range(min(10, s + 1 - m11)):
                    for m22 in range(min(10, s + 1 - max(m11, m12, m21))):
                        for m10 in range(min(10, s + 1 - m11 - m12)):
                            m13 = s - m10 - m11 - m12
                            if m13 > 9:
                                continue
                            for m20 in range(min(10, s + 1 - m21 - m22, s + 1 - m10)):
                                m23 = s - m20 - m21 - m22
                                if m23 > 9:
                                    continue
                                for m00 in range(
                                    min(10, s + 1 - m11 - m22, s + 1 - m10 - m20)
                                ):
                                    m30 = s - m00 - m10 - m20
                                    if m30 > 9:
                                        continue
                                    m33 = s - m00 - m11 - m22
                                    if m33 > 9:
                                        continue
                                    for m01 in range(
                                        min(10, s + 1 - m11 - m21, s + 1 - m00)
                                    ):
                                        m31 = s - m01 - m11 - m21
                                        if m31 > 9:
                                            continue
                                        m32 = s - m30 - m31 - m33
                                        if not (0 <= m32 <= 9):
                                            continue
                                        m02 = s - m12 - m22 - m32
                                        if not (0 <= m02 <= 9):
                                            continue
                                        m03 = s - m00 - m01 - m02
                                        if not (0 <= m03 <= 9):
                                            continue
                                        if m03 + m12 + m21 + m30 != s:
                                            continue
                                        count += 1
        print(f"sum {s}: {count}")
        total_count += count
    # By symmetry, except 18 = 36 - 18.
    total_count += total_count - count
    print(total_count)


if __name__ == "__main__":
    main()
