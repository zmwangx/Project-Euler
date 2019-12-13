#!/usr/bin/env python3

import itertools


def generate_maximix(cars):
    prev_mixes = [f"{cars[-1]}{cars[-2]}"]
    length = 2
    for car in reversed(cars[:-2]):
        length += 1
        mixes = []
        for mix in prev_mixes:
            mix = list(reversed([car, *mix]))
            for pos in range(1, length - 1):
                mixes.append("".join(itertools.chain(mix[:pos], reversed(mix[pos:]))))
        prev_mixes = mixes
    return sorted(mixes)


def main():
    print(generate_maximix("ABCDEFGHIJK")[2010])


if __name__ == "__main__":
    main()
