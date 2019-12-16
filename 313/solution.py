#!/usr/bin/env python3

import functools
import heapq
import sys

import primesieve


# Calculate S(m, n) using A* pathfinding algorithm.
#
# Each state is encoded as (red_coords, empty_coords). The initial state
# is ((0,0), (m-1,n-1)), the target state is one of ((m-1,n-1),
# (m-2,n-1)) and ((m-1,n-1), (m-1,n-2)), and neighbors are
#
#   ((x,y), (u,v)) <-> ((x,y), (u+du,v+dv)) if (x,y)!=(u+du,v+dv),
#   ((x,y), (u,v)) <-> ((u,v), (x,y)) if (x,y)-(u,v)=(du,dv),
#
# where (du,dv) is a direction vector.
@functools.lru_cache(maxsize=None)
def calc_S(m, n):
    if m < n:
        return calc_S(n, m)

    def heuristic(state):
        (x, y), (u, v) = state
        # At least we need to move the empty block from (u,v) to (x,y),
        # and move the red counter from (x,y) to (m-1,n-1), ignoring all
        # other maneuvers.
        return max(abs(u - x) + abs(v - y) + abs((m - 1) - x) + abs((n - 1) - y) - 1, 0)

    directions = ((1, 0), (0, 1), (-1, 0), (0, -1))
    initial_state = ((0, 0), (m - 1, n - 1))
    pqueue = []
    heapq.heappush(pqueue, (heuristic(initial_state), initial_state))
    gscore = {initial_state: 0}
    while pqueue:
        current_fscore, current_state = heapq.heappop(pqueue)
        (x, y), (u, v) = current_state
        if (x, y) == (m - 1, n - 1):
            return current_fscore
        for du, dv in directions:
            nu = u + du
            nv = v + dv
            if (nu, nv) == (x, y):
                nx, ny = u, v
            else:
                nx, ny = x, y
            neighbor_state = (nx, ny), (nu, nv)
            new_gscore = gscore[current_state] + 1
            old_gscore = gscore.get(neighbor_state)
            if old_gscore is None or new_gscore < old_gscore:
                gscore[neighbor_state] = new_gscore
                new_fscore = new_gscore + heuristic(neighbor_state)
                heapq.heappush(pqueue, (new_fscore, neighbor_state))


def explore_S():
    limit = 15
    print("\t".join(["S", *[str(i) for i in range(1, limit + 1)]]))
    for m in range(1, limit + 1):
        print(m, end="\t")
        for n in range(1, limit + 1):
            print(calc_S(m, n), end="\t")
            sys.stdout.flush()
        print()
    print()
    print("\t".join(["\u0394S", *[str(i) for i in range(1, limit + 1)]]))
    for m in range(1, limit + 1):
        print(m, end="\t")
        for n in range(1, limit + 1):
            horizontal_diff = "-" if n == 1 else calc_S(m, n) - calc_S(m, n - 1)
            vertical_diff = "-" if m == 1 else calc_S(m, n) - calc_S(m - 1, n)
            print(f"{horizontal_diff},{vertical_diff}", end="\t")
        print()


def search(bound):
    primes = primesieve.primes(5, bound)
    count = 2
    for p in primes:
        count += (p * p - 1) // 12
    return count


def main():
    # explore_S()
    print(search(10 ** 6))


if __name__ == "__main__":
    main()
