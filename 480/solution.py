#!/usr/bin/env python3


import collections
import functools


@functools.lru_cache(maxsize=None)
def count_sequences(budgets, length):
    assert length > 0
    total_count = len(budgets)  # Number of one letter sequences
    if length == 1:
        return total_count
    last_budget = 0
    last_sub_count = 0
    for i, budget in enumerate(budgets):
        if budget == last_budget:
            # Number of entries leading with this character is the same
            # as the last.
            total_count += last_sub_count
            continue
        new_budgets = list(budgets)
        if budget == 1:
            new_budgets.pop()
        else:
            new_budgets[i] -= 1
            new_budgets.sort(reverse=True)
        last_budget = budget
        last_sub_count = count_sequences(tuple(new_budgets), length - 1)
        total_count += last_sub_count
    # print(budgets, length, total_count)
    return total_count


def P(chars, length, w):
    assert length > 0
    index = 1
    charcounts = collections.Counter(chars)
    for ch in sorted(charcounts):
        if ch < w[0]:
            charcounts[ch] -= 1
            budgets = tuple(
                sorted((cnt for _, cnt in charcounts.items() if cnt > 0), reverse=True)
            )
            index += 1  # one letter sequence ch
            if length > 1:
                # >=2-letter sequences starting with ch
                index += count_sequences(budgets, length - 1)
            charcounts[ch] += 1
    if len(w) == 1:
        return index
    chars = list(chars)
    chars.remove(w[0])
    chars = "".join(chars)
    index += P(chars, length - 1, w[1:])
    return index


def W(chars, length, p):
    assert length > 0
    charcounts = collections.Counter(chars)
    for ch in sorted(charcounts):
        if p == 1:
            return ch
        p -= 1
        if length > 1:
            charcounts[ch] -= 1
            budgets = tuple(
                sorted((cnt for _, cnt in charcounts.items() if cnt > 0), reverse=True)
            )
            sub_count = count_sequences(budgets, length - 1)
            if p <= sub_count:
                chars = "".join(charcounts.elements())
                return ch + W(chars, length - 1, p)
            p -= sub_count
            charcounts[ch] += 1


def main():
    s = sorted("thereisasyetinsufficientdataforameaningfulanswer")
    length = 15
    PP = lambda w: P(s, length, w)
    WW = lambda p: W(s, length, p)
    print(
        WW(
            PP("legionary")
            + PP("calorimeters")
            - PP("annihilate")
            + PP("orchestrated")
            - PP("fluttering")
        )
    )


if __name__ == "__main__":
    main()
