//
//  random.h
//  Project Euler
//
//  Created by Zhiming Wang on 12/05/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//

#ifndef __MapGenerators__random__
#define __MapGenerators__random__

/**
 * Generates a random double in the range of [a, b). Then default range is [0, 
 * 1).
 *
 * @return      a random double in the range of [a, b)
 * @complexity  constant
 */
double randomDouble(double a = 0, double b = 1);

/**
 * Generates a random integer in the range of [a, b].
 *
 * @return      a random integer in the range of [a, b]
 * @complexity  constant
 */
int randomInt(int a, int b);

/**
 * Simulates a Bernoulli distribution random event. The probability of 
 * returning <code>true</code> is <code>p</code>, and the probability of 
 * returning <code>false</code> is <code>1-p</code>.
 *
 * @param       p   probability of returning true
 * @return      a bool type object, which is the result of random event 
 *              simulation
 * @complexity  constant
 */
bool randomProbability(double p);

#endif /* defined(__MapGenerators__random__) */
