/**
 * modulo.c
 * Project Euler Library
mod * Created by Zhiming Wang on 04/19/2013.
 * --------------------------------------
 * Several utilities concerning modular arithmetic.
 */

#ifndef MODULO_H
#define MODULO_H

// arith_t must be a signed integral type
// default is signed int
// can be changed via macros USE_INT_FOR_ARITM, USE_LONG_FOR_ARITH, and
// USE_LLONG_FOR_ARITH
#if   defined(USE_INT_FOR_ARITH)
typedef signed int arith_t;
#elif defined(USE_LONG_FOR_ARITH)
typedef signed long arith_t;
#elif defined(USE_LLONG_FOR_ARITH)
typedef signed long long arith_t;
#else /* default */
typedef signed int arith_t;
#endif

/**
 * Greatest common divisor.
 *
 * Requirement:
 * x > 0, y > 0.
 */
extern arith_t
gcd(arith_t x, arith_t y);

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
