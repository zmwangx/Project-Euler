//
//  main.cpp
//  Prbl061
//  Project Euler
//
//  Created by Zhiming Wang on 12/09/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Starting from octagonal number and cycle through all possibilities (DFS).
//  -------------------------------------------------------------------------
//  Answer: 28684
//

// Define the file stream used for debugging.
// #define __PRBL061_IS_IN_DEBUGGING__ 0
// Test the functionality of <code>preProcess</code>
// #define __PRBL061_IS_IN_DEBUGGING_PHASE_01__ 1

#ifdef __PRBL061_IS_IN_DEBUGGING__
#include <fstream>
std::ofstream debuggingLog;
#endif

#include <iostream>
#include <vector>
#include <set>
#include <cmath>

// 0 for Triangle, 1 for Square, 2 for Pentagonal, 3 for Hexagonal, 4 for
// Heptogonal, 5 for Octogonal
enum PolygonalType {
    TRIANGLE,   SQUARE,     PENTAGONAL,
    HEXAGONAL,  HEPTOGONAL, OCTOGONAL,
};

typedef int TwoDigits;

// Used to store the one type extensions to a <code>TwoDigits</code>.
typedef std::set<TwoDigits> Extensions;

// Used to store all types of extensions to a <code>TwoDigits</code>.
typedef std::vector<Extensions> AllTypeExtensions;

// Used to store all types of extensions to all <code>TwoDigits</code>.
typedef std::vector<AllTypeExtensions> ExtensionCollection;

typedef std::set<PolygonalType> Availabilities;

static void preProcess(ExtensionCollection& allExtensions);

static inline int triangle(int n);
static inline int square(int n);
static inline int pentagonal(int n);
static inline int hexagonal(int n);
static inline int heptogonal(int n);
static inline int octogonal(int n);

static inline TwoDigits upperDigits(int n);
static inline TwoDigits lowerDigits(int n);

static void generateCycles(TwoDigits chainBegin, TwoDigits chainEnd,
                           std::vector<TwoDigits> chain,
                           std::vector<PolygonalType> typeChain,
                           Availabilities availabilities,
                           int nAvailabilities,
                           const ExtensionCollection& allExtensions);
static void printCycle(const std::vector<TwoDigits> chain,
                       const std::vector<PolygonalType> typeChain);

static inline double solveQuadraticEquation(double a, double b, double c);

static inline int triangleInverse(int n);
static inline int squareInverse(int n);
static inline int pentagonalInverse(int n);
static inline int hexagonalInverse(int n);
static inline int heptogonalInverse(int n);
static inline int octogonalInverse(int n);

int main() {
    
#ifdef __PRBL061_IS_IN_DEBUGGING__
    debuggingLog.open("prbl061DebuggingLog.log");
    if (!debuggingLog.is_open()) {
        std::cerr << "Error opening debugging log!" << std::endl;
        exit(-1);
    }
#endif
    
    ExtensionCollection allExtensions;
    // Extensions of a single type to a single <code>TwoDigits</code> can be
    // accessed by <code>allExtensions[twoDigits][polygonalType]</code>. For
    // this reason, though <code>TwoDigits</code> objects are meaningless when
    // they are less than 10, 0, ... , 9 also pushed into <code>allExtensions</
    // code>.
    
    preProcess(allExtensions);
    
    for (TwoDigits twoDigits = 10; twoDigits < 100; ++twoDigits) {
        PolygonalType type = OCTOGONAL;
        Extensions& extensions = allExtensions[twoDigits][type];
        for (Extensions::const_iterator extensionsIt = extensions.begin();
             extensionsIt != extensions.end();
             ++extensionsIt) {
            
            TwoDigits chainBegin = twoDigits;
            TwoDigits chainEnd = *extensionsIt;
            
            std::vector<TwoDigits> chain;
            chain.push_back(chainBegin);
            chain.push_back(chainEnd);
            
            std::vector<PolygonalType> typeChain;
            typeChain.push_back(type);
            
            Availabilities availabilities =
            {TRIANGLE, SQUARE, PENTAGONAL, HEXAGONAL, HEPTOGONAL};
            
            int nAvailabilities = 5;
            
            generateCycles(chainBegin, chainEnd, chain, typeChain,
                           availabilities, nAvailabilities, allExtensions);
        }
    }
    
    return 0;
}

static void preProcess(ExtensionCollection& allExtensions) {
    for (TwoDigits twoDigits = 0; twoDigits < 100; ++twoDigits) {
        AllTypeExtensions emptyAllTypeExtensions;
        allExtensions.push_back(emptyAllTypeExtensions);
        
        AllTypeExtensions& allTypeExtensions = allExtensions[twoDigits];
        for (PolygonalType type = TRIANGLE; type <= OCTOGONAL; ++type) {
            Extensions emptyExtensions;
            allTypeExtensions.push_back(emptyExtensions);
        }
    }
    
    for (PolygonalType type = TRIANGLE; type <= OCTOGONAL; ++type) {
        int (*polygonal)(int n);
        switch (type) {
            case TRIANGLE :
                polygonal = &triangle;
                break;
                
            case SQUARE :
                polygonal = &square;
                break;
                
            case PENTAGONAL :
                polygonal = &pentagonal;
                break;
                
            case HEXAGONAL :
                polygonal = &hexagonal;
                break;
                
            case HEPTOGONAL :
                polygonal = &heptogonal;
                break;
                
            case OCTOGONAL :
                polygonal = &octogonal;
                break;
                
            default:
                std::cerr << "Error assigning polygonal function!"
                          << std::endl;
                exit(-1);
                break;
        }
        
        int n = 1;
        while (true) {
            int p = polygonal(n);
            if (p >= 10000) {
                break;
            }
            if (p >= 1000) {
                TwoDigits pUpperDigits = upperDigits(p);
                TwoDigits pLowerDigits = lowerDigits(p);
                if (pUpperDigits >= 10 && pLowerDigits >= 10) {
                    allExtensions[pUpperDigits][type].insert(pLowerDigits);
                }
            }
            ++n;
        }
    }

#ifdef __PRBL061_IS_IN_DEBUGGING__
#ifdef __PRBL061_IS_IN_DEBUGGING_PHASE_01__
    for (TwoDigits twoDigits = 10; twoDigits < 100; ++twoDigits) {
        debuggingLog << twoDigits << std::endl;
        for (PolygonalType type = TRIANGLE; type <= OCTOGONAL; ++type) {
            switch (type) {
                case TRIANGLE :
                    debuggingLog << "Triangle: ";
                    break;
                    
                case SQUARE :
                    debuggingLog << "Square: ";
                    break;
                    
                case PENTAGONAL :
                    debuggingLog << "Pentagonal: ";
                    break;
                    
                case HEXAGONAL :
                    debuggingLog << "Hexagonal: ";
                    break;
                    
                case HEPTOGONAL :
                    debuggingLog << "Heptogonal: ";
                    break;
                    
                case OCTOGONAL :
                    debuggingLog << "Octogonal: ";
                    break;
                    
                default:
                    debuggingLog << "Unrecognizable polygonal type!";
                    exit(-1);
                    break;
            }
            Extensions& extensions = allExtensions[twoDigits][type];
            for (Extensions::const_iterator i = extensions.begin();
                 i != extensions.end();
                 ++i) {
                debuggingLog << twoDigits << *i << " ";
            }
            debuggingLog << std::endl;
        }
        debuggingLog << std::endl;
    }
#endif
#endif
    
}

static int triangle(int n) {
    return n * (n + 1) / 2;
}

static int square(int n) {
    return n * n;
}

static int pentagonal(int n) {
    return n * (3 * n - 1) / 2;
}

static int hexagonal(int n) {
    return n * (2 * n - 1);
}

static int heptogonal(int n) {
    return n * (5 * n - 3) / 2;
}

static int octogonal(int n) {
    return n * (3 * n - 2);
}

static TwoDigits upperDigits(int n) {
    return n / 100;
}

static TwoDigits lowerDigits(int n) {
    return n % 100;
}

static void generateCycles(TwoDigits chainBegin, TwoDigits chainEnd,
                           std::vector<TwoDigits> chain,
                           std::vector<PolygonalType> typeChain,
                           Availabilities availabilities,
                           int nAvailabilities,
                           const ExtensionCollection& allExtensions) {
    // printCycle(chain, typeChain);
    
    if (nAvailabilities == 1) {
        PolygonalType type = *(availabilities.begin());
        typeChain.push_back(type);
        const Extensions& extensions = allExtensions[chainEnd][type];
        if (extensions.find(chainBegin) != extensions.end()) {
            // Success.
            printCycle(chain, typeChain);
            exit(0);
        }
        
        return;
    }
    
    // Recursion change 1
    --nAvailabilities;
    for (Availabilities::iterator availabilitiesIt = availabilities.begin();
         availabilitiesIt != availabilities.end();
         ++availabilitiesIt) {
        
        PolygonalType type = *availabilitiesIt;
        
        // Recursion change 2
        // Note that since the iterators to <code>availabilies</code> are in
        // use, <code>availablilies</code> cannot be modified in anyway.
        Availabilities newAvailabilities = availabilities;
        newAvailabilities.erase(newAvailabilities.find(type));
        typeChain.push_back(type);
        
        const Extensions& extensions = allExtensions[chainEnd][type];
        
        for (Extensions::const_iterator extensionsIt = extensions.begin();
             extensionsIt != extensions.end();
             ++extensionsIt) {
            TwoDigits newChainEnd = *extensionsIt;
            
            // Recursion change 3
            chain.push_back(newChainEnd);
            
            generateCycles(chainBegin, newChainEnd, chain, typeChain,
                           newAvailabilities, nAvailabilities, allExtensions);
            
            // Backtracking 3
            chain.pop_back();
        }
        
        // Backtracking 2
        typeChain.pop_back();
    }
}

static void printCycle(const std::vector<TwoDigits> chain,
                       const std::vector<PolygonalType> typeChain) {
    int sum = 0;
    for (int i = 0; i < 6; ++i) {
        int polygonalValue = chain[i] * 100 + chain[(i + 1) % 6];
        sum += polygonalValue;
        
        PolygonalType type = typeChain[i];
        
        int polygonalRepresentation = type + 3;
        int (*polygonalInverse)(int n);
        switch (type) {
            case TRIANGLE :
                polygonalInverse = &triangleInverse;
                break;
                
            case SQUARE :
                polygonalInverse = &squareInverse;
                break;
                
            case PENTAGONAL :
                polygonalInverse = &pentagonalInverse;
                break;
                
            case HEXAGONAL :
                polygonalInverse = &hexagonalInverse;
                break;
                
            case HEPTOGONAL :
                polygonalInverse = &heptogonalInverse;
                break;
                
            case OCTOGONAL :
                polygonalInverse = &octogonalInverse;
                break;
        }
        int polygonalInverseValue = polygonalInverse(polygonalValue);
        
        std::cout << "P(" << polygonalRepresentation
                  << ", " << polygonalInverseValue << ") = "
                  << polygonalValue
                  << std::endl;
    }
    std::cout << "sum: " << sum << std::endl;
}

static double solveQuadraticEquation(double a, double b, double c) {
    return (-b + std::sqrt(b*b - 4*a*c)) / (2*a);
}

static int triangleInverse(int n) {
    return static_cast<int>(solveQuadraticEquation(0.5, 0.5, -n));
}

static int squareInverse(int n) {
    return static_cast<int>(solveQuadraticEquation(1, 0, -n));
}

static int pentagonalInverse(int n) {
    return static_cast<int>(solveQuadraticEquation(1.5, -0.5, -n));
}

static int hexagonalInverse(int n) {
    return static_cast<int>(solveQuadraticEquation(2, -1, -n));
}

static int heptogonalInverse(int n) {
    return static_cast<int>(solveQuadraticEquation(2.5, -1.5, -n));
}

static int octogonalInverse(int n) {
    return static_cast<int>(solveQuadraticEquation(3, -2, -n));
}