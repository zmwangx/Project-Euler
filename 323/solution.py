#!/usr/bin/env python3

length = 32


def p(n):
    return (1 - 2 ** (-n)) ** length


def main():
    expectation = 0
    n = 0
    while True:
        delta = 1 - p(n)
        if delta < 1e-11:
            break
        expectation += delta
        n += 1
    print(f"{expectation:.10f}")


if __name__ == "__main__":
    main()
