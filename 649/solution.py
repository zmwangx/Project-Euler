#!/usr/bin/env python3

import collections
import itertools

import numpy


def main():
    a = numpy.zeros((9, 9, 9, 9, 9, 9), dtype=bool)
    count = 0
    losing_positions = [
        (0, 0),
        (0, 1),
        (1, 0),
        (1, 1),
        (2, 2),
        (2, 3),
        (3, 2),
        (3, 3),
        (4, 4),
        (4, 5),
        (5, 4),
        (5, 5),
        (6, 6),
        (6, 7),
        (7, 6),
        (7, 7),
        (8, 8),
    ]
    nimmer = [0, 0, 1, 1, 2, 2, 3, 3, 4]
    for x1, y1 in itertools.product(*[range(9), range(9)]):
        for x2, y2 in itertools.product(*[range(9), range(9)]):
            for x3, y3 in itertools.product(*[range(9), range(9)]):
                # winning = False
                # for s in [2, 3, 5, 7]:
                #     if x1 >= s and not a[x1 - s][y1][x2][y2][x3][y3]:
                #         winning = True
                #         break
                # for s in [2, 3, 5, 7]:
                #     if y1 >= s and not a[x1][y1 - s][x2][y2][x3][y3]:
                #         winning = True
                #         break
                # for s in [2, 3, 5, 7]:
                #     if x2 >= s and not a[x1][y1][x2 - s][y2][x3][y3]:
                #         winning = True
                #         break
                # for s in [2, 3, 5, 7]:
                #     if y2 >= s and not a[x1][y1][x2][y2 - s][x3][y3]:
                #         winning = True
                #         break
                # for s in [2, 3, 5, 7]:
                #     if x3 >= s and not a[x1][y1][x2][y2][x3 - s][y3]:
                #         winning = True
                #         break
                # for s in [2, 3, 5, 7]:
                #     if y3 >= s and not a[x1][y1][x2][y2][x3][y3 - s]:
                #         winning = True
                #         break
                nimmers = collections.Counter(
                    (
                        nimmer[x1],
                        nimmer[y1],
                        nimmer[x2],
                        nimmer[y2],
                        nimmer[x3],
                        nimmer[y3],
                    )
                )
                for k in nimmers:
                    nimmers[k] %= 2
                winning = (
                    nimmers[0],
                    nimmers[1],
                    nimmers[2],
                    nimmers[3],
                    nimmers[4],
                ) not in ((0, 0, 0, 0, 0), (0, 1, 1, 1, 0), (1, 1, 1, 1, 0))
                # assert (
                #     nimmer_winning == winning
                # ), f"{x1} {y1} {x2} {y2} {x3} {y3} {winning} {nimmer_winning}"
                if winning:
                    count += 1
                # else:
                #     w1 = "L" if (x1, y1) in losing_positions else "W"
                #     w2 = "L" if (x2, y2) in losing_positions else "W"
                #     w3 = "L" if (x3, y3) in losing_positions else "W"
                #     print(x1, y1, x2, y2, x3, y3, w1, w2, w3)
                a[x1][y1][x2][y2][x3][y3] = winning
    print(count)


if __name__ == "__main__":
    main()
