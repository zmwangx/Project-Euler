#!/usr/bin/env python3


def expectation(n):
    return 0 if n == 1 else expectation(n - 1) + (2 ** (n - 1) - 1) / n


def main():
    print(f"{expectation(30):.2f}")


if __name__ == "__main__":
    main()
