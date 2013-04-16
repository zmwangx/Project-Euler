//
//  main.cpp
//  Prbl081
//  Project Euler
//
//  Created by Zhiming Wang on 12/11/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Dynamic programming.
//
//  minSum[row, 0] = columnSum(0, 0, row), 0 <= row <= DIMENSION - 1;
//  minSum[row, col] = min{minSum[lastRow, col-1] +
//                         columnSum(col, lastRow, row),
//                         0 <= lastRow <= row},
//                     0 <= row <= DIMENSION - 1, 1 <= col <= DIMENSION - 1,
//
//  where
//
//  columnSum(col, row1, row2) = Sum[matrix[row, col], {row, row1, row2}].
//  ----------------------------------------------------------------------
//  Answer: 427337
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

static const unsigned DIMENSION = 80;

static void readMatrix(std::ifstream& input, int matrix[DIMENSION][DIMENSION]);
static void computeBasicColumnSums(int matrix[DIMENSION][DIMENSION],
                                   int basicColumnSums[DIMENSION][DIMENSION]);
static int minimalPathSum(unsigned row, unsigned col,
                          int minSum[DIMENSION][DIMENSION],
                          int basicColumnSums[DIMENSION][DIMENSION]);
static int columnSum(unsigned col, unsigned row1, unsigned row2,
                     int basicColumnSums[DIMENSION][DIMENSION]);

int main() {
    std::ifstream input("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                        "ProjectEuler/C++/Prbl081/matrix.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening matrix.txt!" << std::endl;
        exit(-1);
    }
    
    int matrix[DIMENSION][DIMENSION];
    int basicColumnSums[DIMENSION][DIMENSION];
    
    readMatrix(input, matrix);
    computeBasicColumnSums(matrix, basicColumnSums);
    
    int minSum[DIMENSION][DIMENSION];
    for (unsigned row = 0; row < DIMENSION; ++row) {
        minSum[row][0] = columnSum(0, 0, row, basicColumnSums);
    }
    for (unsigned col = 1; col < DIMENSION; ++col) {
        for (unsigned row = 0; row < DIMENSION; ++row) {
            minSum[row][col] = minimalPathSum(row, col,
                                              minSum,
                                              basicColumnSums);
        }
    }
    
    std::cout << minSum[DIMENSION - 1][DIMENSION - 1] << std::endl;
    
    return 0;
}

static void readMatrix(std::ifstream& input,
                       int matrix[DIMENSION][DIMENSION]) {
    for (int row = 0; row < DIMENSION; ++row) {
        std::string rowString;
        std::getline(input, rowString);
        std::istringstream rowStringStream(rowString);
        for (int col = 0; col < DIMENSION; ++col) {
            std::string elementString;
            std::getline(rowStringStream, elementString, ',');
            matrix[row][col] = std::atoi(elementString.c_str());
        }
    }
}

static void computeBasicColumnSums(int matrix[DIMENSION][DIMENSION],
                                   int basicColumnSums[DIMENSION][DIMENSION]) {
    for (unsigned col = 0; col < DIMENSION; ++col) {
        basicColumnSums[col][0] = matrix[0][col];
        for (unsigned row = 1; row < DIMENSION; ++row) {
            basicColumnSums[col][row] = basicColumnSums[col][row - 1] +
                                        matrix[row][col];
        }
    }
}

static int minimalPathSum(unsigned row, unsigned col,
                          int minSum[DIMENSION][DIMENSION],
                          int basicColumnSums[DIMENSION][DIMENSION]) {
    // Assign first to minSum[row][col] the value of lastRow = 0.
    int minimalPathSum = minSum[0][col - 1] +
        columnSum(col, 0, row, basicColumnSums);
    for (unsigned lastRow = 1; lastRow <= row; ++lastRow) {
        int newSum = minSum[lastRow][col - 1] +
            columnSum(col, lastRow, row, basicColumnSums);
        if (newSum < minimalPathSum) {
            minimalPathSum = newSum;
        }
    }
    return minimalPathSum;
}

static int columnSum(unsigned col, unsigned row1, unsigned row2,
                     int basicColumnSums[DIMENSION][DIMENSION]) {
    if (row1 == 0) {
        return basicColumnSums[col][row2];
    } else {
        return basicColumnSums[col][row2] - basicColumnSums[col][row1 - 1];
    }
}