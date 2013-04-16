//
//  main.cpp
//  Prbl096
//  Project Euler
//
//  Created by Zhiming Wang on 12/15/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Possibility elimination.
//  ------------------------
//  Answer:
//

#include "sudoku.h"

#include <iostream>
#include <fstream>
#include <string>

static const int NUMBER_OF_CASES = 50;

int main() {
    std::ifstream input("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                        "ProjectEuler/C++/Prbl096/sudoku.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        exit(-1);
    }
    
    int sum = 0;
    for (int i = 0; i < NUMBER_OF_CASES; ++i) {
        std::string line;
        std::getline(input, line); // Read in case delimiter.
        
        std::string values;
        for (int row = 0; row < 9; ++row) {
            std::getline(input, line);
            values += line;
        }
        
        Sudoku sudoku(values);
        sudoku.solve();
        
        int upperleft = sudoku.getGridValue(0, 0) * 100 +
                        sudoku.getGridValue(0, 1) * 10  +
                        sudoku.getGridValue(0, 2);
        sum += upperleft;
    }
    std::cout << sum << std::endl;
    
    return 0;
}