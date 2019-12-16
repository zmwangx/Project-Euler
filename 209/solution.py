#!/usr/bin/env python3

import functools


@functools.lru_cache(maxsize=None)
def C(k):
    if k == 1:
        return 1
    if k == 2:
        return 3
    return C(k - 1) + C(k - 2)


def main():
    neighbor = []
    for i in range(64):
        a, b, c, d, e, f = [int(d) for d in f"{i:06b}"]
        g = a ^ (b & c)
        j = (b << 5) + (c << 4) + (d << 3) + (e << 2) + (f << 1) + g
        neighbor.append(j)
    # 0 -> 0 is fixed.
    seen = set([0])
    count = 1
    for i in range(1, 64):
        if i in seen:
            continue
        chain = [i]
        seen.add(i)
        while (j := neighbor[i]) not in seen:
            chain.append(j)
            seen.add(j)
            i = j
        chain_configs = C(len(chain))
        print(chain, chain_configs)
        count *= chain_configs
    print(count)


if __name__ == "__main__":
    main()
