#!/usr/bin/env python3

# This is an explository script that doesn't scale.

N = 100000


def main():
    used = [set([1]) for _ in range(N * 3)]
    maxlen = 0
    for x in range(2, N + 1):
        used[x - 1].clear()
        choices = sorted(set(range(1, x)) - used[x])
        for y in choices:
            z = x
            r = y
            a = [y]
            while (r := r * r % z) > 1:
                if r in used[z + 1]:
                    break
                else:
                    used[z + 1].add(r)
                a.append(r)
                z += 1
            if z - x + 2 > maxlen:
                maxlen = z - x + 2
                print((x, y), maxlen)


if __name__ == "__main__":
    main()
