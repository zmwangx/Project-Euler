//
//  main.cpp
//  Prbl042
//  Project Euler
//
//  Created by Zhiming Wang on 12/07/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Brute force search.
//  -------------------
//  Answer: 162
// 

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

static bool isTriangleNumber(int n);
static int wordValue(std::string word);

int main() {
    std::ifstream infile("/Users/ZhimingWang/Documents/02Programming/C++/"
                         "ProjectEuler/Prbl042/words.txt");
    int nTriangleWords = 0;
    while (true) {
        std::string word;
        std::getline(infile, word, '\"');
        if (infile.eof()) {
            break;
        }
        if ((word == "") || (word == ",")) {
            continue;
        }
        if (isTriangleNumber(wordValue(word))) {
            ++nTriangleWords;
        }
    }
    
    std::cout << nTriangleWords << std::endl;
    
    return 0;
}

static bool isTriangleNumber(int n) {
    int k = static_cast<int>(std::sqrt(2 * n));
    return (n == k * (k + 1) / 2);
}

static int wordValue(std::string word) {
    int value = 0;
    for (std::string::const_iterator i = word.begin(); i != word.end(); ++i) {
        value += *i - 'A' + 1;
    }
    return value;
}