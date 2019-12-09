#!/usr/bin/env python3

import collections


# https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/
def find_period(arr):
    n = len(arr)
    z = [0] * n
    l, r = 0, 0
    for i in range(1, n):
        if i >= r:
            l, r = i, i
            while r < n and arr[r - l] == arr[r]:
                r += 1
            z[i] = r - l
        else:
            k = i - l
            if z[k] < r - i:
                z[i] = z[k]
            else:
                l = i
                while r < n and arr[r - l] == arr[r]:
                    r += 1
                z[i] = r - l
        if i <= n // 2 and i + z[i] == n:
            return i
    return None


# Calculates the k-th item of the Ulam sequence U(2, 2n+1) for n >= 2,
# where k > n + 4.
def ulam(n, k):
    s = collections.deque([2])
    e = 4 * n + 4
    for m in range(2 * n + 1, e, 2):
        s.append(m)
    s.append(e)
    s.append(e + 1)

    prev = e + 1
    m = e + 1
    diff = [2]
    l = 1
    pow2 = set(2 ** k for k in range(1, 31))
    while True:
        obtainable_from_2 = m == prev
        m += 2
        mm = m - e
        while s and s[0] <= mm:
            x = s.popleft()
        obtainable_from_e = x == mm
        if obtainable_from_2 == obtainable_from_e:
            continue
        s.append(m)
        diff.append(m - prev)
        prev = m
        l += 1
        if l >= 2 * n and l in pow2:
            period = find_period(diff)
            if period is not None:
                print(f"{n}: period {period}")
                break

    diff = diff[:period]
    period_jump = sum(diff)
    assert k > n + 4
    q, r = divmod(k - (n + 4), period)
    result = 4 * n  + 3
    result += period_jump * q
    for i in range(r):
        result += diff[i]
    return result



def main():
    sum_ = 0
    for n in range(2, 11):
        sum_ += ulam(n, 10 ** 11)
    print(sum_)


if __name__ == "__main__":
    main()
