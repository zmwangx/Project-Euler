//
//  main.cpp
//  Prbl095
//  Project Euler
//
//  Created by Zhiming Wang on 12/15/12.
//  Copyright (c) 2012 Zhiming Wang. All rights reserved.
//  -----------------------------------------------------
//  Algorithm:
//
//  Exhaustion.
//  -----------
//  Answer: 14316
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

static const int RANGE = 1000000;

int main() {
    std::vector<int> next;
    next.push_back(0);
    
    std::ifstream input("/Users/ZhimingWang/Dropbox/02ProgrammingProjects/"
                        "ProjectEuler/C++/Prbl095/prbl095.txt");
    if (!input.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        exit(-1);
    }
    while (input.good()) {
        std::string line;
        std::getline(input, line);
        std::istringstream lineStream(line);
        while (lineStream.good()) {
            std::string intString;
            std::getline(lineStream, intString, ',');
            while (intString[0] == ' ') {
                intString.erase(intString.begin());
            }
            if (intString.empty()) {
                continue;
            }
            next.push_back(std::atoi(intString.c_str()));
        }
    }
    
    std::vector<bool> visited(RANGE + 1, false);
    std::vector<bool> visitedInPreviousIterations(RANGE + 1, false);
    
    visited[1] = true;
    visitedInPreviousIterations[1] = true;
    
    std::vector<int> longestAmicableChain;
    
    for (int n = 220; n <= RANGE; ++n) {
        if (!visited[n]) {
            std::vector<int> chain;
            int current = n;
            chain.push_back(n);
            visited[n] = true;

            bool newAmicableChainFound;
            while (true) {
                current = next[current];
                if (current > RANGE || visitedInPreviousIterations[current]) {
                    newAmicableChainFound = false;
                    break;
                }
                if (visited[current]) {
                    newAmicableChainFound = true;
                    break;
                }
                chain.push_back(current);
                visited[current] = true;
            }
            
            if (newAmicableChainFound) {
                std::vector<int> amicableChain;
                int amicableChainFirstElement = current;
                bool amicableChainHasBegun = false;
                
                for (std::vector<int>::const_iterator i = chain.begin();
                     i != chain.end();
                     ++i) {
                    int element = *i;
                    visitedInPreviousIterations[element] = true;
                    if (element == amicableChainFirstElement) {
                        amicableChainHasBegun = true;
                    }
                    if (amicableChainHasBegun) {
                        amicableChain.push_back(element);
                    }
                }
                
                if (amicableChain.size() > longestAmicableChain.size()) {
                    longestAmicableChain = amicableChain;
                }
            }
        }
    }
    
    std::cout << longestAmicableChain.size() << std::endl;
    std::sort(longestAmicableChain.begin(), longestAmicableChain.end());
    std::cout << *(longestAmicableChain.begin()) << std::endl;
    
    return 0;
}