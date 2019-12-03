#!/usr/bin/env python3

import gmpy2


N = 18


def search():
    possible_capacities = [None, set([gmpy2.mpq(1)])]
    for n in range(2, N + 1):
        n_capacities = set()
        for i in range(1, int(n / 2) + 1):
            for c1 in possible_capacities[i]:
                for c2 in possible_capacities[n - i]:
                    n_capacities.add(c1 + c2)
                    n_capacities.add(1 / (1 / c1 + 1 / c2))
        print(f"{n}: {len(n_capacities)}")
        possible_capacities.append(n_capacities)
    all_possible_capacities = set()
    for n in range(1, N + 1):
        all_possible_capacities |= possible_capacities[n]
    return len(all_possible_capacities)


def main():
    print(search())


if __name__ == "__main__":
    main()
