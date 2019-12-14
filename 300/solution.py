#!/usr/bin/env python3

import decimal
import functools
import itertools


N = 15


def visualize_folding(f):
    minx = min(x for x, _ in f)
    maxx = max(x for x, _ in f)
    miny = min(y for _, y in f)
    maxy = max(y for _, y in f)
    mm = {(x, y): i for i, (x, y) in enumerate(f)}
    for x in range(minx, maxx + 1):
        for y in range(miny, maxy + 1):
            print(" " if (x, y) not in mm else mm[(x, y)] % 10, end="")
        print()
    print()


def adjacency(f):
    length = len(f)
    adj = []
    for i in range(length - 2):
        x1, y1 = f[i]
        for j in range(i + 2, length):
            x2, y2 = f[j]
            if abs(x1 - x2) + abs(y1 - y2) == 1:
                adj.append((i, j))
    return tuple(adj)


def generate_foldings(length):
    foldings = []

    def dfs(l, chain, occupied):
        if l == length:
            foldings.append(tuple(chain))
            return
        x, y = chain[-1]
        if x == 0 and y == l - 1:
            # We've been going straight in the x-direction; limit the
            # direction of the first turn (equivalent under reflection).
            delta = ((0, 1), (1, 0))
        else:
            delta = ((0, 1), (0, -1), (1, 0), (-1, 0))
        l += 1
        for dx, dy in delta:
            p = (x + dx, y + dy)
            if p in occupied:
                continue
            chain.append(p)
            occupied.add(p)
            dfs(l, chain, occupied)
            chain.pop()
            occupied.remove(p)

    chain = [(0, 0), (0, 1)]
    occupied = set(chain)
    dfs(2, chain, occupied)

    # Note: one can further deduplicate here by reversing the indices.
    adjacency_configs = set(adjacency(f) for f in foldings)
    return sorted(adjacency_configs, key=len, reverse=True)


def calculate_avg_contacts(length, adjcency_configs):
    total = 0
    for chain in itertools.product(*[(0, 1)] * length):
        # Check whether we've already counted the reverse sequence.
        n = functools.reduce(lambda x, bit: 2 * x + bit, chain, 0)
        n_rev = functools.reduce(lambda x, bit: 2 * x + bit, reversed(chain), 0)
        if n > n_rev:
            continue
        free_contacts = sum(chain[i] * chain[i + 1] for i in range(length - 1))
        # Note: one can further optimize here by breaking early when the
        # theoretical maximum is reached.
        total += (
            free_contacts
            + max(sum(chain[i] * chain[j] for i, j in adj) for adj in adjcency_configs)
        ) * (1 if n == n_rev else 2)
    chain_count = 2 ** length
    decimal.getcontext().prec = length
    prob = decimal.Decimal(total) / decimal.Decimal(chain_count)
    print(f"{total}/{chain_count} = {prob}")


def main():
    adjacency_configs = generate_foldings(N)
    print(f"found {len(adjacency_configs)} adjacency configs")
    calculate_avg_contacts(N, adjacency_configs)


if __name__ == "__main__":
    main()
