//
//  prime.h
//  ProjectEuler
//
//  Created by Zhiming Wang on 12/6/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//
//  Exports some basic checks and operations for prime numbers.
//

#ifndef __ProjectEuler__prime__
#define __ProjectEuler__prime__

#include <vector>

/**
 * Generates all primes in the range of [lowerBound, upperBound].
 *
 * @param       primes      a vector of ints to store the primes generated
 * @param       lowerBound, upperBound  the bounds of the integer ranges in
 *                          which primes are requested
 * @complexity  O(n log log n), according to Wikipedia page on the sieve of 
 *              Eratosthenes
 */
void generatePrimes(std::vector<int>& primes, int lowerBound, int upperBound);

/**
 * Checks if positive integer n is a prime number. Negative inputs result in 
 * false.
 * <p>
 * The second version can take in an already generated sorted prime number 
 * vector (from small to large) containing all the prime numbers in some range 
 * [1, k] to speed up the check. If primeRange is specified, then k equals 
 * primeRange; otherwise, primeRange is by default 1, and k is automatically 
 * set to the largest prime in primes (if primes is not empty).
 *
 * @param       n           the positive number to be checked
 * @param       primes      the sorted prime number vector containing all prime
 *                          numbers in some range [1, k]
 * @param       primeRange  k for the range [1, k]; 1 by default
 * @return      true if n is a prime number; false otherwise
 * @complexity  (1) O(sqrt(n));
 *              (2) in between O(sqrt(n) / log(sqrt(n))) and O(sqrt(n)), 
 *              depending on the quality of primes
 * @see         generatePrimes
 */
bool isPrime(long n);
bool isPrime(long n, std::vector<int>& primes, int primeRange = 1);
#endif /* defined(__ProjectEuler__prime__) */
