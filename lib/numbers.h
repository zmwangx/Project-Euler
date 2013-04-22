/**
 * numbers.h
 * Project Euler shared libraries
 * Created by Zhiming Wang on 04/22/2013.
 * --------------------------------------
 * Some general number theory related utilities.
 */

#ifndef NUMBERS_H
#define NUMBERS_H

#include <cstdlib>

#define arith_t signed long long

/**
 * Length of positive integer.
 */
extern size_t
num_length(arith_t n);

/**
 * Power of 10: 10^k.
 */
extern arith_t
pwr10(size_t k);

#endif
