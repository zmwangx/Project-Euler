#!/usr/bin/env python3

def search_multiple(n):
    t = (1, 1, 1)
    seen = set([t])
    steps = 0
    while True:
        steps += 1
        new = (t[0] + t[1] + t[2]) % n
        if new == 0:
            return True
        t = (t[1], t[2], new)
        if t in seen:
            return False
        seen.add(t)


def main():
    count = 0
    n = 3
    while True:
        if not search_multiple(n):
            count += 1
            if count == 124:
                print(n)
                return
        n += 2


if __name__ == "__main__":
    main()
