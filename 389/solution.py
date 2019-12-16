#!/usr/bin/env python3

from gmpy2 import mpq


def calculate_sum_distribution(dice, count_distribution):
    max_count = max(count_distribution)
    assert max_count > 0
    maxsum = dice * max_count
    poly = [1]
    current_maxsum = 0
    sum_distribution = [0] * (maxsum + 1)
    denom = 1
    for i in range(1, max_count + 1):
        new_poly = [0] * (current_maxsum + dice + 1)
        for j1 in range(current_maxsum + 1):
            for j2 in range(1, dice + 1):
                new_poly[j1 + j2] += poly[j1]
        poly = new_poly
        current_maxsum += dice
        count = count_distribution.get(i, 0)
        denom *= dice
        if count:
            for j in range(current_maxsum + 1):
                sum_distribution[j] += mpq(count * poly[j], denom)
    dist = {i: c for i in range(maxsum + 1) if (c := sum_distribution[i]) > 0}
    return dist


def calculate_sum_variance(dice, count_distribution):
    E1 = mpq(dice + 1, 2)  # Mean
    E2 = mpq((dice + 1) * (2 * dice + 1), 6)  # Square mean
    S1 = sum(j * count_distribution[j] for j in count_distribution)
    S2 = sum(j * (j - 1) * count_distribution[j] for j in count_distribution)
    return E2 * S1 + E1 * E1 * (S2 - S1 * S1)


def main():
    T_distribution = {i: mpq(1, 4) for i in range(1, 5)}
    C_distribution = calculate_sum_distribution(6, T_distribution)
    O_distribution = calculate_sum_distribution(8, C_distribution)
    D_distribution = calculate_sum_distribution(12, O_distribution)
    var = float(calculate_sum_variance(20, D_distribution))
    print(f"{var:.4f}")


if __name__ == "__main__":
    main()
