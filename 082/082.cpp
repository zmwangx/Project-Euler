//
//  main.cpp
//  Prbl082
//  Project Euler
//
//  Created by Zhiming Wang on 12/12/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Dynamic programming.
//
//  (1)
//  minSum[row][1] = matrix[row][1], 1 <= row <= RANGE;
//  minSum[row][col] = min{ minSum[lastRow][col-1] +
//                          columnSum(col, lastRow, row),
//                          1 <= lastRow <= RANGE },
//                     2 <= col <= RANGE,
//                     1 <= row <= RANGE.
//
//  (2)
//  columnSum(col, row1, row2) = \sum_{row = row1}^{row2} matrix[row][col],
//                             = basicColumnSum[col][row2] -
//                               basicColumnSum[col][row1-1],
//                                   if row1 <= row2;
//                             = \sum_{row = row2}^{row1} matrix[row][col],
//                             = basicColumnSum[col][row1] -
//                               basicColumnSum[col][row2-1],
//                                   if row2 < row1,
//                               1 <= col, row1, row2 <= RANGE.
//
//  (3)
//  basicColumnSum[col][0] = 0, 1 <= col <= RANGE;
//  basicColumnSum[col][row] = \sum_{r = 1}^{row} matrix[col][r]
//                           = basicColumnSum[col][row-1] + matrix[row][col],
//                             1 <= col, row <= RANGE.
//
//  -------------------------------------------------------------
//  Answer: 260324
//

// Test the functionality of input phase.
// #define __PRBL082_IS_IN_DEBUGGING_PHASE_01__ 1
// Test the functionality of generating basicColumnSum phase.
// #define __PRBL082_IS_IN_DEBUGGING_PHASE_02__ 2
// Test the functionality of main computation part
// #define __PRBL082_IS_IN_DEBUGGING_PHASE_03__ 3

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

static const unsigned RANGE = 80;

static int columnSum(unsigned col, unsigned row1, unsigned row2,
                     int basicColumnSum[RANGE + 1][RANGE + 1]);

int main() {
    std::ifstream input("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                        "ProjectEuler/C++/Prbl082/matrix.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening matrix.txt!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Read matrix.
    int matrix[RANGE + 1][RANGE + 1];
    for (int row = 1; row <= RANGE; ++row) {
        std::string line;
        std::getline(input, line);
        std::istringstream lineStream(line);
        for (int col = 1; col <= RANGE; ++col) {
            std::string element;
            std::getline(lineStream, element, ',');
            matrix[row][col] = std::atoi(element.c_str());
        }
    }
    
#ifdef __PRBL082_IS_IN_DEBUGGING_PHASE_01__
    // Print matrix.
    for (int row = 1; row <= RANGE; ++row) {
        for (int col = 1; col <= RANGE; ++col) {
            std::cout << matrix[row][col] << ' ';
        }
        std::cout << std::endl;
    }
#endif
    
    // Construct <code>basicColumnSum</code>.
    //
    // Recall:
    // 
    // (3)
    // basicColumnSum[col][0] = 0, 1 <= col <= RANGE;
    // basicColumnSum[col][row] = \sum_{r = 1}^{row} matrix[col][r]
    //                          = basicColumnSum[col][row-1] + matrix[row][col],
    //                            1 <= col, row <= RANGE.
    
    int basicColumnSum[RANGE + 1][RANGE + 1];
    for (unsigned col = 1; col <= RANGE; ++col) {
        basicColumnSum[0][col] = 0;
    }
    for (unsigned col = 1; col <= RANGE; ++col) {
        basicColumnSum[col][0] = 0;
        for (unsigned row = 1; row <= RANGE; ++row) {
            basicColumnSum[col][row] = basicColumnSum[col][row - 1] +
                                       matrix[row][col];
        }
    }
    
#ifdef __PRBL082_IS_IN_DEBUGGING_PHASE_02__
    for (int row = 1; row <= RANGE; ++row) {
        for (int col = 1; col <= RANGE; ++col) {
            std::cout << basicColumnSum[col][row] << " ";
        }
        std::cout << std::endl;
    }
#endif
    
    // Main computations.
    //
    // Recall:
    //
    // (1)
    // minSum[row][1] = matrix[row][1], 1 <= row <= RANGE;
    // minSum[row][col] = min{ minSum[lastRow][col-1] +
    //                         columnSum(col, lastRow, row),
    //                         1 <= lastRow <= RANGE },
    //                    2 <= col <= RANGE,
    //                    1 <= row <= RANGE.
    //
    int minSum[RANGE + 1][RANGE + 1];
    for (unsigned row = 1; row <= RANGE; ++row) {
        minSum[row][1] = matrix[row][1];
    }
    for (unsigned col = 2; col <= RANGE; ++col) {
        for (unsigned row = 1; row <= RANGE; ++row) {
            // Let lastRow = 1.
            minSum[row][col] = minSum[1][col-1] +
                               columnSum(col, 1, row, basicColumnSum);
            for (unsigned lastRow = 2; lastRow <= RANGE; ++lastRow) {
                int newSum = minSum[lastRow][col-1] +
                             columnSum(col, lastRow, row, basicColumnSum);
                if (newSum < minSum[row][col]) {
                    minSum[row][col] = newSum;
                }
            }
        }
    }
    
#ifdef __PRBL082_IS_IN_DEBUGGING_PHASE_03__
    for (unsigned row = 1; row <= RANGE; ++row) {
        for (unsigned col = 1; col <= RANGE; ++col) {
            std::cout << minSum[row][col] << ' ';
        }
        std::cout << std::endl;
    }
#endif
    
    // Find smallest.
    int minPathSum = minSum[1][RANGE];
    for (unsigned row = 2; row <= RANGE; ++row) {
        if (minSum[row][RANGE] < minPathSum) {
            minPathSum = minSum[row][RANGE];
        }
    }
    
    std::cout << minPathSum << std::endl;
    
    return 0;
}

//
// Recall:
//
// (2)
// columnSum(col, row1, row2) = \sum_{row = row1}^{row2} matrix[row][col],
//                            = basicColumnSum[col][row2] -
//                              basicColumnSum[col][row1-1],
//                                  if row1 <= row2;
//                            = \sum_{row = row2}^{row1} matrix[row][col],
//                            = basicColumnSum[col][row1] -
//                              basicColumnSum[col][row2-1],
//                                  if row2 < row1,
//                              1 <= col, row1, row2 <= RANGE.
//
static int columnSum(unsigned col, unsigned row1, unsigned row2,
                     int basicColumnSum[RANGE + 1][RANGE + 1]) {
    if (row1 <= row2) {
        return basicColumnSum[col][row2] - basicColumnSum[col][row1-1];
    } else {
        return basicColumnSum[col][row1] - basicColumnSum[col][row2-1];
    }
}