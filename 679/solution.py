#!/usr/bin/env python3

import itertools
import functools


N = 30
CHARS = ["A", "E", "F", "R"]
KEYWORDS = ["FREE", "FARE", "AREA", "REEF"]


@functools.lru_cache(maxsize=None)
def count(last_three_chars, keywords_mask, remaining_chars):
    if remaining_chars == 0:
        if keywords_mask == 0b1111:
            return 1
        return 0
    _count = 0
    matching_ch = None
    for i, keyword in enumerate(KEYWORDS):
        if last_three_chars == keyword[:3]:
            matching_ch = keyword[-1]
            if (keywords_mask >> i) & 1 == 1:
                # Conflict.
                break
            _count += count(keyword[-3:], keywords_mask | (1 << i), remaining_chars - 1)
    for ch in CHARS:
        if ch == matching_ch:
            continue
        _count += count(last_three_chars[-2:] + ch, keywords_mask, remaining_chars - 1)
    return _count


def main():
    _count = 0
    for combos in itertools.product(CHARS, CHARS, CHARS):
        _count += count("".join(combos), 0b0000, N - 3)
    print(_count)


if __name__ == "__main__":
    main()
