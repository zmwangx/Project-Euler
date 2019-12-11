#!/usr/bin/env sage
bound = 10 ** 12
denom_sum = 0
for n in range(2, 100001):
    if int(sqrt(n)) ** 2 == n:
        continue
    # Note: we need to expand to this many decimal places. Using
    # RR(sqrt(n)) does not produce correct results.
    approx = sqrt(n).n(200).nearby_rational(max_denominator=bound)
    # print("{}\t{}".format(n, approx))
    denom_sum += approx.denominator()
print(denom_sum)
