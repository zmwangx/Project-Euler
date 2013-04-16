//
//  sudoku.h
//  Prbl096
//  ProjectEuler
//
//  Created by Zhiming Wang on 12/15/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Defines the interface of the <code>Sudoku</code> class.
//

#ifndef __ProjectEuler__sudoku__
#define __ProjectEuler__sudoku__

#include <string>
#include <vector>
#include <set>
#include <stack>

class Sudoku {
    
    struct Coord {
        
        int row;
        int col;
        
        Coord() {
            // Do nothing.
        };
        Coord(int row, int col) {
            this->row = row;
            this->col = col;
        }
        Coord(const Coord& other) {
            *this = other;
        }
        
        ~Coord() {
            // Do nothing.
        };
        
        Coord& operator=(const Coord& other) {
            row = other.row;
            col = other.col;
            return *this;
        }
        
        void set(int row, int col) {
            this->row = row;
            this->col = col;
        }
        
    };
    
    typedef std::set<int> Possibilities;
    
    struct Grid {
        
        int value;
        Possibilities possibilities;
        
        Grid() {
            // Do nothing.
        };
        Grid(const Grid& other) {
            *this = other;
        }
        
        ~Grid() {
            // Do nothing.
        };
        
        Grid& operator=(const Grid& other) {
            value = other.value;
            possibilities = other.possibilities;
            return *this;
        }
        
    };
    
    
    
    Grid grids[9][9];
    
    int nAmbiguous;
    
    std::stack<Coord> toBeFixed;
    
public:
    
    Sudoku();
    Sudoku(std::string values);
    Sudoku(const Sudoku& other);
    
    ~Sudoku();
    
    Sudoku& operator=(const Sudoku& other);
    
    bool solve();
    
    bool reduce();
    
    bool fix(Coord coord, int value);
    
    std::vector<Coord> getNeighbors(Coord thisCoord) const;
    
    Coord getLeastAmbiguous() const;
    
    int getGridValue(int row, int col) const;
    
    Possibilities returnAllPossibilities() {
        static Possibilities kAllPossibilities = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        return kAllPossibilities;
    }
    
    void print() const;
    
};

#endif /* defined(__ProjectEuler__sudoku__) */
