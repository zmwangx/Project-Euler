#!/usr/bin/env python3


N = 10_000_000
s = [[] for _ in range(N + 1)]


def sieve():
    global s
    for i in range(2, N + 1):
        if not s[i]:
            for j in range(2 * i, N + 1, i):
                s[j].append(i)


def main():
    sieve()
    m = dict()
    for i in range(N+1):
        if len(s[i]) == 2:
            m[tuple(s[i])] = i
    print(sum(m.values()))


if __name__ == "__main__":
    main()
