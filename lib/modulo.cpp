/**
 * modulo.cpp
 * Project Euler Library
 * Created by Zhiming Wang on 04/19/2013.
 * --------------------------------------
 * Several utilities concerning modular arithmetic.
 */

#include "modulo.h"

static arith_t pwrmod_priv(arith_t a, unsigned k, arith_t n);

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
 * Power mod: a^k (mod n).
 *
 * Requirements:
 * k >= 0, n > 0; the return value is between 0 and n-1.
 *
 * Implementation:
 * Binary recursion. Complexity O(log k).
 */
extern arith_t
pwrmod(arith_t a, unsigned k, arith_t n) {
    a = (a % n + n) % n;
    if (a == 0) {
        return 0;
    } else {
        return pwrmod_priv(a, k, n);
    }
}

// 0 <= a < n-1, return value also between 0 and n-1
static arith_t
pwrmod_priv(arith_t a, unsigned k, arith_t n) {
    if (k == 0) {
        return 1;
    }
    arith_t half = pwrmod_priv(a, k / 2, n);
    if (k % 2 == 0) {
        return half * half % n;
    } else {
        return half * half % n * a % n;
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
 * n > 1; gcd(a, n) = 1.
 * return value satisfies: 1 <= a^{-1} <= n-1.
 */
extern arith_t
inverse(arith_t a, arith_t n) {
    arith_t u, v;
    // make sure a is positive
    a = ((a % n) + n) % n;
    bezout(a, n, &u, &v);
    // u is guaranteed to satisfy
    //     -n < u < n
    // by bezout.
    // we need to get the positive remainder:
    return (u + n) % n;
}

/**
 * Given a, n, and a prime p, check if n is a multiple of the order of a (mod
 * p), namely, whether a^n = 1 (mod p).
 *
 * Requirements:
 * n >= 0.
 */
extern bool
is_multiple_of_order(arith_t a, arith_t n, arith_t p) {
    n = gcd(n, p-1); // Fermat little theorem
    return (pwrmod(a, n, p) == 1);
}
