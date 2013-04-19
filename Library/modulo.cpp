/**
 * modulo.cpp
 * Project Euler Library
 * Created by Zhiming Wang on 04/19/2013.
 * --------------------------------------
 * Several utilities concerning modular arithmetic.
 */

#include "modulo.h"

/**
 * Greatest common divisor.
 *
 * Requirement:
 * x > 0, y > 0.
 */
extern arith_t
gcd(arith_t x, arith_t y) {
    if (x % y == 0) {
        return y;
    } else {
        return gcd(y, x % y);
    }
}

/**
 * Given coprime x and y, calculate u and v for the Bezout formula:
 *     u x + v y = 1.
 *
 * Requirements:
 * x > 0, y > 0
 * return value satisfies: -y < u < y, and v depending on u
 *
 * Algorithm:
 * Euclidean algorithm.
 * If y == 1, let {u = 1, y = 1 - x}, return {u, v};
 * If y > 1, let
 *     y = x0
 *     x = q y + y0
 * and by recursion
 *     u0 x0 + v0 y0 = 1,
 * then
 *     u0 y + v0 (x - q y) = 1,
 * namely
 *     v0 x + (u0 - q v0) y = 1.
 * Therefore, let
 *     u = v0 % y (C div, with positive/negative/0 remainder)
 * we have -y < u < y, and let
 *     v = (1 - u x) / y
 * consequently. We return {u, v} at last.
 */
extern void
bezout(arith_t x, arith_t y, arith_t *u, arith_t *v) {
    if (y == 1) {
        *u = 1;
        *v = 1 - x;
        return;
    }
    arith_t x0 = y;
    arith_t y0 = x % y;
    arith_t u0, v0;
    bezout(x0, y0, &u0, &v0);
    *u = v0 % y;
    *v = (1 - (*u) * x) / y;
    return;
}

/**
 * Calculates the inverse of a in modulo n, namely,
 *     a^{-1} (mod n).
 *
 * Requirement:
 * gcd(a, n) = 1.
 * return value satisfies: 1 <= a^{-1} <= n-1.
 */
extern arith_t
inverse(arith_t a, arith_t n) {
    arith_t u, v;
    bezout(a, n, &u, &v);
    // u is guaranteed to satisfy
    //     -n < u < n
    // by bezout.
    // we need to get the positive remainder:
    return (u + n) % n;
}
