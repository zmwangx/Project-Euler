#!/usr/bin/env python3

import collections


def main():
    q = collections.deque()
    # (depth, x1, x2, y1, y2, horizontal)
    q.append((1, 0, 4096, 0, 2048, True))
    rectcount = collections.defaultdict(int)
    curr_depth = 0
    while q:
        depth, x1, x2, y1, y2, horizontal = q.popleft()
        if depth > curr_depth:
            count = sum(1 for v in rectcount.values() if v == 4)
            rectcount = collections.defaultdict(int)
            print(f"f({curr_depth}) = {count}")
            curr_depth = depth
        if depth > 10:
            break
        rectcount[(x1, y1)] += 1
        rectcount[(x1, y2)] += 1
        rectcount[(x2, y1)] += 1
        rectcount[(x2, y2)] += 1
        depth += 1
        if horizontal:
            x3 = (3 * x1 + x2) // 4
            x4 = (x1 + 3 * x2) // 4
            y3 = (y1 + y2) // 2
            q.append((depth, x1, x3, y1, y2, False))
            q.append((depth, x3, x4, y1, y3, True))
            q.append((depth, x3, x4, y3, y2, True))
            q.append((depth, x4, x2, y1, y2, False))
        else:
            x3 = (x1 + x2) // 2
            y3 = (3 * y1 + y2) // 4
            y4 = (y1 + 3 * y2) // 4
            q.append((depth, x1, x2, y1, y3, True))
            q.append((depth, x1, x3, y3, y4, False))
            q.append((depth, x3, x2, y3, y4, False))
            q.append((depth, x1, x2, y4, y2, True))


if __name__ == "__main__":
    main()
