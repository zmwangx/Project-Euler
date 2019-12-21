#!/usr/bin/env python3

import sympy


A = 25
B = 75
C = 1984
MOD = 10 ** 8

# Label the nodes 0-6:
#
#  0 ----- 1
#  | \   / |
#  |  \ /  |
#  |   4   |
#  |   |   |
#  |   6   |
#  |   |   |
#  |   5   |
#  |  / \  |
#  | /   \ |
#  3 ----- 2
#
# And represent the graphs using adjacency lists.
A_CONNECTIONS = {
    0: [1, 3, 4],
    1: [0, 2, 4],
    2: [1, 3, 5],
    3: [0, 2, 5],
    4: [0, 1, 6],
    5: [2, 3, 6],
    6: [4, 5],
}
B_CONNECTIONS = {
    0: [1, 3, 4],
    1: [0, 2, 4],
    2: [1, 5],
    3: [0, 5],
    4: [0, 1, 6],
    5: [2, 3, 6],
    6: [4, 5],
}


def generate_configs(connections, filled, next_color):
    index = len(filled)
    if index == 7:
        return [filled]
    configs = []
    colors = set(range(next_color + 1)) - set(
        filled[i] for i in connections[index] if i < index
    )
    for color in sorted(colors):
        if color == next_color:
            configs.extend(
                generate_configs(connections, (*filled, color), next_color + 1)
            )
        else:
            configs.extend(generate_configs(connections, (*filled, color), next_color))
    return configs


def count_config(c, colors, fixed=0):
    result = 1
    for color in sorted(set(colors))[fixed:]:
        result *= c - color
    return result


def main():
    A_COUNT = (
        sum(
            count_config(C, config, fixed=2)
            for config in generate_configs(A_CONNECTIONS, (), 0)
        )
        % MOD
    )
    B_COUNT = (
        sum(
            count_config(C, config, fixed=2)
            for config in generate_configs(B_CONNECTIONS, (), 0)
        )
        % MOD
    )
    print(
        sympy.binomial(A + B, A)
        * pow(A_COUNT, A, MOD)
        * pow(B_COUNT, B, MOD)
        * C
        * (C - 1)
        % MOD
    )


if __name__ == "__main__":
    main()
