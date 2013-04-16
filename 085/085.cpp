//
//  main.cpp
//  Prbl085
//  Project Euler
//
//  Created by Zhiming Wang on 12/13/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  For m * n grid there are (m + ... + 1) * (n + ... + 1) rectangles. Then
//  exhaustion.
//  -----------
//  Answer: 2772
//

#include <iostream>
#include <cmath>

static const int EXPECTATION = 2000000;

static int basisForNearestTriangleNumber(double expectation);

int main() {
    // Iterate on m, make sure that m*(m+1)/2 is no larger than the first
    // triangle number above EXPECTATION.
    int smallestDifference = EXPECTATION;
    int gridAreaWithSmallestDifference;
    for (int m = 1; m * (m - 1) / 2 < EXPECTATION; ++m) {
        int mTriangle = m * (m + 1) / 2;
        int n = basisForNearestTriangleNumber(EXPECTATION / mTriangle);
        int nTriangle = n * (n + 1) / 2;
        int nTotalRectangles = mTriangle * nTriangle;
        int difference = std::abs(nTotalRectangles - EXPECTATION);
        if (difference < smallestDifference) {
            smallestDifference = difference;
            gridAreaWithSmallestDifference = m * n;
        }
    }
    std::cout << gridAreaWithSmallestDifference << std::endl;
    
    return 0;
}

static int basisForNearestTriangleNumber(double expectation) {
    // n(n+1)/2 \approx expectation. So we solve the quadratic equation:
    // n^2 + n - 2 * expectation = 0.
    double accurate = (-1 + std::sqrt(1 + 8 * expectation)) / 2;
    int lowerN = std::floor(accurate);
    int upperN = std::ceil(accurate);
    int lowerTriangle = lowerN * (lowerN + 1) / 2;
    int upperTriangle = upperN * (upperN + 1) / 2;
    if (expectation -  lowerTriangle < upperTriangle - expectation) {
        return lowerN;
    } else {
        return upperN;
    }
}