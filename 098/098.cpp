//
//  main.cpp
//  Prbl098
//  Project Euler
//
//  Created by Zhiming Wang on 12/16/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Exhaustion.
//  -----------
//  Answer: 18769
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#include <map>
#include <set>

// Print intermediate results for human analysis.
// #define __IS_IN_HUMAN_ANALYSIS_MODE__

typedef std::string Word;

typedef std::pair<Word, Word> Anagram;

typedef std::vector<std::vector<Anagram> > AnagramLexicon;

struct SortedWord {
    Word word;
    Word sorted;
    
    SortedWord() {
        // Do nothing
    }
    
    SortedWord(Word word) {
        this->word = word;
        this->sorted = word;
        std::sort(this->sorted.begin(), this->sorted.end());
    }
    
    SortedWord(const SortedWord& other) {
        *this = other;
    }
    
    SortedWord& operator=(const SortedWord& other) {
        word = other.word;
        sorted = other.sorted;
        return *this;
    }
    
    friend bool operator<(const SortedWord& sortedWord1, const SortedWord& sortedWord2) {
        if (sortedWord1.word.size() < sortedWord2.word.size()) {
            return true;
        } else if (sortedWord2.word.size() < sortedWord1.word.size()) {
            return false;
        } else if (sortedWord1.sorted < sortedWord2.sorted) {
            return true;
        } else if (sortedWord2.sorted < sortedWord1.sorted) {
            return false;
        } else {
            return sortedWord1.word < sortedWord2.word;
        }
    }
    
};

bool operator<(const SortedWord& sortedWord1, const SortedWord& sortedWord2);

typedef std::vector<SortedWord> SortedLexicon;

typedef std::string Digits;

static inline Digits intToDigits(int integer) {
    return std::to_string(integer);
}

static inline int digitsToInt(Digits digits) {
    return std::atoi(digits.c_str());
}

static bool isSquare(int n) {
    int base = static_cast<int>(std::floor(std::sqrt(n)));
    return base * base == n;
}

int main() {
    std::ifstream input("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                        "ProjectEuler/C++/Prbl098/words.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening words.txt!" << std::endl;
        exit(-1);
    }
    
    SortedLexicon sortedLexicon;
    while (input.good()) {
        std::string line;
        std::getline(input, line, ',');
        std::istringstream lineStream(line);
        std::string word;
        std::getline(lineStream, word, '\"');
        std::getline(lineStream, word, '\"');
        SortedWord sortedWord(word);
        sortedLexicon.push_back(sortedWord);
    }
    std::sort(sortedLexicon.begin(), sortedLexicon.end());
    
#ifdef __IS_IN_HUMAN_ANALYSIS_MODE__
    std::ofstream output("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                         "ProjectEuler/C++/Prbl098/generatedData.txt");
    if (!output.is_open()) {
        std::cerr << "Error opening generatedData.txt!" << std::endl;
        exit(-1);
    }
    for (auto i = sortedLexicon.begin(); i != sortedLexicon.end(); ++i) {
        if ((i + 1 != sortedLexicon.end() && i->sorted == (i + 1)->sorted) ||
            (i != sortedLexicon.begin() && i->sorted == (i - 1)->sorted)) {
            output << i->sorted << ' ' << i->word << std::endl;
        }
    }
#endif
    
    AnagramLexicon anagramLexicon(10); // length = 0, 1, ... , 9
    auto i = sortedLexicon.begin();
    while (i != sortedLexicon.end()) {
        Word sorted1;
        Word sorted2;
        Word sorted3;
        Word word1;
        Word word2;
        Word word3;
        
        sorted1 = i->sorted;
        word1 = i->word;
        if (i + 1 != sortedLexicon.end()) {
            sorted2 = (i + 1)->sorted;
            word2 = (i + 1)->word;
            if (i + 2 != sortedLexicon.end()) {
                sorted3 = (i + 2)->sorted;
                word3 = (i + 2)->sorted;
            }
        }
        
        Word::size_type length = word1.size();
        
        if (sorted1 != sorted2) {
            i += 1;
        } else if (sorted2 != sorted3) {
            anagramLexicon[length].push_back({word1, word2});
            i += 2;
        } else {
            anagramLexicon[length].push_back({word1, word2});
            anagramLexicon[length].push_back({word1, word3});
            anagramLexicon[length].push_back({word2, word3});
            i += 3;
        }
    }
    
    for (int length = 1; length <= 9; ++length) {
        int minimalBase =
        static_cast<int>(std::ceil(std::pow(10, (length - 1)/2.0)));
        int maximalBase =
        static_cast<int>(std::floor(std::sqrt(std::pow(10, length) - 1)));
        
        for (auto anagramIt = anagramLexicon[length].begin();
             anagramIt != anagramLexicon[length].end();
             ++anagramIt) {
            Word origin = anagramIt->first;
            Word target = anagramIt->second;
            for (int base = minimalBase; base <= maximalBase; ++base) {
                Digits originDigits = intToDigits(base * base);
                std::map<char, char> charToDigitMap;
                std::set<char> usedDigits;
                
                // Create character to digit map.
                bool hasAssignmentConflict = false;
                for (int i = 0; i < length; ++i) {
                    char character = origin[i];
                    char digit = originDigits[i];
                    
                    auto mapIt = charToDigitMap.find(character);
                    if (mapIt == charToDigitMap.end()) {
                        if (usedDigits.find(digit) == usedDigits.end()) {
                            charToDigitMap.insert({character, digit});
                            usedDigits.insert(digit);
                        } else {
                            // Digit is already used for another character.
                            hasAssignmentConflict = true;
                            break;
                        }
                    } else {
                        // Character is already mapped to a digit.
                        if (mapIt->second != digit) {
                            // Mapping same character to two digits.
                            hasAssignmentConflict = true;
                        }
                    }
                }
                if (hasAssignmentConflict) {
                    continue;
                }
                
                // Derive the corresponding digits representation of target.
                Digits derivedDigits;
                for (int i = 0; i < length; ++i) {
                    char character = target[i];
                    derivedDigits += charToDigitMap[character];
                }
                
                int derivedValue = digitsToInt(derivedDigits);
                
                if (isSquare(derivedValue) &&
                    derivedValue >= std::pow(10, length - 1)) {
                    std::cout
                    << origin << ' ' << originDigits << ' '
                    << target << ' ' << derivedDigits
                    << std::endl;
                }
            }
        }
    }
    return 0;
}