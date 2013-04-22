/**
 * modulo.c
 * Project Euler Library
mod * Created by Zhiming Wang on 04/19/2013.
 * --------------------------------------
 * Several utilities concerning modular arithmetic.
 */

#ifndef MODULO_H
#define MODULO_H

#define arith_t signed long long

/**
 * Greatest common divisor.
 *
 * Requirements:
 * x > 0, y > 0.
 */
extern arith_t
gcd(arith_t x, arith_t y);

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
pwrmod(arith_t a, unsigned k, arith_t n);

/**
 * Given coprime x and y, calculate u and v for the Bezout formula:
 *     u x + v y = 1.
 *
 * Requirements:
 * x > 0, y > 0
 * return value satisfies: -y < u < y, and v depending on u
 */
extern void
bezout(arith_t x, arith_t y, arith_t *u, arith_t *v);

/**
 * Calculates the inverse of a in modulo n, namely,
 *     a^{-1} (mod n).
 *
 * Requirement:
 * n > 1; gcd(a, n) = 1.
 * return value satisfies: 1 <= a^{-1} <= n-1.
 */
extern arith_t
inverse(arith_t a, arith_t n);

#endif
