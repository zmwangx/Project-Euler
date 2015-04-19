#!/usr/bin/env python3

from math import floor, sqrt

def shorter_leg(j):
    """Compute length of shorter leg in the j-th irreducible case.

    See analysis.tex for details.
    """
    return int(round(((1+sqrt(2))**(2*j+1) + (1-sqrt(2))**(2*j+1) - 2) / 4))

PERIMETER_LIMIT = 99999999

def main():
    """Main computations.

    >>> main()
    3, 4, 5
    20, 21, 29
    119, 120, 169
    696, 697, 985
    4059, 4060, 5741
    23660, 23661, 33461
    137903, 137904, 195025
    803760, 803761, 1136689
    4684659, 4684660, 6625109
    27304196, 27304197, 38613965
    count: 10057761
    """
    j = 0
    count = 0
    while True:
        j += 1
        a = shorter_leg(j)
        b = a + 1
        c = int(round(sqrt(a**2 + b**2)))
        perimeter = a + b + c

        if perimeter > PERIMETER_LIMIT:
            break

        print("%d, %d, %d" % (a, b, c))
        count += floor(PERIMETER_LIMIT / perimeter)

    print("count: %d" % count)

if __name__ == '__main__':
    main()
