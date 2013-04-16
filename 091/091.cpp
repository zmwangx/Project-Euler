//
//  main.cpp
//  Prbl091
//  Project Euler
//
//  Created by Zhiming Wang on 12/15/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Exhaustion.
//  -----------
//  Answer: 14234
//

#include <iostream>

static const int RANGE = 50;

int main() {
    int count = 0;
    for (int x1 = 0; x1 <= RANGE; ++x1) {
        for (int y1 = 0; y1 <= RANGE; ++y1) {
            for (int x2 = 0; x2 <= RANGE; ++x2) {
                for (int y2 = 0; y2 <= RANGE; ++ y2) {
                    int distance1Squared = x1 * x1 + y1 * y1;
                    int distance2Squared = x2 * x2 + y2 * y2;
                    int distance3Squared = (x1 - x2) * (x1 - x2) +
                                           (y1 - y2) * (y1 - y2);
                    if (distance1Squared == 0 ||
                        distance2Squared == 0 ||
                        distance3Squared == 0) {
                        continue;
                    }
                    if (distance1Squared + distance2Squared == distance3Squared
                        ||
                        distance2Squared + distance3Squared == distance1Squared
                        ||
                        distance3Squared + distance1Squared == distance2Squared)
                    {
                        ++count;
                    }
                }
            }
        }
    }
    std::cout << count / 2 << std::endl;
    return 0;
}