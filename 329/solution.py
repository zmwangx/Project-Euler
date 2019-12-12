#!/usr/bin/env python3

import collections
import functools

from gmpy2 import mpq
from miller_rabin import miller_rabin


N = 500
SEQUENCE = "PPPPNNPPPNPPNPN"


@functools.lru_cache(maxsize=None)
def prob(squares, initial_pos):
    rbound = len(squares) - 1
    max_step = len(SEQUENCE) - 1
    q = collections.deque()
    q.append((0, initial_pos, mpq(1)))
    total_prob = mpq(0)
    while q:
        step, pos, p = q.popleft()
        if (squares[pos] and SEQUENCE[step] == "P") or (
            not squares[pos] and SEQUENCE[step] == "N"
        ):
            p *= mpq(2, 3)
        else:
            p *= mpq(1, 3)
        if step == max_step:
            total_prob += p
            continue
        step += 1
        if pos == 0:
            q.append((step, 1, p))
        elif pos == rbound:
            q.append((step, pos - 1, p))
        else:
            p *= mpq(1, 2)
            q.append((step, pos + 1, p))
            q.append((step, pos - 1, p))
    return total_prob


def main():
    squares = [miller_rabin(i) for i in range(1, N + 1)]
    extent = len(SEQUENCE) - 1
    total_prob = mpq(0)
    for i in range(N):
        if i % 100 == 0:
            print(f"progress: {i}")
        left = max(0, i - extent)
        right = min(N, i + extent + 1)
        total_prob += prob(tuple(squares[left:right]), i - left) / N
    print(total_prob)


if __name__ == "__main__":
    main()
