#!/usr/bin/env python3

import functools


@functools.lru_cache(maxsize=None)
def f(s, w, s0, w0):
    assert s >= w >= w0 and s >= s0 >= w0
    if (s0, w0) == (1, 0):
        return 1 if w == 0 else 0
    count = 0
    for s1 in range(1, min(s, s0) + 1):
        if s1 == s:
            # All in one group.
            if w0 >= w:
                count += 1
            continue
        if s1 == s0:
            max_w1 = min(w, w0)
        else:
            max_w1 = min(w, s1)
        for w1 in range(max_w1 + 1):
            rs = s - s1
            rw = w - w1
            if rs < rw:
                continue
            new_s0, new_w0 = min((rs, rw), (s1, w1))
            new_w0 = min(new_w0, rw)
            count += f(rs, rw, new_s0, new_w0)
    return count


def main():
    b = 60
    w = 40
    print(f(b + w, w, b + w, w))


if __name__ == "__main__":
    main()
