//
//  random.cpp
//  Project Euler
//
//  Created by Zhiming Wang on 12/05/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//

#include "random.h"
#include <iostream>

#include <random>

double randomDouble(double a, double b) {
    static std::default_random_engine generator;
    std::uniform_real_distribution<> distribution(a, b);
    return distribution(generator);
}

int randomInt(int a, int b) {
    static std::default_random_engine generator;
    std::uniform_int_distribution<> distribution(a, b);
    return distribution(generator);
}

bool randomProbability(double p) {
    static std::default_random_engine generator;
    std::bernoulli_distribution distribution(p);
    return distribution(generator);
}