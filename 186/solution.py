#!/usr/bin/env python3

import collections


def phone_number_generator():
    q = collections.deque()
    for k in range(1, 56):
        n = (100003 - 200003 * k + 300007 * (k ** 3)) % 1000000
        q.append(n)
        yield n
    while True:
        n = (q[0] + q[31]) % 1000000
        q.popleft()
        q.append(n)
        yield n


def main():
    g = phone_number_generator()
    cliques = collections.defaultdict(set)
    call = 0
    failed = 0
    while True:
        size = len(cliques[524287])
        if size >= 990000:
            print(call - failed)
            break

        call += 1
        if call % 100_000 == 0:
            print(f"progress: {call:,} {size}")

        from_ = next(g)
        to_ = next(g)
        if from_ == to_:
            failed += 1
            continue
        c1 = cliques[from_]
        if to_ in c1:
            continue
        c2 = cliques[to_]
        if not c1:
            c1.add(from_)
        if not c2:
            c2.add(to_)
        # Merge the smaller clique into the larger clique,
        # updating all references of the smaller clique.
        if len(c1) < len(c2):
            c1, c2 = c2, c1
        c1 |= c2
        for member in c2:
            cliques[member] = c1


if __name__ == "__main__":
    main()
    ...
