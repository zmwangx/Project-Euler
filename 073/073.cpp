//
//  main.cpp
//  Prbl073
//  Project Euler
//
//  Created by Zhiming Wang on 12/11/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Note that the sequence is essentially a Farey sequence. Recall the property
//  of Farey sequence: adjacent $a1/b1$ and $a2/b2$ derive $(a1+a2)/(b1+b2)$.
//  In this problem, due to this property, only the denominator matters. Thus
//  we can simulate the generation of Farey sequence by recursion and keep
//  track of the denominators.
//  --------------------------
//  Answer: 7295372
//

#include <iostream>

static const int MAX_DENOMINATOR = 12000;
static const int STARTING_DENOMINATOR_1 = 3;
static const int STARTING_DENOMINATOR_2 = 2;

static int nFractionsInBetween(int denominator1, int denominator2);

int main() {
    std::cout << nFractionsInBetween(STARTING_DENOMINATOR_1,
                                     STARTING_DENOMINATOR_2);
    return 0;
}

static int nFractionsInBetween(int denominator1, int denominator2) {
    if (denominator1 + denominator2 > MAX_DENOMINATOR) {
        return 0;
    }
    int newDenominator = denominator1 + denominator2;
    return nFractionsInBetween(denominator1,    newDenominator) +
           nFractionsInBetween(newDenominator,  denominator2) + 1;
}