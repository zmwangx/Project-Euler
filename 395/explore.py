#!/usr/bin/env python3

import argparse
import collections
import itertools

import matplotlib.pyplot as plt
import matplotlib.collections as mc


def segment(x, y):
    return ((x.real, x.imag), (y.real, y.imag))


def square(a, b, c, d):
    return [segment(a, b), segment(b, c), segment(c, d), segment(d, a)]


def generate_new_segments_and_bases(a, b):
    c = complex(0.64, 0.48) * (b - a) + a
    d = complex(-0.48, 0.64) * (b - a) + a
    e = complex(0.16, 1.12) * (b - a) + a
    f = complex(0.12, 0.84) * (b - a) + b
    g = complex(0.48, 0.36) * (b - a) + b
    return [*square(a, c, e, d), *square(b, c, f, g)], ((d, e), (f, g))


def bounding_box(*segments):
    points = list(itertools.chain(*segments))
    xs = [p[0] for p in points]
    ys = [p[1] for p in points]
    return min(xs), max(xs), min(ys), max(ys)


def print_bounding_box(*segments):
    xmin, xmax, ymin, ymax = bounding_box(*segments)
    area = (xmax - xmin) * (ymax - ymin)
    print(f"{area} (xmin={xmin}, xmax={xmax}, ymin={ymin}, ymax={ymax})")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--depth", type=int, default=10)
    parser.add_argument("--plot", action="store_true")
    parser.add_argument("--save", action="store_true")
    args = parser.parse_args()

    segments = square(complex(0, 0), complex(1, 0), complex(1, 1), complex(0, 1))
    bases = collections.deque()
    bases.append((1, (complex(0, 1), complex(1, 1))))
    curr_depth = 1
    while bases:
        depth, base = bases.popleft()
        if depth > curr_depth:
            print(f"depth {curr_depth}: ", end="")
            print_bounding_box(*segments)
            curr_depth = depth
        if depth > args.depth:
            continue
        new_segments, new_bases = generate_new_segments_and_bases(*base)
        segments.extend(new_segments)
        for new_base in new_bases:
            bases.append((depth + 1, new_base))

    if args.plot or args.save:
        _, axes = plt.subplots()
        axes.add_collection(mc.LineCollection(segments, colors="green", linewidth=1))
        plt.axis("equal")
        plt.axis("off")
        if args.plot:
            plt.show()
        elif args.save:
            plt.savefig("tree.svg")


if __name__ == "__main__":
    main()
