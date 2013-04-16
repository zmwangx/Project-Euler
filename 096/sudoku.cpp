//
//  sudoku.cpp
//  Prbl096
//  ProjectEuler
//
//  Created by Zhiming Wang on 12/15/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Implements the <code>Sudoku</code> class.
//

#include "sudoku.h"

#include <iostream>

Sudoku::Sudoku() {
    // Do nothing.
}

Sudoku::Sudoku(std::string values) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            grids[row][col].value = 0;
            grids[row][col].possibilities = returnAllPossibilities();
        }
    }
    
    nAmbiguous = 81;
    auto valueIt = values.begin();
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (*valueIt != '0') {
                Coord coord(row, col);
                fix(coord, *valueIt - '0');
            };
            ++valueIt;
        }
    }
    
    // Reinitialize <code>toBeFixed</code>.
    while (!toBeFixed.empty()) {
        toBeFixed.pop();
    }
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grids[row][col].value == 0 &&
                grids[row][col].possibilities.size() == 0) {
                // Failure.
                std::cerr << "Error input. No solution." << std::endl;
                exit(-1);
            }
            if (grids[row][col].possibilities.size() == 1) {
                Coord coord(row, col);
                toBeFixed.push(coord);
            }
        }
    }
}

Sudoku::Sudoku(const Sudoku& other) {
    *this = other;
}

Sudoku::~Sudoku() {
    // Do nothing.
}

Sudoku& Sudoku::operator=(const Sudoku& other) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            grids[row][col] = other.grids[row][col];
        }
    }
    nAmbiguous = other.nAmbiguous;
    toBeFixed = other.toBeFixed;
    return *this;
}

bool Sudoku::solve() {
    bool successfullyReduced = reduce();
    if (!successfullyReduced) {
        return false;
    }
    
    if (nAmbiguous == 0) {
        return true;
    }
    
    Sudoku absolute(*this); // For backtracking.
    
    Coord leastAmbiguousCoord(getLeastAmbiguous());
    Possibilities possibilities =
    grids[leastAmbiguousCoord.row][leastAmbiguousCoord.col].possibilities;
    for (auto i = possibilities.begin(); i != possibilities.end(); ++i) {
        fix(leastAmbiguousCoord, *i);
        if (solve()) {
            return true;
        }
        *this = absolute;
    }
    return false;
}

bool Sudoku::reduce() {
    while (!toBeFixed.empty()) {
        Coord newFixed = toBeFixed.top();
        toBeFixed.pop();
        
        int value = *(grids[newFixed.row][newFixed.col].possibilities.begin());
        bool successfullyFixed = fix(newFixed, value);
        if (!successfullyFixed) {
            // Failure.
            return false;
        }
    }
    return true;
}

bool Sudoku::fix(Coord coord, int value) {
    int row = coord.row;
    int col = coord.col;
    grids[row][col].value = value;
    grids[row][col].possibilities.clear();
    --nAmbiguous;
    
    std::vector<Coord> neighbors = getNeighbors(coord);
    for (auto i = neighbors.begin(); i != neighbors.end(); ++i) {
        Grid& neighbor = grids[i->row][i->col];
        if (neighbor.value != 0) {
            continue;
        }
        
        Possibilities::size_type
        nPossibilitiesBefore = neighbor.possibilities.size();
        
        neighbor.possibilities.erase(value);
        
        Possibilities::size_type
        nPossibilitiesAfter  = neighbor.possibilities.size();
        
        if (nPossibilitiesAfter < nPossibilitiesBefore) {
            if (neighbor.possibilities.size() == 0) {
                return false;
            }
            if (neighbor.possibilities.size() == 1) {
                toBeFixed.push(*i);
            }
        };
    }
    return true;
}

std::vector<Sudoku::Coord> Sudoku::getNeighbors(Coord thisCoord) const {
    std::vector<Coord> neighbors;
    
    int thisRow = thisCoord.row;
    int thisCol = thisCoord.col;
    
    // Same row.
    for (int col = 0; col < 9; ++col) {
        if (col != thisCol) {
            Coord coord(thisRow, col);
            neighbors.push_back(coord);
        }
    }
    
    // Same col.
    for (int row = 0; row < 9; ++row) {
        if (row != thisRow) {
            Coord coord(row, thisCol);
            neighbors.push_back(coord);
        }
    }
    
    // Same block.
    int blockBeginRow = thisRow / 3 * 3;
    int blockBeginCol = thisCol / 3 * 3;
    for (int row = blockBeginRow; row < blockBeginRow + 3; ++row) {
        for (int col = blockBeginCol; col < blockBeginCol + 3; ++col) {
            if (row != thisRow || col != thisCol) {
                Coord coord(row, col);
                neighbors.push_back(coord);
            }
        }
    }
    
    return neighbors;
}

Sudoku::Coord Sudoku::getLeastAmbiguous() const {
    Possibilities::size_type leastNPossibilities = 10;
    Coord leastAmbiguousCoord;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grids[row][col].value == 0 &&
                grids[row][col].possibilities.size() < leastNPossibilities) {
                leastNPossibilities = grids[row][col].possibilities.size();
                leastAmbiguousCoord.set(row, col);
            }
        }
    }
    return leastAmbiguousCoord;
}

int Sudoku::getGridValue(int row, int col) const {
    return grids[row][col].value;
}

void Sudoku::print() const {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            std::cout << grids[row][col].value;
        }
        std::cout << std::endl;
    }
}