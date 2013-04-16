//
//  main.cpp
//  Prbl089
//  Project Euler
//
//  Created by Zhiming Wang on 12/11/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Dynamic programming.
//
//  First we list all legal numerals and subtractive combinations as seen in
//  <code>onedigitStandards</code>, <code>twoDigitStandards</code>, and
//  <code>threeDigitStandards</code>. Each <code>Standard</code> object
//  contains two fields: the integral value, and the length of representation.
//  The first field, the Roman numeral representation, is only for readability.
//  1000 is not included since it will be treated differently.
//
//  Then, for 0 <= n <= 999, it is easy to prove that the minimal lengths
//  satisfy:
//
//  length[0] = 0 (only for convinience of presenting formula);
//  length[n] = min{length[n - standard.value] + standard.length,
//
//                  standard is a d-digit Standard object (d is the number of
//                  digits in n), where:
//                  (i)  standard.value <= n,
//                  (ii) standard.value >= standardValue[n - standard.value],
//                       where standardValue[n] records the maximal standard
//                       used in the minimal representation of n.
//                  }.
//
//  For n >= 1000, it must contain Floor[n / 1000] Ms (1000), and the rest is
//  treated as 0 <= n <= 999.
//  -------------------------
//  Answer:
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Standard {
    unsigned value;
    unsigned length;
    std::string representation;
};

static const std::vector<Standard> ONE_DIGIT_STANDARDS =
{{1, 1, "I"}, {4, 2, "IV"}, {5, 1, "V"}, {9, 2, "IX"}};
static const std::vector<Standard> TWO_DIGIT_STANDARDS =
{{10, 1, "X"}, {40, 2, "XL"}, {50, 1, "L"}, {90, 2, "XC"}};
static const std::vector<Standard> THREE_DIGIT_STANDARDS =
{{100, 1, "C"}, {400, 2, "CD"}, {500, 1, "D"}, {900, 2, "CM"}};

enum ROMAN_NUMERAL {
    I = 1,
    V = 5,
    X = 10,
    L = 50,
    C = 100,
    D = 500,
    M = 1000,
};

static void compute0To999(std::vector<unsigned>& lengths);
static inline unsigned computeMinimalLength(unsigned n,
                                            std::vector<unsigned>& lengths);
static unsigned romanToInt(const std::string& romanString);

int main() {
    std::vector<unsigned> lengths;
    compute0To999(lengths);
    
    std::ifstream input("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                        "ProjectEuler/C++/Prbl089/roman.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening roman.txt!" << std::endl;
        exit(-1);
    }
    
    unsigned originalLengthSum = 0;
    unsigned minimalLengthSum = 0;
    while (input.good()) {
        std::string romanString;
        std::getline(input, romanString);
        if (romanString.empty()) {
            break;
        }
        
        originalLengthSum += romanString.length();
        unsigned decimalValue = romanToInt(romanString);
        minimalLengthSum += computeMinimalLength(decimalValue, lengths);
    }
    
    std::cout << originalLengthSum - minimalLengthSum << std::endl;
    
    return 0;
}

static void compute0To999(std::vector<unsigned>& lengths) {
    std::vector<unsigned> standardValues;
    
    lengths.clear();
    standardValues.clear();
    // length[0] = 0
    lengths.push_back(0);
    standardValues.push_back(0);
    
    for (unsigned n = 1; n <= 999; ++n) {
        const std::vector<Standard>* standardsPtr;
        if (n < 10) {
            standardsPtr = &ONE_DIGIT_STANDARDS;
        } else if (n < 100) {
            standardsPtr = &TWO_DIGIT_STANDARDS;
        } else {
            standardsPtr = &THREE_DIGIT_STANDARDS;
        }
        
        const std::vector<Standard>& standards = *standardsPtr;
        
        unsigned minLength = n + 1;
        unsigned maxStandardValue = 0;
        
        for (std::vector<Standard>::const_iterator
             standardsIt = standards.begin();
             standardsIt != standards.end();
             ++standardsIt) {
            const Standard& standard = *standardsIt;
            // condition (i) for standard
            if (standard.value > n) {
                break;
            }
            unsigned reduced = n - standard.value;
            if (standard.value < standardValues[reduced]) {
                continue;
            }
            
            unsigned newLength = lengths[reduced] + standard.length;
            if (newLength < minLength) {
                minLength = newLength;
                maxStandardValue = standard.value;
            }
        }
        
        lengths.push_back(minLength);
        standardValues.push_back(maxStandardValue);
    }
}

static unsigned computeMinimalLength(unsigned n,
                                     std::vector<unsigned>& lengths) {
    return n / 1000 + lengths[n % 1000];
}

static unsigned romanToInt(const std::string& romanString) {
    std::basic_string<ROMAN_NUMERAL> romanValue;
    for (std::string::const_iterator i = romanString.begin();
         i != romanString.end();
         ++i) {
        switch (*i) {
            case 'I' :
                romanValue += I;
                break;
                
            case 'V' :
                romanValue += V;
                break;
                
            case 'X' :
                romanValue += X;
                break;
                
            case 'L' :
                romanValue += L;
                break;
                
            case 'C' :
                romanValue += C;
                break;
                
            case 'D' :
                romanValue += D;
                break;
                
            case 'M' :
                romanValue += M;
                break;                
        }
    }
    
    int decimalValue = 0;
    for (std::basic_string<ROMAN_NUMERAL>::const_iterator
         i = romanValue.begin();
         i != romanValue.end();
         ++i) {
        if ((i + 1 != romanValue.end()) && (*i < *(i + 1))) {
            // Subtractive pair
            decimalValue -= *i;
        } else {
            decimalValue += *i;
        }
    }
    
    return static_cast<unsigned>(decimalValue);
}