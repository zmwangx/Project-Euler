#!/usr/bin/env python3

import collections


State = collections.namedtuple("State", "A1 A2 A3 A4 A5")


def calculate_expectation(state, remaining_days):
    if state in calculate_expectation.cache:
        return calculate_expectation.cache[state]
    if remaining_days == 1:
        return 1
    expectation = 0
    total_choices = sum(state)
    if total_choices == 1:
        k = state.index(1)
        new_state = State(*[0 if i <= k else 1 for i in range(5)])
        expectation = 1 + calculate_expectation(new_state, remaining_days - 1)
    else:
        for k in range(5):
            if state[k] > 0:
                new_state = State(
                    *[
                        state[i] if i < k else state[i] - 1 if i == k else state[i] + 1
                        for i in range(5)
                    ]
                )
                expectation += (
                    state[k]
                    / total_choices
                    * calculate_expectation(new_state, remaining_days - 1)
                )
    print(state, expectation)
    calculate_expectation.cache[state] = expectation
    return expectation


calculate_expectation.cache = dict()


def main():
    # Minus 2 to exclude first and last.
    expectation = calculate_expectation(State(1, 0, 0, 0, 0), 16) - 2
    print(f"{expectation:.6f}")


if __name__ == "__main__":
    main()
