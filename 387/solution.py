#!/usr/bin/env python3

from miller_rabin import miller_rabin


def generate_right_truncatable_harshads(max_digits):
    # h will be a list of (harshad, sum of digits) pairs.
    h = []
    h1 = [(k, k) for k in range(1, 10)]
    h.extend(h1)
    prev_hn = h1
    for n in range(2, max_digits + 1):
        hn = []
        for k, s in prev_hn:
            for d in range(10):
                kk = 10 * k + d
                ss = s + d
                if kk % ss == 0:
                    hn.append((kk, ss))
        h.extend(hn)
        prev_hn = hn
    return h


def main():
    h = generate_right_truncatable_harshads(13)
    # Filter strong Harshads.
    h = [k for k, s in h if miller_rabin(k // s)]
    sum_ = 0
    for k in h:
        for d in (1, 3, 7, 9):
            n = k * 10 + d
            if miller_rabin(n):
                print(n)
                sum_ += n
    print(f"sum: {sum_}")


if __name__ == "__main__":
    main()
